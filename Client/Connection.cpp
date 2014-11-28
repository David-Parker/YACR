#include <iostream>
#include <windows.h> 
#include <winsock.h> 
#include <stdio.h>
#include "Connection.h"

using namespace std;

void Connection::ReportError(int errorCode, const char * function) {
	char errMsg[128] = {};
	errMsg[127] = '\0';
	sprintf(errMsg, "Call to %s returned error %d.", function, errorCode);
	MessageBox(NULL, errMsg, "socketIndication", MB_OK);
}

int Connection::setupConnection(int port, char* ipAddr) {
	WORD sockVersion;
	WSADATA wsaData;
	int nret;

	sockVersion = MAKEWORD(1,1);

	/* Setup the client socket */
	WSAStartup(sockVersion, &wsaData);

	/* Store server information */
	in_addr iaHost;
	iaHost.s_addr = inet_addr(ipAddr);
	LPHOSTENT hostEntry = gethostbyaddr((const char*)&iaHost,sizeof(struct in_addr),AF_INET); // gethostbyaddr()

	if(!hostEntry) {
		checkError(SOCKET_ERROR, "gethostby__()");
	}

	/* Create the client socket */
	cSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	checkError(cSocket, "socket()");

	/* Fill a SOCKADD_IN struct with address information */
	SOCKADDR_IN serverInfo;

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(port);

	/* Connect to the server */
	nret = connect(cSocket, (LPSOCKADDR)&serverInfo,sizeof(struct sockaddr));
	checkError(nret,"connect()");

	/* Successfully connected to the server! */

	return NETWORK_OK;
}

void Connection::closeConnection() {
	closesocket(cSocket);
	WSACleanup();
}

void Connection::sendMessage(const char * message) {
	int nret;
	char * buffer = new char[MAX_MESSAGE_SIZE];
	strcpy(buffer, message);
	nret = send(cSocket, buffer,strlen(buffer) + 1,0);

	if(nret == SOCKET_ERROR) {
		ReportError(WSAGetLastError(),"Send Message() Error!");
	}
}

