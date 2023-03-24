/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:42:45 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/27 16:52:36 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f) (unsigned int, char))
{
	char			*p;
	unsigned int	idx;
	unsigned int	len_src;

	if (!s)
		return (NULL);
	len_src = ft_strlen((char *)s);
	idx = 0;
	p = (char *)malloc(len_src + 1);
	if (!p || !s || !f)
		return (NULL);
	while (idx < len_src)
	{
		p[idx] = f(idx, s[idx]);
		idx++;
	}
	p[idx] = '\0';
	return (p);
}

// char hh(unsigned int i, char c)
// {
// 	return (c - 32);
// }
// int main()
// {
// 	printf("%s" , ft_strmapi(NULL, hh));
// }