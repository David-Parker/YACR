#include <iostream>
#include <windows.h> 
#include <winsock.h> 
#include <stdio.h>
#include "Connection.h"
#include <signal.h>
#include <thread>
#include <process.h>

using namespace std;
Connection * connptr = NULL;

void signal_callback_handler(int signum) {
	printf("Caught signal %d\n", signum);

	if(connptr != NULL) {
		printf("Closing connection.\n");
		connptr->closeConnection();
	}

	exit(signum);
}

unsigned __stdcall ServerMessage(void *data) {
	SOCKET sock = (SOCKET)data;
	Connection conn;
	int nret = 1;

	char * recvBuff = new char[MAX_MESSAGE_SIZE];
	while(nret) {
		nret = conn.recieve(recvBuff,MAX_MESSAGE_SIZE, sock);
		printf("%s\n", recvBuff);

		if(nret == SOCKET_ERROR) {
			free(recvBuff);
			return 0;
		}
	}
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShow) {
	/* Register the client signal handler */
	signal(SIGINT, signal_callback_handler);

	int port = 80;
	char ip[32];
	char name[MAX_MESSAGE_SIZE];

	cout << "Please enter a username: ";
	cin.getline(name,MAX_MESSAGE_SIZE);

	cout << "Please enter a port number (default is 80): ";
	cin >> port;

	cout << "Please enter an ip address: ";
	cin >> ip;

	Connection conn;
	connptr = &conn;
	conn.setupConnection(port, ip);
	conn.sendMessage(name);

	char msg[MAX_MESSAGE_SIZE] = {};

	/* Create a server message recieveing thread */
	unsigned threadID;
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &ServerMessage, (void*)conn.cSocket, 0, &threadID);

	while(true) {
		cin.getline(msg,MAX_MESSAGE_SIZE);
		if(strcmp(msg,""))
			conn.sendMessage(msg);
	}

	/* Connection Session Over */
	connptr->closeConnection();

	return 0;
}
