#include<iostream>
#include<WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
//#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main() {
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock == INVALID_SOCKET) {
		cout << "create socket error" << endl;
		return -1;
	}

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(6666);
	sockAddr.sin_addr.s_addr = inet_addr("192.168.1.3");
	void *dst = nullptr;
	//sockAddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", dst);

	cout << "---connecting---" << endl;

	if (connect(clientSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) < 0) {
		cout << "connect error" << endl;
		return -1;
	}
	cout << "connecting success" << endl;
	cout << "send message to server: " << endl;

	while (1) {
		char buff[100];
		fgets(buff, 100, stdin);
		if (send(clientSock, buff, 100, 0) < 0) {
			cout << "send error" << endl;
			return -1;
		}
	}

	closesocket(clientSock);
	WSACleanup();
	system("pause");
	return 0;
}

