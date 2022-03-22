#include "CommonGatewayInterface.hpp"

CommonGatewayInterface::CommonGatewayInterface(std::string const &path, Request &request, sockaddr_in &addr, ConfigFile &config)
{
	this->cgiPath = path + request.query.address;

	FillEnv(request, addr, config);
}

CommonGatewayInterface::CommonGatewayInterface(const CommonGatewayInterface &other)
{
	this->cgiPath = other.cgiPath;
	this->env = other.env;
}

CommonGatewayInterface::~CommonGatewayInterface()
{

}

CommonGatewayInterface &CommonGatewayInterface::operator=(const CommonGatewayInterface &other)
{
	this->cgiPath = other.cgiPath;
	this->env = other.env;
	return (*this);
}

void		CommonGatewayInterface::FillEnv(Request &request, sockaddr_in &addr, ConfigFile &config)
{
	newEnv.push_back("QUERY_STRING=" + request.query.query_string);	
	newEnv.push_back("QUERY_METHOD=" + request.query.method);	
	newEnv.push_back("GATEWAY_INTEFACE=CGI/1.1");
	newEnv.push_back("SERVER_SOFTWARE=*NIX");
	newEnv.push_back("REMOTE_ADDR=" + getIP(addr.sin_addr.s_addr));;
	newEnv.push_back("REMOTE_HOST=" + std::to_string(addr.sin_port));
	newEnv.push_back("SERVER_NAME=" + request.head["Host"]);
	newEnv.push_back("SERVER_PORT=" + std::to_string(config.port));
	newEnv.push_back("SERVER_ADDR=" + config.ip);
	newEnv.push_back("SERVER_PROTOCOL=HTTP/1.1");
	newEnv.push_back("SCRIPT_NAME=" + request.query.address);
	newEnv.push_back("REQUEST_URI=" + request.query.address);
	newEnv.push_back("PATH_INFO=" + request.query.address);
	newEnv.push_back("SCRIPT_FILENAME=" + abs_path(config.rootDirectory + request.query.address));
	newEnv.push_back("PATH_TRANSLATED=" + abs_path(config.rootDirectory + request.query.address));
	
	if (!request.body.empty())
	{
		newEnv.push_back("CONTENT_TYPE=" + request.head["Content-Encoding"]);
		newEnv.push_back("CONTENT_LENGTH=" + to_string(request.body.length()));
	}
	
	for (std::map<std::string, std::string>::iterator it = request.head.begin(); it != request.head.end(); it++)
	{
		newEnv.push_back(ToupperStr(it->first) + "=" + it->second);
	}
}

std::string	CommonGatewayInterface::ExecuteCGI()
{
	pid_t	pid;
	std::string final_string = "";
	char	*argc[2];
	int		res;
	char	*env[newEnv.size()];
	int		pipe_fd[2];

	// std::cout << this->cgiPath << std::endl;
	// std::cerr << access(this->cgiPath.c_str(), 0) << std::endl;
	for (size_t i = 0; i < newEnv.size(); i++)
	{
		env[i] = (char*)newEnv[i].c_str();
	}
	env[newEnv.size()] = nullptr;
	pipe(pipe_fd);
	argc[0] = (char*)this->cgiPath.c_str();
	argc[1] = nullptr;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		if (execve(this->cgiPath.c_str(), argc, env) == -1)
		{
			std::cerr << this->cgiPath.c_str() << " " << errno << std::endl;
			exit(0);
		}
	}

	close(pipe_fd[1]);
	waitpid(pid, &res, 0);

	char *buf = new char[BUFSIZ + 1];
	bzero(buf, BUFSIZ + 1);
	while (read(pipe_fd[0], buf, BUFSIZ))
		final_string += buf;
	close(pipe_fd[0]);

	return (final_string);
}
