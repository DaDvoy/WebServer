#include "ServerLaunch.hpp"

ServerLaunch::~ServerLaunch()
{
}

ServerLaunch::ServerLaunch(list<ConfigFile> &config)
{
	this->config = config;
}

bool	ServerLaunch::ExecuteServers()
{	
	if (config.size() == 0)
		return false;
	InitializeServers();
    int countUsers = 10;
    std::cout << "------------------config-------------------\n";

	std::cout << "server_name: " << config.begin()->domain << std::endl;
	std::cout << "port: " << config.begin()->port << std::endl;
	std::cout << "error_page: " << config.begin()->errorPage << std::endl;
	std::cout << "root: " << config.begin()->rootDirectory << std::endl;
	std::cout << "client_max_body_size: " << config.begin()->limitClientBodySize << std::endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int server_fd, fd_send;
    sockaddr_in address;
    int addrlen = sizeof(address);

    std::string  hello_there("HTTP/1.1 200 OK\r\n"
                             "content-encoding: gzip\r\n"
                             "content-length: 80000\r\n"
                             "content-type: text/html\r\n"
                             "server: GuluGulu\r\n");
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config.begin()->port);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, countUsers) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((fd_send = accept(server_fd, (sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }


        std::cout << "\n+++++++ Starting request parser ++++++++\n\n";
        RequestParser requestParser(fd_send); // старт парсера запроса
        
        std::cout << "\n+++++++ Query string ++++++++\n\n";

        Request newRequest = requestParser.request; //так можно присвоить новый реквест объекту реквест для удобства
        std::cout << "query_string: " << newRequest.query.query_string << std::endl;
        std::cout << "method: " << newRequest.query.method << std::endl;
        std::cout << "address: " << newRequest.query.address << std::endl;
        std::cout << "protocol: " << newRequest.query.protocol << std::endl << std::endl;

        std::cout << "\n+++++++ HEADERS ++++++++\n\n";


        std::map<std::string, std::string>::iterator it = requestParser.request.head.begin();
        std::map<std::string, std::string>::iterator it_end = requestParser.request.head.end();

        while (it != it_end) // вывод заголовков
        {
             std::cout << it->first << ": " <<  " " << it->second << std::endl;
            it++;
        }
        std::cout << "\n+++++++ BODY ++++++++\n\n";
        std::cout << newRequest.body << std::endl; 
        std::cout << "\n\n+++++++ Ending request parser ++++++++\n";

        std::cout << "+++++++++++++++++++++++++\n";
        Response resp(requestParser.request);
        resp.buildResponse();
        std::cout << "+++++++++++++++++++++++++\n";

       // todo: ready string for sent write(fd_send , resp.getResponse().c_str()  , strlen(resp.getResponse().c_str()));
//        (void)env;
        
        // CommonGatewayInterface *cgi = new CommonGatewayInterface("cgi/test.cgi", newRequest, address, (*config.begin()));
        // cgi->ExecuteCGI();
        std::cout << "host: " << newRequest.head["Host"] << std::endl;
        // hello_there = (char *)cgi->ExecuteCGI().c_str();
        send(fd_send, hello_there.c_str(), hello_there.length(), 0);
        printf("------------------Response sent-------------------\n");
        close(fd_send);
    }
}

void	ServerLaunch::InitializeServers()
{

}
