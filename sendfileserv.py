import socket
import os
import sys
import subprocess
import platform

def recv_all(sock, size):
    data = b''
    while len(data) < size:
        chunk = sock.recv(min(4096, size - len(data)))
        if not chunk:
            break
        data += chunk
    return data

def send_file(filename, conn):
    with open(filename, "rb") as f:
        data = f.read()
        size = f"{len(data):010}"
        conn.sendall(size.encode() + data)

def recv_file(filename, conn):
    try:
        size = int(conn.recv(10).decode())
        data = recv_all(conn, size)
        with open(filename, "wb") as f:
            f.write(data)
        print(f"Success: Received {filename} - {len(data)} bytes.")
    except ValueError:
        pass

def list_files():
    if platform.system() == "Windows":
        return subprocess.getoutput("dir")
    else:
        return subprocess.getoutput("ls -l")

def main():
    if len(sys.argv) != 2:
        print("Usage: python sendfileserv.py <port>")
        sys.exit(1)

    port = int(sys.argv[1])
    ctrl_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ctrl_sock.bind(('', port))
    ctrl_sock.listen(1)

    print(f"Server listening on port {port}...")

    while True:
        client_sock, client_addr = ctrl_sock.accept()
        print(f"Control connection from {client_addr}")

        while True:
            cmd_data = client_sock.recv(1024).decode()
            if not cmd_data:
                break

            if cmd_data.strip() == "quit":
                print("Client requested to quit.")
                break

            parts = cmd_data.strip().split()
            cmd = parts[0]
            filename = parts[1] if len(parts) > 1 else ""
            data_port = int(parts[-1])

            # Connect to client's ephemeral port
            data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            data_sock.connect((client_addr[0], data_port))

            if cmd == "put":
                recv_file(filename, data_sock)

            elif cmd == "get":
                if not os.path.exists(filename):
                    print("File not found.")
                else:
                    send_file(filename, data_sock)

            elif cmd == "ls":
                output = list_files()
                data_sock.sendall(output.encode())

            data_sock.close()

        client_sock.close()
        print("Control connection closed.")

if __name__ == "__main__":
    main()
