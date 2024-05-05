/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:52:00 by stescaro          #+#    #+#             */
/*   Updated: 2024/05/03 15:20:16 by sfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_no_string(t_line **line, t_echo **echo, int f)
{
	t_echo	*tmp;

	if (!(*line)->line[4 + (f * 3)])
	{
		(void)((f) && printf("\e[38;2;0;0;0m\e[48;2;255;255;255m%%\033[0m"));
		(*line)->exit--;
		printf("\n");
		return (handle_logic(line), 0);
	}
	tmp = *echo;
	while (tmp && tmp->printed)
		tmp = tmp->next;
	if (!tmp && --(*line)->exit < 2)
		return (handle_logic(line), printf("\n"));
	tmp->printed = 1;
	printf("%s%s", tmp->str, &((*line)->line[5 + (f * 3)]));
	(void)((f) && printf("\e[38;2;0;0;0m\e[48;2;255;255;255m%%\033[0m"));
	printf("\n");
	return (handle_logic(line), 0);
}

static	int	find_n(char *line, int *i, int ret)
{
	int	n;

	while (line[*i] && is_space(line[*i]))
		(*i)++;
	if (line[*i] == '$' && line[*i + 1] == '?')
	{
		(*i) += 2;
		return (ret);
	}
	n = ft_atoi(&line[*i]);
	if (line[*i] == '-')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (n);
}

static	char	find_operator(char *line, int *i)
{
	char	operator;

	while (line[*i] && line[*i] != '+' && line[*i] != '-' && line[*i] != '*'
		&& line[*i] != '/' && line[*i] != '%')
		(*i)++;
	operator = line[*i];
	if (operator)
		(*i)++;
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (operator);
}

int	expr_shell(t_line **line, int ret)
{
	int			i;
	long long	res;
	int			n;
	char		operator;

	i = 5;
	res = find_n((*line)->line, &i, ret);
	while ((*line)->line[i])
	{
		operator = find_operator((*line)->line, &i);
		n = find_n((*line)->line, &i, ret);
		if (operator == '+')
			res += n;
		else if (operator == '-')
			res -= n;
		else if (operator == '*')
			res *= n;
		else if (operator == '/' && n != 0)
			res /= n;
		else if (operator == '/' && --(*line)->exit < 2 && printf("expr:"))
			return (handle_logic(line), printf(" division by zero\n") * 0 + 1);
		else if (operator == '%')
			res %= n;
	}
	return (handle_logic(line), (i > 5 && printf("%lld\n", res)) * 0);
}

int	exit_shell(t_line **line, int ret, int ext)
{
	char	*l;
	int		i;
	char	*tmp;
	int		n;

	l = (*line)->line;
	i = 4;
	printf("exit\n");
	while (l[i] && is_space(l[i]))
		i++;
	if (!l[i])
		return (handle_logic(line), ext);
	tmp = ft_substr(&l[i], 0, len_to_first_space(&l[i]));
	n = find_n(l, &i, ret);
	while (n < 0)
		n = 256 + n;
	while (n > 255)
		n = n - 256;
	while (l[i] && is_space(l[i]))
		i++;
	if (l[i] && is_space(l[i]) && printf("exit: too many arguments\n"))
		return (handle_logic(line), free(tmp), 1);
	else if (l[i] && printf("exit: %s: numeric argument required\n", tmp))
		return (handle_logic(line), free(tmp), -12);
	return (free(tmp), -(10 + n));
}
