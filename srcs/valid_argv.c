/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:07:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/15 21:03:33 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

_Bool		add_to_args_1(t_argv *args, t_file *file, t_flags flags)
{
	if (args->dir == NULL)
		args->dir = (t_dir*)ft_memalloc(sizeof(t_dir));
	if (file->type == 'l' && flags.l && add_link(file, file->name) == -1)
		return (1);
	if (flags.l && get_group_login(file) == -1)
		return (1);
	if (flags.l)
		get_padding(args->dir, file);
	args->dir->names_len += file->name_len;
	args->dir->size++;
	file->next = args->dir->files;
	args->dir->files = file;
	return (0);
}

void		add_to_args(t_stat *st, char *name, t_argv *args, t_flags flags)
{
	char		type_st;
	char		type_buf;
	t_stat		buf;
	t_file		*file;

	stat(name, &buf);
	type_buf = GET_TYPE(buf.st_mode);
	type_st = GET_TYPE(st->st_mode);
	if ((type_st == 'l' && type_buf == 'd' && !flags.l) || type_st == 'd')
	{
		st->st_mtime = buf.st_mtime;
		args->dirs = cr_t_file(name, ft_strlen(name), st, args->dirs);
		args->dirs->type = type_st;
		args->size++;
	}
	else
	{
		file = cr_t_file(name, ft_strlen(name), st, NULL);
		file->type = type_st;
		if (add_to_args_1(args, file, flags))
			free_file(file);
	}
}

t_argv		*valid_argv(char **argv, t_flags flags)
{
	t_argv	*args;
	t_stat	*stat;
	t_stat	buf;

	args = (t_argv*)ft_memalloc(sizeof(t_argv));
	while (*argv)
	{
		if (lstat(*argv, &buf) == -1)
			error(*argv);
		else
		{
			stat = (t_stat*)malloc(sizeof(t_stat));
			ft_memcpy(stat, &buf, sizeof(t_stat));
			add_to_args(stat, *argv, args, flags);
		}
		argv++;
	}
	return (args);
}
