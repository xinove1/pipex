/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:47:03 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/12 19:27:40 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_file(char *file_name, t_pipes pipes)
{
	char	buffer[101];
	int		file_fd;
	int		qty_read;

	close(pipes.stdout[1]);
	file_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
		error_handler(2);
	qty_read = read(pipes.stdout[0], buffer, 100);
	while (qty_read)
	{
		write(file_fd, buffer, qty_read);
		buffer[qty_read] = 0;
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
	if (file_fd == -1)
	{
		ft_putendl_fd(file_name, 2);
		error_handler(2);
	}
	pipes = init_pipes();
	qty_read = read(file_fd, buffer, 100);
	while (qty_read)
	{
		write(pipes.stdout[1], buffer, qty_read);
		qty_read = read(file_fd, buffer, 100);
	}
	close(file_fd);
	return (pipes);
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
		;
	else if (err_id == 4)
		ft_putendl_fd("Fail to fork.", 2);
	else if (err_id == 5)
		ft_putendl_fd("Command not found.", 2);
	exit(EXIT_FAILURE);
}

char	*find_path(char *command, char **bin_paths)
{
	char	*path;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(bin_paths[0], "/");
	path = ft_strjoin(tmp, command);
	i = 1;
	while (access(path, F_OK) && bin_paths[i])
	{
		free(path);
		free(tmp);
		tmp = ft_strjoin(bin_paths[i++], "/");
		path = ft_strjoin(tmp, command);
	}
	if (access(path, F_OK))
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(command, 2);
		free(path);
		path = NULL;
	}
	free(tmp);
	return (path);
}

char	**parse_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}
