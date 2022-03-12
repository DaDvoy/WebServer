#include "CommonGatewayInterface.hpp"

CommonGatewayInterface::CommonGatewayInterface(std::string const &path, Request &request, sockaddr_in &addr, ConfigFile &config)
{
	this->cgiPath = path;

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
	std::vector<std::string>	newEnv;

	newEnv.push_back("QUERY_STRING=" + request.query.query_string);	
	newEnv.push_back("QUERY_METHOD=" + request.query.method);	
	newEnv.push_back("GATEWAY_INTEFACE=CGI/1.1");
	newEnv.push_back("SERVER_SOFTWARE=*NIX");
	newEnv.push_back("REMOTE_ADDR=127.0.0.1");
	newEnv.push_back("REMOTE_HOST=" + std::to_string(addr.sin_port));
	newEnv.push_back("SERVER_NAME=" + request.head["Host"]);
	newEnv.push_back("SERVER_PORT=" + std::to_string(config.port));
	newEnv.push_back("SERVER_ADDR=127.0.0.1");
	newEnv.push_back("SERVER_PROTOCOL=HTTP/1.1");
	newEnv.push_back("SCRIPT_NAME=" + request.query.address);
	newEnv.push_back("REQUEST_URI=" + request.query.address);
	newEnv.push_back("PATH_INFO=" + request.query.address);
	// newEnv.push_back("SCRIPT_FILENAME=");
	// newEnv.push_back("PATH_TRANSLATED=");
	
	if (!request.body.empty())
	{
		newEnv.push_back("CONTENT_TYPE=");
		newEnv.push_back("CONTENT_LENGTH=");
	}
	
	for (std::map<std::string, std::string>::iterator it = request.head.begin(); it != request.head.end(); it++)
	{
		newEnv.push_back(ToupperStr(it->first) + "=" + it->second);
	}
	std::cout << "================ENV================\n";
	env[newEnv.size()] = nullptr;
	for (int i = 0; i < (int)newEnv.size(); i++)
		env[i] = (char*)newEnv[i].c_str();
}

std::string	CommonGatewayInterface::ExecuteCGI()
{
	pid_t	pid;
	std::string final_string = "";
	char	*argc[2];
	int		res;
	int		pipe_fd[2];

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
		execve(this->cgiPath.c_str(), argc, env);
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
