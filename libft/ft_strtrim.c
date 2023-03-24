/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:06:19 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/30 16:59:24 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_s1;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size_s1 = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[size_s1]) && size_s1 != 0)
		size_s1--;
	return (ft_substr((char *)s1, 0, size_s1 + 1));
}

/*

		ft_strtrim("+-213456-+", "-+")
		ft_strchr("-+",'-')

		ft_strtrim("+-213456-+", "+-")
		ft_strchr("+-",'-')

*/
// int main()
// {
// 	printf("%s",ft_strtrim("abd213456bca", "abc"));
// }