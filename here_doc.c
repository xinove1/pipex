/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:20:48 by nthomas-          #+#    #+#             */
/*   Updated: 2022/07/13 10:20:49 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*read_eof(char *eof)
{
	char	*line;
	t_list	*list;

	ft_putstr_fd("\nhere_doc>", 1);
	line = get_next_line(0);
	list = ft_lstnew(line);
	while (line)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(0);
		if (!ft_strncmp(eof, line, ft_strlen(eof)))
			break ;
		ft_lstadd_back(&list, ft_lstnew(line));
	}
	if (line)
		free(line);
	return (list);
}

void	here_doc_loop(int argc, char **argv, t_data *data)
{
	int		i;
	t_list	*lines;

	lines = read_eof(argv[2]);
	while (push_pipe(lines, data))
	{
		i = 2;
		while (++i < argc - 1)
		{
			error_handler(0, NULL, 0);
			if (i == argc - 2)
			{
				if (!open_file(argv[i + 1], WAC_FLAGS, &data->pipes.out[1]))
					break ;
			}
			else
				pipe(data->pipes.out);
			prep_command(argv[i], data);
			close(data->pipes.in[0]);
			close(data->pipes.out[1]);
			data->pipes.in[0] = data->pipes.out[0];
		}
	}
	ft_lstclear(&lines, free);
}

int	push_pipe(t_list *lines, t_data *data)
{
	static t_list	*i = NULL;
	static int		flag = 0;

	if (!i && !flag)
	{
		i = lines;
		flag = 1;
	}
	else if (!i && flag)
		return (0);
	pipe(data->pipes.in);
	write(data->pipes.in[1], i->content, ft_strlen(i->content));
	close(data->pipes.in[1]);
	i = i->next;
	return (1);
}
