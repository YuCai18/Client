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
	if (SOCKET_ERROR == connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in))) {
		printf("ERROR,建立连接失败！\n");
	}
	else {
		printf("建立连接成功！\n");
	}
	
	while (true)
	{
		//3.输入请求命令
		char cmdBuf[128] = {};
		scanf("%s", cmdBuf);
		//4.处理请求
		if (0 == strcmp(cmdBuf,"exit")) {
			printf("收到exit命令，任务结束");
			break;
		}
		else {
			//5.向服务器发送请求命令
			send(_sock,cmdBuf,strlen(cmdBuf) + 1,0);
		}
		//6.接收服务器信息
		char recvBuf[128] = {};
		int nlen = recv(_sock, recvBuf, 128, 0);
		if (nlen > 0) {
			printf("接收到数据:%s", recvBuf);
		}
	}

	
	//7.关闭套接字
	closesocket(_sock);

	//清除windows socket环境
	WSACleanup();
	printf("已退出。");
	//防止一闪而过
	getchar();
	return 0;
}