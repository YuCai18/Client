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
			printf("�˳�cmdThread�߳�\n");
			break;
		}
		else if (0 == strcmp(cmdBuf, "login")) {
			Login login;
			strcpy(login.userName, "CaiYu");
			strcpy(login.PassWord, "123");
			client->SendData(&login);
		}
		else if (0 == strcmp(cmdBuf, "logout")) {
			Logout logout;
			strcpy(logout.userName, "CaiYu");
			client->SendData(&logout);
		}
		else {
			printf("��֧�ֵ����\n");
		}
	}
}

int main() {
	//Windows
	EasyTcpClient client;
	client.Connect("192.168.85.1",4567);
	//MacOS
	//EasyTcpClient client2;
	//client2.Connect("192.168.85.128",4567);
	//Ubuntu
	//EasyTcpClient client3;
	//client3.Connect("192.168.85.129",4567);
	//����UI�߳�
	std::thread t1(cmdThread, &client);
	t1.detach(); 

	//std::thread t2(cmdThread, &client2);
	//t2.detach();

	//std::thread t3(cmdThread, &client3);
	//t3.detach();

	//while (client.isRun() || client2.isRun() || client3.isRun())
	while (client.isRun())
	{
		client.OnRun();
		//client2.OnRun();
		//client3.OnRun();
	}
	client.Close();
	//client2.Close();
	//client3.Close();

	printf("���˳���\n");
	//��ֹһ������
	getchar();
	return 0;
}
