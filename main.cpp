#include "./src/includes.hpp"
#include "./src/ConfigParser.hpp"
#include "./src/RequestParser.hpp"
#include "./src/CommonGatewayInterface.hpp"
#include "./src/ConfigParser.hpp"
#include <map>

#define PORT 8080

// int main(int argc, char  *argv[], char *env[])
// {
// 		if (argc != 2)
// 	{
// 		std::cerr << "Wrong params!\n";
// 		std::cerr << "help: ./gulugulu src/config/Default.conf\n";
// 		return (-1);
// 	}	
// 	ConfigParser parsing;
//     list<ConfigFile> Configs = parsing.GetServerConfigs(argv[1]);
//     int countUsers = 10;
//     std::cout << "------------------Configs-------------------\n";

// 	std::list<Configs>::iterator config = parsing.GetConfig().begin();
// 	std::cout << "server_name: " << config->server_name << std::endl;
// 	std::cout << "port: " << config->port << std::endl;
// 	std::cout << "error_page: " << config->error_page << std::endl;
// 	std::cout << "root: " << config->root << std::endl;
// 	std::cout << "client_max_body_size: " << config->client_max_body_size << std::endl;
// 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     int server_fd, new_socket;
//     sockaddr_in address;
//     int addrlen = sizeof(address);
    
//     std::string hello_there = "Hello from server";
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("In socket");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(config->port);

//     memset(address.sin_zero, '\0', sizeof address.sin_zero);

//     if (bind(server_fd, (sockaddr *)&address, sizeof(address))<0)
//     {
//         perror("In bind");
//         exit(EXIT_FAILURE);
//     }
//     if (listen(server_fd, countUsers) < 0)
//     {
//         perror("In listen");
//         exit(EXIT_FAILURE);
//     }
//     while(1)
//     {
//         printf("\n+++++++ Waiting for new connection ++++++++\n\n");
//         if ((new_socket = accept(server_fd, (sockaddr *)&address, (socklen_t*)&addrlen))<0)
//         {
//             perror("In accept");
//             exit(EXIT_FAILURE);
//         }


//         std::cout << "\n+++++++ Starting request parser ++++++++\n\n";
//         RequestParser requestParser(new_socket); // старт парсера запроса
        
//         std::cout << "\n+++++++ Query string ++++++++\n\n";

//         Request newRequest = requestParser.request; //так можно присвоить новый реквест объекту реквест для удобства

//         std::cout << "query_string: " << newRequest.query.query_string << std::endl;
//         std::cout << "method: " << newRequest.query.method << std::endl;
//         std::cout << newRequest.query.address << std::endl;
//         std::cout << newRequest.query.protocol << std::endl << std::endl;

//         std::cout << "\n+++++++ HEADERS ++++++++\n\n";

//         std::map<std::string, std::string>::iterator it = newRequest.head.begin(); //для итерации по мапе заголовков нужно использовать итераторы
//         std::map<std::string, std::string>::iterator it_end = newRequest.head.end();

//         std::cout << "\n+++++++ BODY ++++++++\n\n";
//         std::cout << newRequest.body << std::endl;        
//         while (it != it_end) // вывод заголовков
//         {
//             std::cout << it->first << ": " << it->second << std::endl;
//             it++;
//         }
//         std::cout << "\n\n+++++++ Ending request parser ++++++++\n";
//         (void)env;
//         //CommonGatewayInterface *cgi = new CommonGatewayInterface("cgi/test.cgi", env, newRequest, address, *config);
//         //cgi->ExecuteCGI(new_socket);
//         //std::cout << "host: " << newRequest.head["Host"] << std::endl;
//         // hello_there = (char *)cgi->ExecuteCGI().c_str();
//         write(new_socket, hello_there.c_str(), strlen(hello_there.c_str()));
//         printf("------------------Response sent-------------------\n");
//         close(new_socket);
//     }
//   return 0;
// }


int main(int argc, char const *argv[])
{
    ConfigParser parser;

    if (argc != 2)
        return (-1);
    list<ConfigFile> Configs = parser.GetServerConfigs(argv[1]);

    std::cout << Configs.begin()->port << std::endl;
    std::cout << Configs.begin()->index << std::endl;
    std::cout << Configs.begin()->ip << std::endl;
    std::cout << Configs.begin()->errorPage << std::endl;
    std::cout << Configs.begin()->limitClientBodySize << std::endl;
    std::cout << Configs.begin()->autoindex << std::endl;
    return (0);
}
