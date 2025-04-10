#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
enum CMD
{
	CMD_LOGIN,
	CMD_LOGIN_RESULT,
	CMD_LOGOUT,
	CMD_LOGOUT_RESULT,
	CMD_ERROR
};
//消息头
struct DataHeader
{
	short dataLength; //数据长度
	short cmd;
};
//DataPackage
struct Login :public DataHeader
{
	Login() {
		dataLength = sizeof(Login);
		cmd = CMD_LOGIN;
	}
	char userName[32];
	char PassWord[32];
};

struct LoginResult :public DataHeader
{
	LoginResult()
	{
		dataLength = sizeof(LoginResult);
		cmd = CMD_LOGIN_RESULT;
		result = 0;
	}
	int result;
};

struct Logout : public DataHeader
{
	Logout()
	{
		dataLength = sizeof(Logout);
		cmd = CMD_LOGOUT;
	}
	char userName[32];
};

struct LogoutResult : public DataHeader
{
	LogoutResult()
	{
		dataLength = sizeof(LogoutResult);
		cmd = CMD_LOGOUT_RESULT;
		result = 0;
	}
	int result;

};
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
			printf("收到exit命令，任务结束。\n");
			break;
		}
		else if(0 == strcmp(cmdBuf, "login")){
			//5.向服务器发送请求命令
			Login login;
			strcpy(login.userName,"CaiYu");
			strcpy(login.PassWord, "123");
			send(_sock, (const char*)&login, sizeof(login), 0);
			//接收服务器返回的消息
			LoginResult loginRet = {};
			recv(_sock, (char*)&loginRet, sizeof(loginRet), 0);
			printf("LoginResult:%d \n",loginRet.result);
		}
		else if (0 == strcmp(cmdBuf, "logout")) {
			//向服务器发送请求命令
			Logout logout;
			strcpy(logout.userName,"CaiYu");
			send(_sock, (const char*)&logout, sizeof(logout), 0);
			//接收服务器返回的消息
			LogoutResult logoutRet;
			recv(_sock, (char*)&logoutRet, sizeof(logoutRet), 0);
			printf("LogoutResult :%d \n", logoutRet.result);
		}
		else {
			printf("收到不支持命令，请重新输入。\n");
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