/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:36:18 by nthomas-          #+#    #+#             */
/*   Updated: 2022/04/07 06:44:55 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipes	previous_pipes;
	char	**path;
	int		i;
	int		here_doc;

	if (argc < 5)
		error_handler(0);
	i = 1;
	here_doc = check_doc(argv[1]);
	if (here_doc)
		previous_pipes = read_args_eof(argv[2], argv, &i); //TODO check if i is being altered properly
	else
		previous_pipes = read_file(argv[1]);
	printf("%s main i\n", argv[i] );
	path = parse_path(envp);
	printf("%d i ; %d argc \n", i, argc);
	while (++i < argc - 1)
		previous_pipes = setup_cmd(argv[i], previous_pipes, envp, path);
	free_2darray(path);

	if (here_doc)
		write_file_append(argv[i], previous_pipes);
	else
		write_file(argv[i], previous_pipes);
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
