/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:43:35 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/21 23:43:07 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen((char *)s) + 1;
	while (len--)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
