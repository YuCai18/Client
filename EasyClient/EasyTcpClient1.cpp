#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
enum CMD
{
	CMD_LOGIN,
	CMD_LOGOUT,
	CMD_ERROR
};
//��Ϣͷ
struct DataHeader
{
	short dataLength; //���ݳ���
	short cmd;
};
//DataPackage
struct Login
{
	char userName[32];
	char PassWord[32];
};

struct LoginResult
{
	int result;

};

struct Logout
{
	char userName[32];
};

struct LogoutResult
{
	int result;

};
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
			printf("�յ�exit������������\n");
			break;
		}
		else if(0 == strcmp(cmdBuf, "login")){
			Login login = {"CaiYu","123"};
			DataHeader dh = { sizeof(Login),CMD_LOGIN};
			//5.�������������������
			send(_sock, (const char*)&dh,sizeof(dh),0);
			send(_sock, (const char*)&login, sizeof(login), 0);
			//���շ��������ص���Ϣ
			DataHeader retHeader = {};
			LoginResult loginRet = {};
			recv(_sock,(char*)&retHeader,sizeof(retHeader),0);
			recv(_sock, (char*)&loginRet, sizeof(loginRet), 0);
			printf("LoginResult:%d \n",loginRet.result);
		}
		else if (0 == strcmp(cmdBuf, "logout")) {
			Logout logout = {};
			DataHeader dh = {sizeof(logout),CMD_LOGOUT};
			//�������������������
			send(_sock, (const char*)&dh, sizeof(dh), 0);
			send(_sock, (const char*)&logout, sizeof(logout), 0);
			//���շ��������ص���Ϣ
			DataHeader retHeader = {};
			LogoutResult logoutRet = {};
			recv(_sock, (char*)&retHeader, sizeof(retHeader), 0);
			recv(_sock, (char*)&logoutRet, sizeof(logoutRet), 0);
			printf("LogoutResult :%d \n", logoutRet.result);
		}
		else {
			printf("�յ���֧��������������롣\n");
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