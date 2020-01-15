/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_t_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:00:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/06 18:00:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*cr_t_file(char *name, int name_len, t_stat *stat, t_file *next)
{
	t_file	*file;

	file = (t_file*)ft_memalloc(sizeof(t_file));
	file->name_len = name_len;
	file->name = (char *)malloc(file->name_len + 1);
	ft_memcpy((void*)file->name, (void*)name, file->name_len);
	file->name[file->name_len] = '\0';
	file->stat = stat;
	file->next = next;
	return (file);
}
