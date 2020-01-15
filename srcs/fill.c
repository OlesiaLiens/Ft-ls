/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:58:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/15 15:58:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		fill_spaces(char *res, int nbr)
{
	while (nbr > 0)
	{
		*res = ' ';
		res++;
		nbr--;
	}
}

void		fill_number(char *res, size_t nbr, int len)
{
	while (len)
	{
		res--;
		*res = (nbr % 10) + 48;
		nbr = nbr / 10;
		len--;
	}
}
