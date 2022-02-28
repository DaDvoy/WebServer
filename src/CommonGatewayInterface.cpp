#include "CommonGatewayInterface.hpp"

CommonGatewayInterface::CommonGatewayInterface(std::string const &path, char **env)
{
	this->cgiPath = path;
	this->env = env;
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
