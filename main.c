/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:36:18 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/04 09:06:43 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: refactor buffer variables to use a const value defined
int	main(int argc, const char *argv[])
{
	t_pipes	previous_pipes;
	if (argc < 4)
		error_handler(0);
	printf("r : %s\n", argv[4]);
	previous_pipes = read_file((char *)argv[1]);
	previous_pipes = parse_setup_cmd((char *)argv[2], previous_pipes);
	previous_pipes = parse_setup_cmd((char *)argv[3], previous_pipes);
	write_file((char *)argv[4], previous_pipes);
	close_pipes(previous_pipes);
}

void	write_file(char *file_name, t_pipes pipes)
{
	char	buffer[101];
	int		file_fd;
	int		qty_read;

	close(pipes.stdout[1]);
	file_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT , 0664);
	if (file_fd == -1)
	 	error_handler(2);
	qty_read = read(pipes.stdout[0], buffer, 100);
	while (qty_read)
	{
		write(file_fd, buffer, qty_read);
		buffer[qty_read] = 0;
		printf("write to file: %d\n", qty_read);
		qty_read = read(pipes.stdout[0], buffer, 100);
	}
	close(file_fd);
}

t_pipes	read_file(char *file_name)
{
	t_pipes	pipes;
	char	buffer[101];
	int		file_fd;
	int		qty_read;

	file_fd = open(file_name, O_RDONLY);
	// TODO: test which error it throws and maybe print the file name
	if (file_fd == -1)
		error_handler(2);
	pipes = init_pipes();
	printf("File path: %s \n", file_name);
	qty_read = read(file_fd, buffer, 100);
	while (qty_read)
	{
		write(pipes.stdout[1], buffer, qty_read);
		qty_read = read(file_fd, buffer, 100);
	}
	close(file_fd);
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

char	*find_path(char *command)
{
	const char	*possible_paths[3] = {"/usr/bin/", "/usr/local/bin/", NULL};
	char		*path;
	int			i;

	path = ft_strjoin(possible_paths[0], command);
	i = 1;
	while (access(path, F_OK) && possible_paths[i])
	{
		printf("path not found: %s \n", path);
		free(path);
		path = ft_strjoin(possible_paths[i++], command);
	}
	if (!access(path, F_OK))
		printf("path found: %s \n", path);
	else
		error_handler(5);
	return (path);
}

void	exec_command(t_pipes pipes, char **args)
{
	pid_t	child;
	char	*command;

	command = find_path(args[0]);
	// TODO: error handling for fork
	child = fork();
	if (child == 0)
	{
		setup_pipes_child(pipes);
		execve(command, &args[0], NULL);
	}
	wait(NULL);
	free(command);
}

void	error_handler(int err_id)
{
	if (err_id == 0)
		ft_putendl_fd("To few arguments.", 2);
	else if (err_id == 1)
		ft_putendl_fd("To many arguments.", 2);
	else if (err_id == 2)
		perror("");
	else if (err_id == 3)
		ft_putendl_fd("File dosn't exist.", 2);
	else if (err_id == 4)
		ft_putendl_fd("Fail to fork.", 2);
	else if (err_id == 5)
		ft_putendl_fd("Command not found.", 2);
	exit(EXIT_FAILURE);
}
