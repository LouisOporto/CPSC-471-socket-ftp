#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

bool clientInit(const char* host, const char* port);

void clientMainLoop();
