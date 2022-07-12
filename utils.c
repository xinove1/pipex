/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:11 by nthomas-          #+#    #+#             */
/*   Updated: 2022/07/12 10:48:12 by nthomas-         ###   ########.fr       */
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

char	*find_path(char *command, t_data *data)
{
	char	*path;
	char	*tmp;
	int		i;

	tmp = ft_strjoin("/", command);
	path = ft_strjoin(data->paths[0], tmp);
	i = 1;
	while (access(path, F_OK) && data->paths[i])
	{
		free(path);
		path = ft_strjoin(data->paths[i++], tmp);
	}
	if (access(path, F_OK | X_OK))
	{
		if (access(path, F_OK))
			error_handler(3, command, 127);
		else
			error_handler(2, path, 126);
		free(path);
		path = NULL;
	}
	free(tmp);
	return (path);
}

int	read_eof(char *eof)
{
	int		pipe_line[2];
	char	*line;

	pipe(pipe_line);
	ft_putstr_fd("\nhere_doc>", 1);
	line = get_next_line(0);
	while (ft_strncmp(eof, line, ft_strlen(eof)))
	{
		write(pipe_line[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(pipe_line[1]);
	return (pipe_line[0]);
}

int	error_handler(int err_id, char *str, int new_exit)
{
	static int	exit_code = 0;

	if (err_id == 1)
		ft_putendl_fd("Fail to fork.", 2);
	else if (err_id == 2)
		perror(str);
	else if (err_id == 3)
	{
		ft_putstr_fd("Command not found:", 2);
		ft_putendl_fd(str, 2);
	}
	if (new_exit >= 0)
		exit_code = new_exit;
	return (exit_code);
}
