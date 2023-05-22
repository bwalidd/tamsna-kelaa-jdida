/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_sep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:23:24 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/21 17:24:28 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_sep(char *s, char sep)
{
	char	*ret;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[n] && (s[n] != sep))
		n++;
	ret = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
