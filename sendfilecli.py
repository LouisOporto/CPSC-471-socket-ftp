import socket
import os
import sys

def create_data_socket():
    data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    data_sock.bind(('', 0))  # Ephemeral port
    data_sock.listen(1)
    return data_sock, data_sock.getsockname()[1]

def send_file(filename, conn):
    with open(filename, "rb") as f:
        data = f.read()
        size = f"{len(data):010}"
        conn.sendall(size.encode() + data)

def recv_file(filename, conn):
    try:
        size = int(conn.recv(10).decode())
        data = b''
        while len(data) < size:
            chunk = conn.recv(min(4096, size - len(data)))
            if not chunk:
                break
            data += chunk
        with open(filename, "wb") as f:
            f.write(data)
        print(f"Success: {filename} - {len(data)} bytes received.")
    except ValueError:
        pass

def handle_command(ctrl_sock):
    while True:
        cmd = input("ftp> ").strip()
        if cmd == "quit":
            ctrl_sock.sendall(cmd.encode())
            break

        elif cmd.startswith("put ") or cmd.startswith("get ") or cmd == "ls":
            data_sock, data_port = create_data_socket()
            full_cmd = f"{cmd} {data_port}"
            ctrl_sock.sendall(full_cmd.encode())

            conn, _ = data_sock.accept()
            tokens = cmd.split()

            if tokens[0] == "put":
                filename = tokens[1]
                if not os.path.exists(filename):
                    print("Failure: File does not exist.")
                    conn.close()
                    continue
                send_file(filename, conn)

            elif tokens[0] == "get":
                filename = tokens[1]
                recv_file(filename, conn)

            elif tokens[0] == "ls":
                output = conn.recv(4096).decode()
                print(output)

            conn.close()
            data_sock.close()

        else:
            print("Invalid command.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python sendfilecli.py <server_host> <server_port>")
        sys.exit(1)

    server_host = sys.argv[1]
    server_port = int(sys.argv[2])

    ctrl_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ctrl_sock.connect((server_host, server_port))

    print("Connected to server.")
    handle_command(ctrl_sock)

    ctrl_sock.close()
    print("Disconnected.")
