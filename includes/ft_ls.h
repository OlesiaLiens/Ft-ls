/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:47:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2019/04/13 17:47:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>

# define GET_TYPE(mode) "-pc-d-b---l-s-w"[mode >> 12 & 15]

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct s_file	t_file;

typedef struct		s_flags
{
	_Bool	l;
	_Bool	b_r;
	_Bool	r;
	_Bool	a;
	_Bool	t;
	_Bool	f;
}					t_flags;

struct				s_file
{
	char	*name;
	int		name_len;
	char	*link;
	int		link_len;
	char	type;
	char	*full_path;
	char	*group;
	int		group_len;
	char	*login;
	int		login_len;
	int		min_len;
	int		maj_len;
	int		nlink_len;
	int		size_len;
	t_stat	*stat;
	t_file	*next;
};

typedef struct		s_dir
{
	blkcnt_t	total;
	char		*name;
	int			names_len;
	t_file		*files;
	t_file		**files_arr;
	int			size;
	int			links_len;
	int			links_count;
	int			padding_nlink;
	int			padding_login;
	int			padding_group;
	int			padding_size;
	int			padding_maj;
	int			padding_min;
	_Bool		c_or_b_type;
}					t_dir;

typedef struct		s_argv
{
	t_dir	*dir;
	t_file	*dirs;
	int		size;
}					t_argv;

char				**parsing_flags(char **argv, t_flags *flags);
char				**sort_argv(char **argv);
void				error(char *name);
t_argv				*valid_argv(char **argv, t_flags flags);
t_file				*sort_list(t_file *lst);
t_file				**sort_files(t_file *files, t_flags flags, int size);
void				write_dir(t_dir *dir, t_flags flags, _Bool name, _Bool nl);
void				write_dirs(t_argv *args, t_flags flags);
void				free_dir(t_dir *dir);
void				free_file(t_file *file);
t_dir				*create_dir(char *name, t_flags flags);
t_file				*cr_t_file(char *name, int len, t_stat *stat, t_file *next);
void				add_file(t_dir *dir, t_dirent *entry, t_flags flags);
size_t				nbr_len(size_t nbr);
void				free_all_files(t_file *file);
void				recursion(char *path, t_flags flags, _Bool name, _Bool nl);
ssize_t				add_link(t_file *file, char *path);
int					get_group_login(t_file *file);
void				get_padding(t_dir *dir, t_file *file);
int					fill_str(char *res, t_file *file, t_dir *dir);
void				fill_spaces(char *res, int nbr);
void				fill_number(char *res, size_t nbr, int len);

#endif
