/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:34:41 by nthomas-          #+#    #+#             */
/*   Updated: 2022/04/05 10:11:22 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_pipes
{
	int	stdin[2];
	int	error[2];
	int	stdout[2];
}	t_pipes;

int		exec_command(t_pipes pipes, char *command, char **args, char **envp);
void	setup_pipes_child(t_pipes pipes);
t_pipes	setup_cmd(char *arg, t_pipes stdin, char **envp, char **bin_paths);
void	close_pipes(t_pipes pipes);
char	*find_path(char *command, char **bin_paths);
t_pipes	read_file(char *file_name);
t_pipes	init_pipes(void);
void	write_file(char *file_name, t_pipes pipes);
void	error_handler(int err_id);
int		cmd_util(t_pipes pipes, char **args, char **envp, char **bin_paths);
int		check_child_err(t_pipes pipes);
char	**parse_path(char **envp);
void	free_2darray(char **array);
int		check_doc(char *arg);
t_pipes	read_args_eof(char *here_doc, char *argv[], int *i);
void	write_file_append(char *file_name, t_pipes pipes);

#endif
