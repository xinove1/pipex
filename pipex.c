/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:04 by nthomas-          #+#    #+#             */
/*   Updated: 2022/07/12 10:48:05 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 5)
	{
		ft_putendl_fd("Too few arguments.", 2);
		exit(EXIT_FAILURE);
	}
	else if (argc > 5 && !BONUS)
	{
		ft_putendl_fd("Too many arguments.", 2);
		exit(EXIT_FAILURE);
	}
	data.envp = envp;
	data.paths = parse_path(envp);
	if (BONUS && !ft_strncmp(argv[1], "here_doc", 8))
		printf("here doc \n");
	else
		pipex_loop(argc, argv, &data);
	free_2darray(data.paths);
	return (error_handler(0, NULL, -1));
}

void	pipex_loop(int argc, char **argv, t_data *data)
{
	int		i;

	i = 1;
	if (!open_file(argv[1], O_RDONLY, &data->pipes.in[0]))
	{
		pipe(data->pipes.in);
		close(data->pipes.in[1]);
		i = 2;
	}
	while (++i < argc - 1)
	{
		error_handler(0, NULL, 0);
		if (i == argc - 2)
		{
			if (!open_file(argv[i + 1], WTC_FLAGS, &data->pipes.out[1]))
				break ;
		}
		else
			pipe(data->pipes.out);
		prep_command(argv[i], data);
		close(data->pipes.in[0]);
		close(data->pipes.out[1]);
		data->pipes.in[0] = data->pipes.out[0];
	}
}

int	open_file(char *file, int flags, int *dest)
{
	int	fd;

	fd = open(file, flags, 0664);
	if (fd < 0)
	{
		error_handler(2, file, 1);
		return (0);
	}
	*dest = fd;
	return (1);
}

void	prep_command(char *command, t_data *data)
{
	char	**args;
	char	*path;

	args = parse_substr(ft_split(command, ' '));
	path = find_path(args[0], data);
	if (!path)
	{
		free_2darray(args);
		return ;
	}
	free(args[0]);
	args[0] = path;
	exec_command(args, data);
	free_2darray(args);
}

void	exec_command(char **args, t_data *data)
{
	pid_t	child;
	int		wstatus;

	child = fork();
	if (child == 0)
	{
		dup2(data->pipes.out[1], 1);
		dup2(data->pipes.in[0], 0);
		execve(args[0], &args[0], data->envp);
	}
	else if (child < 0)
		error_handler(1, NULL, 1);
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		error_handler(0, NULL, WEXITSTATUS(wstatus));
}
