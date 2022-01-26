#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define SIZE_OF_QUEUE 10
#define EXIT_FAIL 1
#define PORT 8080
#define BUFFER_SIZE 30000

// int main(int argc, char** argv)
// {
//     int status;
//     ConfigurationFile *config;
//     if (argc == 1)
//         config = getConfig("Default.conf");
//     else
//     {
//         std::string filename(argv[1]);
//         config = getConfig(filename);
//     }

//     //TO DO
//     std::cout "Got config in main. Server: " config get server info << std::endl;

//     // socket initialization
//     std::list<Websocket*> sockets;
//     Websockets* s;
//     for (std::vector<ConfigurationServer>::iterator itb = config->)

// }
int main(int argc, char const *argv[])
{
    int server_socket, client_socket;
    long len_read;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    Request req;
    Response resp;
    ConfigFile conf;

    // Reading conf file
    ParseConf(argv[1]);

    // Creating socket file descriptor
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::perror("In socket");
        exit(EXIT_FAIL);
    }

    // Set up the sockaddr structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(localIP);
    address.sin_port = htons(PORT);
    // memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // Bind the listening socket
    if (bind(server_socket, (struct sockaddr* )&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAIL);
    }

    // Creating the queue for the incoming connections
    // LISTEN MODE
    if (listen(server_socket, SIZE_OF_QUEUE) < 0)
    {
        perror("In listen");
        exit(EXIT_FAIL);
    }

    while(1)
    {
        printf("\nWaiting for new connection\n\n");
    
        // Accepting incoming connation
        if ((client_socket = accept(server_socket, (struct sockaddr* )&address, (socklen_t* )&addrlen)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAIL);
        }
        
        // Reading 
        char buffer_to_read[BUFFER_SIZE] = {0};
        req.body = buffer_to_read;

        len_read = recv(client_socket, buffer_to_read, BUFFER_SIZE);
    
        // Обработка пришедшего сообщения
        char* buffer_to_send[BUFFER_SIZE] = ParseRequest(req, resp);
        // resp.body = buffer_to_send;

        // resp->get_msg() response сообщение
        // resp->length() длина сообщения для отправки
        send(client_socket, resp->get_msg(), strlen(resp->length()));
        std::cout << "Message sent" << std:endl;
        close(client_socket);
    }
    return 0;
}
