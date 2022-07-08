/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:52:09 by nthomas-          #+#    #+#             */
/*   Updated: 2022/06/29 13:52:10 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	program_loop(int argc, char **argv, t_data *data);
void	here_doc_loop(int argc, char **argv, t_data *data);
int		exec_command(char *command, char **args, t_data *data);

void	push_pipes(t_data *data);
t_pipes	init_pipes(void);
void	close_pipes(t_pipes pipes);
void	setup_pipes_child(t_pipes pipes);
int		push_input_pipe(int input, t_data *data);

char	**parse_path(char **envp);
int		check_doc(char *arg);
void	free_2darray(char **array);
void	error_handler(int err_id, t_data *data);
char	*find_path(char *command, t_data *data);
int		check_child_err(t_pipes pipes);

void	read_file(char *file_name, t_data *data);
void	write_file(char *file_name, int flags, t_data *data);
int		read_eof(char *eof);

#endif // PIPEX_H
