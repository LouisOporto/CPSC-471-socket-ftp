#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid usage: ./ftp_client <host> <port>\n");
        return -1;
    }

    printf("Running FTP client\n");
    
    const char* host = "localhost";
    const char* port = "12345";
    sockaddr_in srvaddr;

    int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    printf("Closing FTP client...\n");
    return 0;
}