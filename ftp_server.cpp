#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid usage: ./ftp_server <port>\n");
        return -1;
    }

    
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return -1;
    }
    
    int port = std::stoi(argv[1]); // Switch to using port 20 maybe?
    sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    srvaddr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0) {
        fprintf(stderr, "Failed to bind to port %d\n", port);
    }
    
    listen(sd, 5);
    
    printf("Running FTP server on port: %d\n", port);
    int csd;
    
    bool running = true;
    while (running) {
        csd = accept(sd, nullptr, nullptr);
        if (csd < 0) continue;
        else {
            close(sd);
            running = false;
        }
        printf("New connection\n");
        
    }

    printf("Closing FTP server...\n");
    return 0;
}