/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:36:18 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/13 14:57:38 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, const char *argv[], char *envp[])
{
	t_pipes	previous_pipes;
	char	**path;

	if (argc < 5)
		error_handler(0);
	else if (argc > 5)
		error_handler(1);
	previous_pipes = read_file((char *)argv[1]);
	path = parse_path(envp);
	previous_pipes = setup_cmd((char *)argv[2], previous_pipes, envp, path);
	previous_pipes = setup_cmd((char *)argv[3], previous_pipes, envp, path);
	free_2darray(path);
	write_file((char *)argv[4], previous_pipes);
	close_pipes(previous_pipes);
	return (0);
}

t_pipes	setup_cmd(char *arg, t_pipes stdin, char **envp, char **bin_paths)
{
	char	**args;
	t_pipes	pipes;
	int		error;

	pipes = init_pipes();
	dup2(stdin.stdout[0], pipes.stdin[0]);
	close_pipes(stdin);
	args = ft_split(arg, ' ');
	error = cmd_util(pipes, args, envp, bin_paths);
	free_2darray(args);
	if (error)
	{
		free_2darray(bin_paths);
		close_pipes(pipes);
		error_handler(error);
	}
	return (pipes);
}

int	cmd_util(t_pipes pipes, char **args, char **envp, char **bin_paths)
{
	char	*command;
	int		error;

	error = 0;
	command = find_path(args[0], bin_paths);
	if (!command)
		return (3);
	if (exec_command(pipes, command, args, envp))
		error = 4;
	if (check_child_err(pipes))
		error = 3;
	free(command);
	return (error);
}

int	check_child_err(t_pipes pipes)
{
	char	buffer[101];
	int		qty_read;

	close(pipes.error[1]);
	qty_read = read(pipes.error[0], buffer, 100);
	if (qty_read == 0)
		return (0);
	while (qty_read > 0)
	{
		buffer[qty_read] = 0;
		ft_putendl_fd(buffer, 2);
		qty_read = read(pipes.error[0], buffer, 100);
	}
	return (1);
}

int	exec_command(t_pipes pipes, char *command, char **args, char **envp)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		setup_pipes_child(pipes);
		execve(command, &args[0], envp);
	}
	else if (child < 0)
		return (1);
	wait(NULL);
	return (0);
}
