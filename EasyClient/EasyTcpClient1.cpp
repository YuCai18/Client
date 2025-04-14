#include"EasyTcpClient.hpp"
#include<thread>

//#pragma comment(lib,"ws2_32.lib")

void cmdThread(EasyTcpClient*  client)
{
	while (true)
	{
		char cmdBuf[256] = {};
		scanf("%s", cmdBuf);

		if (0 == strcmp(cmdBuf, "exit")) {
			client->Close();
			printf("退出cmdThread线程\n");
			break;
		}
		else if (0 == strcmp(cmdBuf, "login")) {
			Login login;
			strcpy(login.userName, "CaiYu");
			strcpy(login.PassWord, "123");
			client->sendData(&login);
		}
		else if (0 == strcmp(cmdBuf, "logout")) {
			Logout logout;
			strcpy(logout.userName, "CaiYu");
			client->sendData(&logout);
		}
		else {
			printf("不支持的命令。\n");
		}
	}
}
int main() {
	EasyTcpClient client;
	client.Connect("127.0.0.1", 4567);

	//EasyTcpClient client2;
	//client.Connect("127.0.0.1", 4568);

	//启动UI线程
	std::thread t1(cmdThread, &client);
	t1.detach(); //与主线程进行一个分离
	//std::thread t2(cmdThread, &client2);
	//t2.detach(); //与主线程进行一个分离


	//while (client.isRun() || client2.isRun())
	while (client.isRun())
	{
		client.OnRun();
		//client2.OnRun();
	}
	client.Close();
	//client2.Close();

	printf("已退出。\n");
	//防止一闪而过
	getchar();
	return 0;
}
