/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:09:36 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/19 20:58:41 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	cmpt;

	cmpt = 0;
	index = 0;
	while (src[cmpt] != '\0')
		cmpt++;
	while (src[index] != '\0' && index + 1 < dstsize && dstsize)
	{
		dst[index] = src[index];
		index++;
	}
	if (dstsize)
		dst[index] = '\0';
	return (cmpt);
}
