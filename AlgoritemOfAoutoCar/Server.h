#pragma once
#include <vector>
#include <string>
class Server
{
public:
	Server() {};
	std::vector<std::pair<std::string, std::string>> Receivinginformation();
	void handle_get(int client_socket, char* request);
	void handle_post(int client_socket, char* request);
};

