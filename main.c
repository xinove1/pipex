#include "pipex.h"

int	main(int argc, const char *argv[])
{
	t_pipes	previous_pipes;
	if (argc < 4)
	{
		ft_putstr_fd("Not enough arguments. \n", 2);
		exit(1);
	}
	printf("r : %s\n", argv[4]);
	previous_pipes = read_file((char *)argv[1]);
	previous_pipes = parse_setup_cmd((char *)argv[2], previous_pipes);
	previous_pipes = parse_setup_cmd((char *)argv[3], previous_pipes);
	write_file((char *)argv[4], previous_pipes);
	close_pipes(previous_pipes);
}

void	write_file(char *file_name, t_pipes pipes)
{
	char	*path;
	char	buffer[101];
	int		file_fd;
	int		qty_read;

	close(pipes.stdout[1]);
	path = ft_strjoin("./", file_name);
	file_fd = open(path, O_WRONLY, O_CREAT, O_TRUNC);
	qty_read = read(pipes.stdout[0], buffer, 100);
	while (qty_read)
	{
		write(file_fd, buffer, qty_read);
		buffer[qty_read] = 0;
		printf("write to file: %d\n", qty_read);
		qty_read = read(pipes.stdout[0], buffer, 100);
	}
	close(file_fd);
	free(path);
}

t_pipes	read_file(char *file_name)
{
	char	*path;
	t_pipes	pipes;
	char	buffer[101];
	int		file_fd;
	int		qty_read;

	path = ft_strjoin("./", file_name);
	if(!access(path, R_OK))
	{
		pipes = init_pipes();
		file_fd = open(path, O_RDONLY);
		printf("File path: %s \n", path);
		qty_read = read(file_fd, buffer, 100);
		while (qty_read)
		{
			write(pipes.stdout[1], buffer, qty_read);
			qty_read = read(file_fd, buffer, 100);
		}
		close(file_fd);
	}
	else
	{
		perror("");
		exit(1);
	}
	free(path);
	return (pipes);
}

t_pipes	parse_setup_cmd(char *arg, t_pipes stdin)
{
	char	**args;
	t_pipes	pipes;
	int		i;

	pipes = init_pipes();
	dup2(stdin.stdout[0], pipes.stdin[0]);
	close_pipes(stdin);
	args = ft_split(arg, ' ');
	exec_command(pipes, args);
	i = -1;
	while(args[++i])
		free(args[i]);
	free(args);
	return (pipes);
}

// TODO: check if !access is the right way of checking the path
char	*find_path(char *command)
{
	const char	*possible_paths[2] = {"/usr/bin/", "/usr/local/bin/"};
	char		*path;
	int			i;

	path = ft_strjoin(possible_paths[0], command);
	i = 1;
	while (access(path, F_OK) && i < 2)
	{
		printf("path not found: %s \n", path);
		free(path);
		path = ft_strjoin(possible_paths[i++], command);
	}
	if (!access(path, F_OK))
		printf("path found: %s \n", path);
	else
		perror("Command not found. \n");
	return (path);
}

void	exec_command(t_pipes pipes, char **args)
{
	pid_t	child;
	char	*command;

	command = find_path(args[0]);
	child = fork();
	if (child == 0)
	{
		setup_pipes_child(pipes);
		execve(command, &args[0], NULL);
	}
	wait(NULL);
	free(command);
}
