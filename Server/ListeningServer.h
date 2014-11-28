#ifndef LISTSER_H
#define LISTSER_H

#define NETWORK_ERROR  -1
#define NETWORK_OK 		0
#define NUM_CONNECTIONS 10
#define MAX_MESSAGE_SIZE 256

#define backKey '\b'	/* To disable backspaces, #define backKey NULL */
#define newLine '\n' 
#define endStr '\0' 

#define checkError(item, str)	do { \
		 							if(item == SOCKET_ERROR) {\
		 								nret = WSAGetLastError();\
		 								ReportError(nret,str);\
		 								WSACleanup();\
		 								return NETWORK_ERROR;\
									}\
								} while(0);

class ListeningServer {
private:
SOCKET client;

public:
	SOCKET listeningSocket;
	void ReportError(int errorCode, const char * function);
	int setupListening(int port);
	void closeServer();
	int recieve(SOCKET sock, char * &buffer, int size);
	char* readLine(SOCKET s, int);
};

#endif