/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:35:09 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/09 10:24:10 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_pipes_child(t_pipes pipes)
{
	dup2(pipes.stdin[0], 0);
	dup2(pipes.stdout[1], 1);
	dup2(pipes.error[1], 2);
	close(pipes.stdin[1]);
	close(pipes.stdout[0]);
	close(pipes.error[0]);
}

void	close_pipes(t_pipes pipes)
{
	close(pipes.stdin[0]);
	close(pipes.stdout[0]);
	close(pipes.error[0]);
	close(pipes.stdin[1]);
	close(pipes.stdout[1]);
	close(pipes.error[1]);
}

t_pipes	init_pipes(void)
{
	t_pipes	pipes;

	pipe(pipes.error);
	pipe(pipes.stdin);
	pipe(pipes.stdout);
	return (pipes);
}
