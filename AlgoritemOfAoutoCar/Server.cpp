#include "Server.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <vector>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
std::vector<std::pair<std::string, std::string>> Server::Receivinginformation()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        std::cerr << "Can't initialize Winsock! Quitting" << std::endl;
    }
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        cerr << "Unable to create socket" << endl;
        exit(EXIT_FAILURE);
    }
    // Bind socket to port 5000
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(54000);
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
    {
        cerr << "Unable to bind socket to port" << endl;
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1)
    {
        cerr << "Unable to listen for incoming connections" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Server is listening on port 54000..." << endl;

    // Accept incoming connection
    client_address_len = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
    if (client_socket == -1)
    {
        cerr << "Failed to accept incoming connection" << endl;

    }

    cout << "Accepted new connection from client:%d\n", ntohs(client_address.sin_port);

    // Read HTTP request from client
    char request[1024];
    int length = recv(client_socket, request, sizeof(request), 0);
    std::regex regex("maneuver=([^&]+)&distance=([^&]+)");
    std::smatch match;
    std::vector<std::pair<std::string, std::string>> result;

    std::string message = request;
    while (std::regex_search(message, match, regex)) {
        result.push_back(std::make_pair(match[1].str(), match[2].str()));
        message = match.suffix();
    }

    for (const auto& pair : result)
    {
        std::cout << "[" << pair.first << "," << pair.second << "]" << std::endl;
    }
    // cout<<"the length:" <<length<<endl;
    if (length < 0)
    {
        cout << "Failed to read from client" << endl;
        closesocket(client_socket);
    }
    // cout<< message<<endl;
     // Extract the path from the message
    std::string path = message.substr(message.find_first_of('/') + 1, message.find('?') - message.find_first_of('/') - 1);

    // Extract the query string from the message
    std::string queryString = message.substr(message.find('?') + 1);

    std::map<int, std::string> objects;

    // Parse the query string to extract objects
    std::stringstream ss(queryString);
    std::string token;
    while (std::getline(ss, token, '&')) {
        std::string::size_type pos = token.find('=');
        int key = std::stoi(token.substr(0, pos));
        std::string value = token.substr(pos + 1);
        objects[key] = value;
    }

    // Extract the title of the message
    std::string title = path;

    // Output the title and objects
  //  std::cout << "Title of the message: " << title << std::endl;
 //   std::cout << "Objects:" << std::endl;
    // Determine the HTTP request method
    char http_method[10];
    int i = 0;
    while (request[i] != ' ') {
        http_method[i] = request[i];
        i++;
    }
    http_method[i] = '\0';

    // Determine the URI from the HTTP request
    char uri[1024];
    int j = 0;
    i++;
    while (request[i] != ' ') {
        uri[j] = request[i];
        i++;
        j++;
    }
    uri[j] = '\0';

    //cout<<"Request received: method="<< http_method<<"uri="<< uri<<endl;

    // Route the HTTP request
    if (strcmp(http_method, "GET") == 0) {
        handle_get(client_socket, uri);
    }
    else if (strcmp(http_method, "POST") == 0) {
        handle_post(client_socket, uri);
    }
    else {
        char error_message[] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, error_message, strlen(error_message), 0);
    }

    // Close client socket
    closesocket(client_socket);
    cout << "Connection closed" << endl;
    // Close server socket
    closesocket(server_socket);
    return result;
}

void Server::handle_get(int client_socket, char* request)
{
    if (strcmp(request, "/") == 0) {
        char message[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 77\r\n\r\n<html><body><h1>Welcome to my website</h1></body></html>";
        send(client_socket, message, strlen(message), 0);
    }
    else if (strcmp(request, "/about") == 0) {
        char message[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 72\r\n\r\n<html><body><h1>About me</h1><p>I'm a programmer</p></body></html>";
        send(client_socket, message, strlen(message), 0);
    }
    else {
        char error_message[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 0\r\n\r\n";
        send(client_socket, error_message, strlen(error_message), 0);
    }
}

void Server::handle_post(int client_socket, char* request)
{
    char success_message[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 15\r\n\r\nPost received\n";
    send(client_socket, success_message, strlen(success_message), 0);
}

