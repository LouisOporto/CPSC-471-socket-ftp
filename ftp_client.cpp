#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid usage: ./ftp_client <host> <port>\n");
        return -1;
    }

    
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd == -1) {
        fprintf(stderr, "Failed to create socket\n");
        return -1;
    }
    
    int port = std::stoi(argv[2]);
    sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    srvaddr.sin_addr.s_addr = INADDR_ANY; // localhost
    
    if(connect(sd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) == -1) {
        fprintf(stderr, "Failed to connect to FTP server\n");
        return -1;
    }
    printf("Running FTP client to localhost and port: %d\n", port);

    char buffer[1024];
    bool running = true;
    while (running) {
        printf("ftp> ");
        fgets(buffer, 1024, stdin);

        if((send(sd, buffer, 1024, 0)) < 0) {
            fprintf(stderr, "Failed to send message\n");
            return -1;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "quit") == 0) {
            running = false;
        }
    }

    close(sd);
    printf("Closing FTP client...\n");
    return 0;
}