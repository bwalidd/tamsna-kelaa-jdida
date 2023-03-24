/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:24:52 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/30 16:17:17 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digist(int n)
{
	size_t	count;

	count = 0;
	if (n)
	{
		while (n)
		{
			n /= 10;
			count++;
		}
		return (count);
	}
	else
		return (1);
}

static void	ft_write_nbrber(char *dest, long int n)
{
	if (n < 10)
		*dest = n + '0';
	else
	{
		*dest = n % 10 + '0';
		ft_write_nbrber(dest - 1, n / 10);
	}
}

char	*ft_itoa(int n)
{
	long int		nbr;
	char			*result;
	size_t			len;

	nbr = (long int)n;
	if (n < 0)
	{
		len = ft_count_digist(n) + 1;
		nbr = nbr * -1;
	}
	else
		len = ft_count_digist(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_write_nbrber((result + len - 1), nbr);
	if (n < 0)
		*result = '-';
	result[len] = '\0';
	return (result);
}
