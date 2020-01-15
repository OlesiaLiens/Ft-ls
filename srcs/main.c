/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:14:02 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/18 16:23:34 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	check_name_nline(char *path, t_flags flags, t_argv *args, int i)
{
	_Bool	name;
	_Bool	new_line;
	t_dir	*dir;

	name = args->dir != NULL;
	new_line = args->dir != NULL;
	if (!name && !new_line)
	{
		if (args->size > 1)
			name = 1;
		if (i > 0)
			new_line = 1;
	}
	if (flags.b_r)
		recursion(path, flags, name, new_line);
	else if ((dir = create_dir(path, flags)))
	{
		write_dir(dir, flags, name, new_line);
		free_dir(dir);
	}
}

void	write_dirs(t_argv *args, t_flags flags)
{
	t_file	**dirs_arr;
	int		i;

	i = 0;
	dirs_arr = sort_files(args->dirs, flags, args->size);
	while (i < args->size)
	{
		check_name_nline(dirs_arr[i]->name, flags, args, i);
		i++;
	}
	free(dirs_arr);
}

void	write_args(t_argv *args, t_flags flags)
{
	t_dir	*dir;

	if (args == NULL)
	{
		if (flags.b_r)
			recursion(".", flags, 0, 0);
		else if ((dir = create_dir(".", flags)))
		{
			write_dir(dir, flags, 0, 0);
			free_dir(dir);
		}
	}
	else
	{
		if (args->dir)
		{
			write_dir(args->dir, flags, 0, 0);
			free_dir(args->dir);
		}
		if (args->dirs)
		{
			write_dirs(args, flags);
			free_all_files(args->dirs);
		}
	}
}

int		main(int argc, char **argv)
{
	t_flags	flags;
	t_argv	*args;

	args = NULL;
	ft_bzero((void*)&flags, sizeof(t_flags));
	if (argc != 1)
	{
		argv = parsing_flags(argv + 1, &flags);
		if (*argv && flags.f == 0)
			argv = sort_argv(argv);
		if (*argv)
			args = valid_argv(argv, flags);
		write_args(args, flags);
	}
	else
		write_args(args, flags);
	return (0);
}
