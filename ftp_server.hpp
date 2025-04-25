#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>


bool serverInit(const char* port);

void serverMainLoop();
