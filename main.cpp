#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ftp_client.hpp"
#include "ftp_server.hpp"


int main(int argc, char* argv[]) {
    int mode = 0; // 0 for client and 1 for server
    if (argc == 2) {
        // Valid input
        if (strcmp(argv[1], "server") == 0) mode = 1;
        else if (strcmp(argv[1], "client") == 0) mode = 0;
        else {
            fprintf(stderr, "Invalid usage: main.exe <client/server>\n");
            return -1;
        }
    }
    else {
        fprintf(stderr, "Invalid usage: main.exe <client/server>\n");
        return -1;
    }


    // Clientside
    if (mode == 0) {
        printf("Running FTP client\n");
        
        const char* host = "localhost";
        const char* port = "12345";
        if (clientInit(host, port) == 0) {
            fprintf(stderr, "Failed to run client\n");
            return -1;
        }

        clientMainLoop();
    }

    // Serverside
    if (mode == 1) {
        printf("Running FTP server\n");

        const char* port = "12345";
        if (serverInit(port) == 0) {
            fprintf(stderr, "Failed to run server\n");
            return -1;
        }

        serverMainLoop();
    }

    printf("Closing FTP...\n");
    return 0;
}