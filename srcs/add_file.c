/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 21:10:00 by oshyiata          #+#    #+#             */
/*   Updated: 2019/05/06 21:10:00 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_full_path(char const *s1, t_dirent *entry)
{
	char	*res;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	res = (char *)malloc(s1_len + entry->d_namlen + 2);
	if (res == NULL)
		return (NULL);
	ft_memcpy((void*)res, (void*)s1, s1_len);
	res[s1_len] = '/';
	ft_memcpy((void*)(res + s1_len + 1), (void*)entry->d_name, entry->d_namlen);
	res[s1_len + entry->d_namlen + 1] = '\0';
	return (res);
}

ssize_t	add_link(t_file *file, char *path)
{
	ssize_t	res;

	file->link = (char *)malloc(512);
	res = readlink(path, file->link, 512);
	if (res == -1)
	{
		free(file->link);
		error(file->name);
	}
	else
	{
		file->link_len = res;
	}
	return (res);
}

int		get_group_login(t_file *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(file->stat->st_uid);
	grp = getgrgid(file->stat->st_gid);
	if (pwd == NULL || grp == NULL)
	{
		error(file->name);
		return (-1);
	}
	file->login_len = ft_strlen(pwd->pw_name);
	file->login = (char *)malloc(file->login_len + 1);
	ft_memcpy((void*)file->login, (void*)pwd->pw_name, file->login_len);
	file->login[file->login_len] = '\0';
	file->group_len = ft_strlen(grp->gr_name);
	file->group = (char *)malloc(file->group_len + 1);
	ft_memcpy((void*)file->group, (void*)grp->gr_name, file->group_len);
	file->group[file->group_len] = '\0';
	return (0);
}

void	get_padding(t_dir *dir, t_file *file)
{
	if (file->type == 'c' || file->type == 'b')
	{
		dir->c_or_b_type = 1;
		file->min_len = nbr_len(minor(file->stat->st_rdev));
		file->maj_len = nbr_len(major(file->stat->st_rdev));
		if (dir->padding_maj < file->maj_len)
			dir->padding_maj = file->maj_len;
		if (dir->padding_min < file->min_len)
			dir->padding_min = file->min_len;
	}
	file->nlink_len = nbr_len(file->stat->st_nlink);
	if (dir->padding_nlink < file->nlink_len)
		dir->padding_nlink = file->nlink_len;
	file->size_len = nbr_len(file->stat->st_size);
	if (dir->padding_size < file->size_len)
		dir->padding_size = file->size_len;
	if (dir->padding_login < file->login_len)
		dir->padding_login = file->login_len;
	if (dir->padding_group < file->group_len)
		dir->padding_group = file->group_len;
	if (file->link_len)
	{
		dir->links_len += file->link_len;
		dir->links_count++;
	}
}

void	add_file(t_dir *dir, t_dirent *entry, t_flags flags)
{
	t_file	*file;

	file = cr_t_file(entry->d_name, entry->d_namlen,
					(t_stat*)malloc(sizeof(t_stat)), NULL);
	file->full_path = get_full_path(dir->name, entry);
	if (lstat(file->full_path, file->stat) == -1)
	{
		error(entry->d_name);
		return (free_file(file));
	}
	file->type = GET_TYPE(file->stat->st_mode);
	if (file->type == 'l' && flags.l && add_link(file, file->full_path) == -1)
		return (free_file(file));
	if (flags.l && get_group_login(file) == -1)
		return (free_file(file));
	file->next = dir->files;
	dir->files = file;
	dir->size++;
	dir->names_len += entry->d_namlen;
	dir->total += file->stat->st_blocks;
	if (flags.l)
		get_padding(dir, file);
}
