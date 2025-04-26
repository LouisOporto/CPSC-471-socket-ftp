#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>


bool serverInit(const char* port) {
    bool success = true;

    return success;
}

void serverMainLoop() {

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid usage: ./ftp_server <port>\n");
        return -1;
    }

    printf("Running FTP server\n");
    
    const char* port = "12345";
    if (serverInit(port) == 0) {
        fprintf(stderr, "Failed to run server\n");
        return -1;
    }

    serverMainLoop();

    printf("Closing FTP server...\n");
    return 0;
}