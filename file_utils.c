#include "pipex.h"

void	write_file(char *file_name, int flags, t_data *data)
{
	char	buffer[101];
	int	file_fd;
	int	qty_read;

	file_fd = open(file_name, flags, 0664); //TODO search what 0664 file permission is
	if (file_fd == -1)
		error_handler(1, data);
	qty_read = read(data->pipes.in[0], buffer, 100);
	while (qty_read)
	{
		write(file_fd, buffer, qty_read);
		buffer[qty_read] = 0;
		qty_read = read(data->pipes.in[0], buffer, 100);
	}
	close(file_fd);
}

void	read_file(char *file_name, t_data *data)
{
	char	buffer[101];
	int	file_fd;
	int	qty_read;

	file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1)
	{
		ft_putendl_fd(file_name, 2); //TODO check if this is necessary
		error_handler(1, data);
	}
	data->pipes = init_pipes();
	qty_read = read(file_fd, buffer, 100);
	while (qty_read)
	{
		write(data->pipes.in[1], buffer, qty_read);
		qty_read = read(file_fd, buffer, 100);
	}
	close(file_fd);
	close(data->pipes.in[1]);
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
