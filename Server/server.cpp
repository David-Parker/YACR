#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include "ListeningServer.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
	int port = 88;
	cout << "Please enter a port number (default is 80): ";
	cin >> port;

	ListeningServer ls;
	ls.setupListening(port);

	ls.closeServer();
	return 0;
}

