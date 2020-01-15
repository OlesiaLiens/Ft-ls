/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:55:07 by oshyiata          #+#    #+#             */
/*   Updated: 2018/11/15 15:37:30 by oshyiata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			step;

	temp_dst = (unsigned char*)dst;
	temp_src = (unsigned char*)src;
	step = sizeof(size_t);
	while (n >= step)
	{
		*((size_t*)temp_dst) = *((size_t*)temp_src);
		n -= step;
		temp_dst += step;
		temp_src += step;
	}
	while (n > 0)
	{
		*temp_dst = *temp_src;
		n--;
		temp_dst++;
		temp_src++;
	}
	return (dst);
}
