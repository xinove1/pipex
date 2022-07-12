/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:36:00 by nthomas-          #+#    #+#             */
/*   Updated: 2022/07/12 18:36:04 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_substr(char **args)
{
	int		head;
	int		tail;
	char	*tmp;

	find_head_tail(args, &head, &tail);
	if (head == 0 && tail == 0)
		return (args);
	if (head != tail)
		cat_args(args, head, tail);
	tmp = ft_strtrim(args[head], "'");
	free(args[head]);
	args[head] = tmp;
	return (args);
}

void	cat_args(char **args, int head, int tail)
{
	int		i;
	char	*tmp;

	i = head;
	while (args[i] && i < tail)
	{
		tmp = ft_strjoin_triple(args[head], " ", args[i + 1]);
		free(args[head]);
		free(args[i + 1]);
		args[head] = tmp;
		i++;
	}
	i = head;
	while (++i <= tail)
		args[i] = NULL;
	i = tail + 1;
	head++;
	while (args[i])
	{
		args[head] = args[i];
		args[i] = NULL;
		i++;
		head++;
	}
}

char	*ft_strjoin_triple(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	return (str);
}

void	find_head_tail(char **args, int *head, int *tail)
{
	int	i;

	i = -1;
	*head = 0;
	*tail = 0;
	while (args[++i])
	{
		if (args[i][0] == '\'' && *head == 0)
			*head = i;
		if (args[i][ft_strlen(args[i]) - 1] == '\'')
			*tail = i;
	}
}
