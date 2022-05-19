#include "pipex_bonus.h"

int		check_doc(char *arg)
{
	if (!ft_strncmp(arg, "here_doc", 8))
		return (1);
	else
		return (0);
}

// REVIEW check if its works
void	write_file_append(char *file_name, t_pipes pipes)
{
	char	buffer[101];
	int		file_fd;
	int		qty_read;

	close(pipes.stdout[1]);
	file_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0664);
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


// Read from argv and return pipe with the stuff
t_pipes	read_args_eof(char *eof, char *argv[], int *i)
{
	t_pipes	pipes;

	pipes = init_pipes();
	*i += 2;
	// REVIEW: read substring? send spaces between args?
	// REVIEW: does the EOF needs to be alone,
	// REVIEW: new lines?
	printf("eof: %s ; i: %d\n", eof, *i);
	while (ft_strncmp(eof, argv[*i], ft_strlen(eof)))
	{
		write(pipes.stdin[1], argv[*i], ft_strlen(argv[*i]));
		write(pipes.stdin[1], " ", 1);
		printf("String written to stdin pipe: %s\n", argv[*i]);
		(*i)++;
	}
	printf("%d read args eof i\n", *i );
	return (pipes);
}
