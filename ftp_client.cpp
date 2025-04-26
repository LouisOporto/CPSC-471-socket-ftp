#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid usage: ./ftp_client <host> <port>\n");
        return -1;
    }

    printf("Running FTP client\n");
    
    const char* port = "12345";
    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd == -1) {
        fprintf(stderr, "Failed to create socket\n");
        return -1;
    }
    
    sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = 12345;
    srvaddr.sin_addr.s_addr = INADDR_ANY; // localhost

    if(connect(sd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) == -1) {
        fprintf(stderr, "Failed to connect to FTP server\n");
        return -1;
    }

    printf("Closing FTP client...\n");
    return 0;
}