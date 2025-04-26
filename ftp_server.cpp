#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
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

    printf("Closing FTP server...\n");
    return 0;
}