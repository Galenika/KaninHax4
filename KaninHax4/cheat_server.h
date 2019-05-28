#pragma once
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

namespace hack_server
{
	SOCKET client_socket;
	SOCKET server_socket;

	int number_of_connections = 0; 

	void shutdown_server()
	{
		shutdown(server_socket, SD_BOTH);
		shutdown(client_socket, SD_BOTH);

		closesocket(server_socket);
		closesocket(client_socket);
		WSACleanup();
	}

	void wait_for_connection(const char* client_ip)
	{
		WSAData wsa_data;
		auto dll_version = MAKEWORD(2, 2);
		if (WSAStartup(dll_version, &wsa_data) != 0)
		{
			std::cout << "startup failed!" << std::endl;
			return;
		}
		SOCKADDR_IN addr;
		int addr_lenght = sizeof(addr);
		inet_pton(AF_INET, client_ip, &addr.sin_addr.S_un.S_addr);
		addr.sin_port = htons(9128);
		addr.sin_family = AF_INET;

		server_socket = socket(AF_INET, SOCK_STREAM, NULL);
		bind(server_socket, (sockaddr*)&addr, addr_lenght);
		listen(server_socket, SOMAXCONN);
		client_socket = accept(server_socket, (SOCKADDR*)&addr, &addr_lenght);

		if (client_socket != 0)
		{
			std::cout << "client connected!" << std::endl;
			number_of_connections++;
			std::string motd_string = "motd";
			auto str_size = motd_string.size();
			send(client_socket, (char*)&str_size, sizeof(int), NULL);
			send(client_socket, motd_string.c_str(), motd_string.size(), NULL);
		}
		else
		{
			std::cout << "client failed to connect!" << std::endl;
			closesocket(client_socket);
			closesocket(server_socket);
		}
	}
	
	void server_print(std::string msg)
	{
		if (number_of_connections) 
		{
			int str_size = msg.size();
			int ret = 0;
			ret = send(client_socket, (char*)&str_size, sizeof(int), NULL);
			ret = send(client_socket, msg.c_str(), str_size, NULL);
			if (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET)
			{
				std::cout << "client disconnected!" << std::endl;
				number_of_connections--;
				shutdown_server();
				return;
			}
		}
	}
}