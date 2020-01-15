/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/01 17:18:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parsing_flags_1(char *str, t_flags *flags)
{
	while (*str != 0)
	{
		if (*str == 'l')
			flags->l = 1;
		else if (*str == 'R')
			flags->b_r = 1;
		else if (*str == 'r')
			flags->r = 1;
		else if (*str == 'a')
			flags->a = 1;
		else if (*str == 't')
			flags->t = 1;
		else if (*str == 'f')
			flags->f = 1;
		else
		{
			ft_putendl("usage: put flags ONLY -t -a -R -r -l -f");
			exit(0);
		}
		str++;
	}
}

char	**parsing_flags(char **argv, t_flags *flags)
{
	char *str;

	while (*argv)
	{
		str = *argv;
		if (*str == '-' && *(str + 1))
			parsing_flags_1(str + 1, flags);
		else
			break ;
		argv++;
	}
	return (argv);
}
