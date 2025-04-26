#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>


bool clientInit(const char* host, const char* port) {
    bool success = true;
    

    return success;
}

void clientMainLoop() {

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid usage: ./ftp_client <host> <port>\n");
        return -1;
    }

    printf("Running FTP client\n");
    
    const char* host = "localhost";
    const char* port = "12345";
    if (clientInit(host, port) == 0) {
        fprintf(stderr, "Failed to run client\n");
        return -1;
    }

    clientMainLoop();

    printf("Closing FTP client...\n");
    return 0;
}