/*
#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//1.建立socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock) {
		printf("错误，建立Socket失败!\n");
	}
	else {
		printf("建立Socket成功!\n");
	}
	//2.连接服务器
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (SOCKET_ERROR == connect(_sock,(sockaddr*) &_sin, sizeof(sockaddr_in))){
		printf("ERROR,建立连接失败！\n");
	}
	else {
		printf("建立连接成功！\n");
	}
	//3.接收服务器信息
	char recvBuf[256] = {};
	int nlen = recv(_sock, recvBuf,256,0);
	if (nlen > 0) {
		printf("接收到数据:%s",recvBuf);
	}
	//4.关闭套接字
	closesocket(_sock);

	//清除windows socket环境
	WSACleanup();
	//防止一闪而过
	getchar();
	return 0;
}
*/