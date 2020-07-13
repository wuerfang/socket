#include<iostream>
#include<WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;

int main() {	
	char buff[100];
	int n;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "start socket error" << endl;
		return -1;
	}
		

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET) {
		cout << "create socket error" << endl;
		return -1;
	}
		

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;							//ʹ��IPv4��ַ
	sockAddr.sin_port = htons(6666);						//�˿ں�   Ҫ�õ�htons()����ת��
	sockAddr.sin_addr.s_addr = inet_addr("192.168.1.3");	//�����IP��ַ32λ
	//inet_pton(AF_INET, "127.0.0.1", (void*)&sockAddr.sin_addr.S_un.S_addr);
	
	if (bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {//���׽���
		cout << "bind socket error" << endl;
		return -1;
	}
	if (listen(servSock, 6) == SOCKET_ERROR) {
		cout << "bind socket error" << endl;
		return -1;
	}
	cout << "---waiting for client's request---" << endl;
	SOCKET connfd;
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	if ((connfd = accept(servSock, (SOCKADDR*)&clntAddr, &nSize)) == SOCKET_ERROR) {
		cout << "accept socket error" << endl;
		return -1;
	}
	while (1) {		
		n = recv(connfd, buff, 100, 0);
		//buff[n] = '\0';
		cout << buff << endl;
	}
	closesocket(connfd);
	closesocket(servSock);//�ر��׽���
	//��ֹ DLL ��ʹ��
	WSACleanup();
	system("pause");
	return 0;
}