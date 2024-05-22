#pragma once
#include <vector>
#include <string>
#include <mutex>

class Server
{
	std::mutex mtxprint;
public:
	Server() {};
	std::vector<std::pair<std::string, std::string>> Receivinginformation();
	void handle_get(int client_socket, char* request);
	void handle_post(int client_socket, char* request);
	void print(const std::string& message);
};

