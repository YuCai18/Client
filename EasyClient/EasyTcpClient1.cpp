#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
int main() {

	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//1.����socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock) {
		printf("���󣬽���Socketʧ��!\n");
	}
	else {
		printf("����Socket�ɹ�!\n");
	}
	//2.���ӷ�����
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (SOCKET_ERROR == connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in))) {
		printf("ERROR,��������ʧ�ܣ�\n");
	}
	else {
		printf("�������ӳɹ���\n");
	}
	
	while (true)
	{
		//3.������������
		char cmdBuf[128] = {};
		scanf("%s", cmdBuf);
		//4.��������
		if (0 == strcmp(cmdBuf,"exit")) {
			printf("�յ�exit����������");
			break;
		}
		else {
			//5.�������������������
			send(_sock,cmdBuf,strlen(cmdBuf) + 1,0);
		}
		//6.���շ�������Ϣ
		char recvBuf[128] = {};
		int nlen = recv(_sock, recvBuf, 128, 0);
		if (nlen > 0) {
			printf("���յ�����:%s", recvBuf);
		}
	}

	
	//7.�ر��׽���
	closesocket(_sock);

	//���windows socket����
	WSACleanup();
	printf("���˳���");
	//��ֹһ������
	getchar();
	return 0;
}