#include "Server.hpp"

Server	&Server::operator=(const Server &other)
{
	this->configServer = other.configServer;
	this->locations = other.locations;
	this->name = other.name;
	return (*this);
}

bool Server::operator==(Server other)
{
	return (this->name == other.name);
}

Server::Server()
{

}

Server::Server(ConfigFile config) : configServer(config)
{
	name = config.domain;

	std::vector<Location>::iterator it = config.locations.begin();
	std::vector<Location>::iterator itEnd = config.locations.end();

	while (it != itEnd)
	{
		Location &location = *it;
		locations[location] = Server(*location.config);
		it++;
	}
}

std::string	&Server::getName()
{
	return (name);
}

Server::~Server()
{

}

Server &Server::GetLocationServer(string &uri)
{
    map<Location, Server>::iterator     locationsIter = locations.begin();
	map<Location, Server>::iterator     coincidence = locations.end();
	int maxExtLength = -1;


	while (locationsIter != locations.end())
    {
    	if (locationsIter->first.path == uri)
	    {
		    coincidence = locationsIter;
		    break;
	    }
    	string path = locationsIter->first.path;
    	if (path.substr(path.length() - 2) == "/*")
	    {
			if (path.substr(0, path.length() - 2) == uri)
			{
				coincidence = locationsIter;
				break;
			}
	    }
        if (match(uri.c_str() ,path.c_str()))
        {
        	int tmp = locationsIter->first.path.length() - locationsIter->first.path.find_last_of('*');
        	if (tmp > maxExtLength || maxExtLength == -1 || (tmp == maxExtLength && coincidence->first.path.length() < locationsIter->first.path.length())) {
		        coincidence = locationsIter;
		        maxExtLength = tmp;
	        }
        }
        locationsIter++;
    }
	if (coincidence != locations.end()) {
		string path = coincidence->first.path;
		int lastDirIndex = path.find_last_of('/');

		if (lastDirIndex > 0) {
			uri.erase(0, lastDirIndex);
		}
		return coincidence->second;
	}
    return *this;
}

Response Server::getHttpResponse(const sockaddr_in &addr, Request *request, ConfigFile *config)
{
    string message;
    string path;
    Response response;

	if (config->isCGI(path))
	{
		CommonGatewayInterface  cgiRequest(*request, configServer, addr);
		response = cgiRequest.ExecuteCGI(request->file_fd);
		response.isCgi = true;
		return response;
	}
    if (request->query.method == "PUT" || request->query.method == "POST") {
        path = config->rootDirectory + request->query.address;
        bool file_exists = exists(path);
		int result;


		if (request->file_fd)
			result = file_put_contents(path, request->file_fd, 0666);
		else
			result = file_put_contents(path, request->body, 0666);
		if (result == -1) {
			response.code(404);
		}
		else {
			if (file_exists)
				response.code(204);
			else
				response.code(201);
			response.header("Content-Location", request->query.address);
		}

    }
    else {
        path = configServer.getIndexPath(request->query.address);


	    if (path.empty())
		    return *response.code(404);
	    else if (is_file(path)){
            response.putFile(path);
        }
        else if (config->autoindex)
        {
            vector<string> *dirs = get_dir_content(path);
            string body;
            if (dirs == nullptr)
                return *response.code(500);
            string webPath = "<a href=\"" + request->query.address;
            if (*(--request->query.address.end()) != '/')
                webPath += '/';
            for (unsigned i = 0; i < dirs->size(); i++) {
                body += webPath + (*dirs)[i] + "\">" + (*dirs)[i] + "</a><br>" ;
            }
            response.body(body);
            response.header("Content-Type", "text/html");
            delete dirs;
        }
        else
            return *response.code(404);
    }
    response.attachDefaultHeaders(*config);
    return response;
}
