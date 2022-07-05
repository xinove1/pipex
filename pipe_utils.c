/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:51:58 by nthomas-          #+#    #+#             */
/*   Updated: 2022/06/29 13:51:59 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_pipes_child(t_pipes pipes)
{
	dup2(pipes.in[0], 0);
	dup2(pipes.out[1], 1);
	dup2(pipes.err[1], 2);
	close(pipes.in[1]);
	close(pipes.out[0]);
	close(pipes.err[0]);
}

void	close_pipes(t_pipes pipes)
{
	close(pipes.in[0]);
	close(pipes.out[0]);
	close(pipes.err[0]);
	close(pipes.in[1]);
	close(pipes.out[1]);
	close(pipes.err[1]);
}

t_pipes	init_pipes(void)
{
	t_pipes	pipes;

	//TODO refactor pipes usage
	pipe(pipes.err);
	pipe(pipes.in);
	pipe(pipes.out);
	return (pipes);
}

void	push_pipes(t_data *data)
{
	close_pipes(data->previous);
	data->previous = data->pipes;
	data->pipes = init_pipes();
	dup2(data->previous.out[0], data->pipes.in[0]);
	close(data->previous.out[1]);
}

int	push_input_pipe(int input, t_data *data)
{
	char	buffer[2];
	int		qty_read;

	close_pipes(data->pipes);
	data->pipes = init_pipes();
	qty_read = read(input, buffer, 1);
	while (qty_read > 0)
	{
		write(data->pipes.in[1], buffer, 1);
		if (buffer[0] == '\n')
		{
			close(data->pipes.in[1]);
			return (1);
		}
		qty_read = read(input, buffer, 1);
	}
	close(data->pipes.in[1]);
	return (0);
}
