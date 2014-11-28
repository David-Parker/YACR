#include <windows.h>
#include <winsock.h>
#include "ListeningServer.h"

#ifndef USER_H
#define USER_H

class User {
private:

public:
	char * name;
	SOCKET socket;

	User() {name = new char[MAX_MESSAGE_SIZE];}
};

#endif