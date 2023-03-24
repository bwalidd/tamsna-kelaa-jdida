/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:46:29 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/22 22:04:32 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char			*d;
	unsigned const char		*s;
	size_t					idx;

	d = dst;
	s = src;
	idx = 0;
	if (src < dst)
	{
		idx = n;
		while (idx--)
			d[idx] = s[idx];
	}
	else
	{
		ft_memcpy(d, s, n);
	}
	return (dst);
}
