/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:48:29 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/30 16:12:14 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*pos;

	pos = lst;
	i = 0;
	while (pos != NULL)
	{
		pos = pos->next;
		i++;
	}
	return (i);
}
