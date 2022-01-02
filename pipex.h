/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 00:13:02 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/02 09:23:26 by nthomas-         ###   ########.fr       */
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
	int	stdin[2];
	int	error[2];
	int	stdout[2];
} t_pipes;

void	exec_command(t_pipes pipes, char **args);
void	setup_pipes_child(t_pipes pipes);
t_pipes	parse_setup_cmd(char *arg, t_pipes stdin);
void	close_pipes(t_pipes pipes);
char	*find_path(char *command);
t_pipes	read_file(char *file_name);
t_pipes	init_pipes(void);
void	write_file(char *file_name, t_pipes pipes);

#endif
