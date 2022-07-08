#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_pipes
{
	int	in[2];
	int	err[2];
	int	out[2];
}	t_pipes;

typedef struct s_data
{
	t_pipes		pipes;
    char		**paths;
    char		**envp;
}	t_data;

char	**parse_path(char **envp);
int		check_doc(char *arg);
void	free_2darray(char **array);
void	error_handler(int err_id, char *str);
char	*find_path(char *command, t_data *data);
int		check_child_err(t_pipes pipes);

void	exec_command(char **args, t_data *data);
void	pipex_loop(int argc, char **argv, t_data *data);
void	prep_command(char *command, t_data *data);
#endif // PIPEX_H
