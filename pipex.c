#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		here_doc;

	if (argc < 5)
		error_handler(0, NULL);
	data.envp = envp;
	data.paths = parse_path(envp);
	data.previous = init_pipes();
	data.pipes = init_pipes();
	here_doc = check_doc(argv[1]);
	if (here_doc)
		here_doc_loop(argc, argv, &data);
	else
		program_loop(argc, argv, &data);
	free_2darray(data.paths);
	return (EXIT_SUCCESS);
}

void	here_doc_loop(int argc, char **argv, t_data *data)
{
	int		i;
	char	**args;
	char	*command;
	int		input;

	input = read_eof(argv[2]);
	while (push_input_pipe(input, data))
	{
		i = 2;
		while (i++ < argc - 2)
		{
			args = ft_split(argv[i], ' ');
			command = find_path(args[0], data);
			if (!command)
			{
				free_2darray(args);
				error_handler(-1, data);
			}
			exec_command(command, args, data);
			check_child_err(data->pipes);
			push_pipes(data);
		}
		write_file(argv[i], O_WRONLY | O_APPEND | O_CREAT, data);
	}
	close_pipes(data->previous);
}

void	program_loop(int argc, char **argv, t_data *data)
{
	int		i;
	char	**args;
	char	*command;

	i = 1;
	read_file(argv[1], data);
	while (i++ < argc - 2)
	{
		args = ft_split(argv[i], ' ');
		command = find_path(args[0], data);
		if (!command)
		{
			free_2darray(args);
			error_handler(-1, data);
		}
		exec_command(command, args, data);
		check_child_err(data->pipes);
		push_pipes(data);
	}
	write_file(argv[i], O_WRONLY | O_TRUNC | O_CREAT, data);
	close_pipes(data->previous);
	close_pipes(data->pipes);
}

int	exec_command(char *command, char **args, t_data *data)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		setup_pipes_child(data->pipes);
		execve(command, &args[0], data->envp);
	}
	else if (child < 0)
	{
		free_2darray(args);
		error_handler(1, data);
	}
	wait(NULL);
	free(command);
	free_2darray(args);
	return (0);
}
