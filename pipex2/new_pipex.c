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
    t_pipes		previous;
    t_pipes		pipes;
    char		**paths;
    char		**envp;
}	t_data;

int	main(int argc, char *argv[], char *envp[])
{

}
