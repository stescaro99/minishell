/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:45:13 by stescaro          #+#    #+#             */
/*   Updated: 2024/04/18 09:42:31 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	short	is_pipe(char *line)
{
	int	pip;
	int	maj;
	int	min;

	min = find_char(line, '<');
	maj = find_char(line, '>');
	pip = find_char(line, '|');
	if (pip < 0 && min < 0 && maj < 0)
		return (0);
	return (1);
}

short	set_logic(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '|' && line[i + 1] == '|')
		return (1);
	if (line[i] == '&' && line[i + 1] == '&')
		return (2);
	if (line[i] == ';')
		return (-1);
	return (0);
}

short	find_type(char *line)
{
	int	i;

	i = 0;
	if (ft_strncmp(line, "exit", 4) == 0 && is_space(line[4]))
		return (-1);
	else if (is_pipe(line))
		return (1);
	else if (ft_strncmp(&line[i], "echo", 4) == 0 && is_space(line[4 + i]))
		return (2);
	else if (ft_strncmp(&line[i], "cd", 2) == 0 && is_space(line[2 + i]))
		return (3);
	else if (ft_strncmp(&line[i], "pwd", 3) == 0 && is_space(line[3 + i]))
		return (4);
	else if (ft_strncmp(&line[i], "export", 6) == 0 && is_space(line[6 + i]))
		return (5);
	else if (ft_strncmp(&line[i], "unset", 5) == 0 && is_space(line[5 + i]))
		return (6);
	else if (ft_strncmp(&line[i], "env", 3) == 0 && is_space(line[3 + i]))
		return (7);
	else if (find_char(line, '=') > 0 && !is_space(line[find_char(line, '=')
				- 1]) && !is_space(line[find_char(line, '=') + 1]))
		return (8);
	return (0);
}
