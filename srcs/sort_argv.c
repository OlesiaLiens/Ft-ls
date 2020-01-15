/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:35:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/15 21:27:52 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static _Bool		check_for_swap(char *first, char *second)
{
	int		i;

	i = 0;
	while (first[i] && second[i])
	{
		if ((unsigned char)second[i] < (unsigned char)first[i] ||
			(second[i] == first[i] && second[i + 1] == '\0' &&
			first[i + 1] != '\0'))
			return (1);
		else if (first[i] == second[i])
			i++;
		else
			break ;
	}
	return (0);
}

char				**sort_argv(char **argv)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (check_for_swap(argv[i], argv[j]))
			{
				temp = argv[i];
				argv[i] = argv[j];
				argv[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (argv);
}
