#include "pipex.h"

void	pipex_loop(int argc, char **argv, t_data *data);
int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 5)
	{
		ft_putendl_fd("To few arguments.", 2);
		exit(EXIT_FAILURE);
	}
	else if ( argc > 5)
	{
		ft_putendl_fd("To many arguments.", 2);
		exit(EXIT_FAILURE);
	}
	data.envp = envp;
	data.paths = parse_path(envp);
	pipex_loop(argc, argv, &data);
	free_2darray(data.paths);
	return (EXIT_SUCCESS);
}

void	pipex_loop(int argc, char **argv, t_data *data)
{
	int		i;
	int		write_flags;

	write_flags = O_WRONLY | O_TRUNC | O_CREAT;
	data->pipes.in[0] = open(argv[1], O_RDONLY);
	if (data->pipes.in[0] < 0)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(argv[1], 2);
		data->pipes.in[0] = 0;
		i = 2;
	}
	else
		i = 1;
	while (++i < argc - 1)
	{
		if (i == argc - 2)
			data->pipes.out[1] = open(argv[i + 1], write_flags, 0664);
		else
			pipe(data->pipes.out);
		prep_command(argv[i], data);
		close(data->pipes.in[0]);
		close(data->pipes.out[1]);
		data->pipes.in[0] = data->pipes.out[0];
	}
}

void	prep_command(char *command, t_data *data)
{
	char	**args;
	char	*path;

	args = ft_split(command, ' ');
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

	child = fork();
	if (child == 0)
	{
		ft_printf("command %s \n", args[0]);
		dup2(data->pipes.out[1], 1);
		dup2(data->pipes.in[0], 0);
		execve(args[0], &args[0], data->envp);
	}
	else if (child < 0)
		ft_putendl_fd("Fail to fork.", 2);
	wait(NULL);
}
