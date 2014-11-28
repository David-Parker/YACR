#ifndef CNC_H
#define CNC_H

#define NETWORK_ERROR	-1
#define NETWORK_OK 		0
#define MAX_MESSAGE_SIZE 256

#define checkError(item, str)	do { \
		 							if(item == SOCKET_ERROR) {\
		 								nret = WSAGetLastError();\
		 								ReportError(nret,str);\
		 								WSACleanup();\
		 								return NETWORK_ERROR;\
									}\
								} while(0);

class Connection {
private:

public:
	SOCKET cSocket;
	void ReportError(int, const char*);
	int setupConnection(int port, char* ipAddr);
	void closeConnection();
	void sendMessage(const char * message);

};

#endif