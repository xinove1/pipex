#include "pipex.h"

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
