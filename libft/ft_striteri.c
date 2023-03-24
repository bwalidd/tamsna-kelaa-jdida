/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:13:30 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/30 16:23:53 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f) (unsigned int, char *))
{
	size_t	idx;

	idx = 0;
	if (!s || !f)
		return ;
	while (s[idx])
	{
		f(idx, &s[idx]);
		idx++;
	}
}

/*void	*f(unsigned int i, char *s)
{
		s[i] = 'k';	
}*/
