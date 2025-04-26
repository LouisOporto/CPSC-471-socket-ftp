#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>


int main(int argc, char* argv[]) {
    // const char* port = 0;
    if (argc != 2) {
        fprintf(stderr, "Invalid usage: ./ftp_server <port>\n");
        return -1;
    }

    printf("Running FTP server\n");
    
    const char* port = "12345";
    sockaddr_in srvaddr;
    

    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = 12345;
    srvaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Closing FTP server...\n");
    return 0;
}