#include "./src/includes.hpp"
#include "./src/ConfigParser.hpp"
#include "./src/RequestParser.hpp"

#define PORT 8080

int main(int argc, char  *argv[])
{
		if (argc != 2)
	{
		std::cerr << "Wrong params!\n";
		std::cerr << "help: ./gulugulu src/config/Default.conf\n";
		return (-1);
	}	
	ConfigParser parsing(argv[1]);

	std::list<Configs>::iterator config = parsing.GetConfig().begin();
	std::cout << "server_name: " << config->server_name << std::endl;
	std::cout << "port: " << config->port << std::endl;
	std::cout << "error_page: " << config->error_page << std::endl;
	std::cout << "root: " << config->root << std::endl;
	std::cout << "client_max_body_size: " << config->client_max_body_size << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    std::string hello = "Hello from server";
    char hello_there[18] = "Hello from server";
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config->port);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        RequestParser requestParser(new_socket);
        write(new_socket , hello_there , strlen(hello_there));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
  return 0;
}
