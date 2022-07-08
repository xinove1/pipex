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
	if (access(path, F_OK))
	{
		ft_putstr_fd("Command not found:", 2);
		ft_putendl_fd(command, 2);
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
