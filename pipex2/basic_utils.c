/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:51:40 by nthomas-          #+#    #+#             */
/*   Updated: 2022/06/29 13:51:42 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2darray(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**parse_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}

int	check_doc(char *arg)
{
	if (!ft_strncmp(arg, "here_doc", 8))
		return (1);
	else
		return (0);
}

void	error_handler(int err_id, t_data *data)
{
	if (err_id == 0)
		ft_putendl_fd("To few arguments.", 2);
	else if (err_id == 1)
		perror("");
	else if (err_id == 2)
		ft_putendl_fd("Fail to fork.", 2);
	else if (err_id == 3)
		ft_putendl_fd("Command not found.", 2);
	if (data)
		free_2darray(data->paths);
	exit(EXIT_FAILURE);
}

char	*find_path(char *command, t_data *data)
{
	char	*path;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(data->paths[0], "/");
	path = ft_strjoin(tmp, command);
	i = 1;
	while (access(path, F_OK) && data->paths[i])
	{
		free(path);
		free(tmp);
		tmp = ft_strjoin(data->paths[i++], "/");
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

int	check_child_err(t_pipes pipes)
{
	char	buffer[101];
	int		qty_read;

	close(pipes.err[1]);
	qty_read = read(pipes.err[0], buffer, 100);
	if (qty_read == 0)
		return (0);
	while (qty_read > 0)
	{
		buffer[qty_read] = 0;
		ft_putendl_fd(buffer, 2);
		qty_read = read(pipes.err[0], buffer, 100);
	}
	return (1);
}
