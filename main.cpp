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
    char hello_there[] =    "HTTP/1.1 200 OK\n"
                            "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
                            "Server:Gulu Gulu 2.0\n"
                            "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
                            "Content-Length: 2500\n"
                            "Content-Type: text/html\n"
                            "Connection: Closed\n\n"

"<html>\n"
"<head>\n"
"<meta charset=UTF-8\">\n"
"<meta name=\"color-scheme\" content=\"light dark\">\n"


"<style>\n"
"<body> {"
"-webkit-font-smoothing: antialiaseed;\n"
"font-size: 100%;\n"
"margin: 0;\n"
"}\n"

".content {\n"
"background-color: rgb(0, 139, 139);\n"       //76, 146, 143
"color: rgb(255, 245, 238);\n"
//"font-size: calc(100% - 2px);\n"
"line-height: calc(100% + 6px);\n"
"min-width: 240px;\n"
"}\n"

"h1 {\n"
"font-size:calc(100% + 8px);\n"
"font-weight: 400;\n"
"line-height: calc(100% + 8px);\n"
"}\n"
        ".take-more-info {\n"
        "color: rgb(240, 230, 140);\n"
        "text-decoration: none;\n"  //если это строку закоментить, то переход на 418 будет подчеркнут
        "}\n"

"@media (max-width: 100px), (max-height: 100px) {\n"
".content {\n"
"font-size: calc(100% - 4px);\n"
"line-height: calc(100% + 6px);\n"
"}\n"
"h1 {\n"
"font-size:calc(100% + 8px);\n"
"font-weight: 400;\n"
"line-height: calc(100% + 8px);\n"
"}\n"
"}\n"

".content {\n"
        "margin-inline-end: auto;\n"
        "margin-inline-start: auto;\n"
        "max-width: 300px;\n"
    "}\n"

    ".icon {\n"
        "margin-inline-end: auto;\n"
        "margin-inline-start: auto;\n"
        "}\n"
"h1 {\n"
"text-aligin: canter;\n"
"}\n"
// format of location
"@media (min-width: 720px) {\n"
        ".icon,\n"
        "h1,\n"
  "#subtitle,\n"
  ".learn-more-button {\n"
            "margin-top: 0.5rem;\n"
        "}\n"

        ".icon,\n"
        "h1,\n"
  "#subtitle,\n"
  ".bulletpoints,\n"
  "#cookie-controls {\n"
  "margin-bottom: 1.5rem;\n"
    "}\n"

    ".content {\n"
    "margin-top: 40px;\n"
        "min-width: 240px;\n"
        "padding: 8px 48px 24px;\n"
    "}\n"




"p {\n"
        "display: block;\n"
        "margin-block-start: 1em;\n"
        "margin-block-end: 1em;\n"
        "margin-inline-start: 0px;\n"
        "margin-inline-end: 0px;\n"
        "}\n"



"</style>\n"



"</head>\n"
"<head>\n"
    "<meta charset=UTF-8\">\n"
    "<meta name=\"color-scheme\" content=\"light dark\">\n"
    "<title>What do you want?</title>\n"
    "</head>\n"
    "<body>\n"
    "<div class=\"content\">\n"
    "<div class=\"icon\" role=\"presentation\" alt></div>\n"
                            "<h1>Mi ne comprene vin</h1>\n"
                            "<p id=\"subtitle\">\n"
                                            "<span>\n"
                                            "Do you now how it works?"
                                            "</span>\n"
/*here are link for "take more info"*/      "<a class=\"take-more-info\" href=\"https://www.google.com/teapot\">take more info</a>\n"
                           "</p>\n"
    "</div>\n"
    "</body>\n"
"</html>\n\n";

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
