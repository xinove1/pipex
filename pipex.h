#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# define WTC_FLAGS O_WRONLY | O_TRUNC | O_CREAT
# define WAC_FLAGS O_WRONLY | O_APPEND| O_CREAT
# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_pipes
{
	int	in[2];
	int	out[2];
}	t_pipes;

typedef struct s_data
{
	t_pipes		pipes;
    char		**paths;
    char		**envp;
}	t_data;

char	**parse_path(char **envp);
void	free_2darray(char **array);
int		error_handler(int err_id, char *str, int new_exit);
char	*find_path(char *command, t_data *data);

void	exec_command(char **args, t_data *data);
void	pipex_loop(int argc, char **argv, t_data *data);
void	prep_command(char *command, t_data *data);
int		open_file(char *file, int flags, int *dest);

void	find_head_tail(char **args, int *head, int *tail);
void	cat_args(char **args, int head, int tail);
char	**parse_substr(char **args);
char	*ft_strjoin_triple(char *s1, char *s2, char *s3);
#endif // PIPEX_H
