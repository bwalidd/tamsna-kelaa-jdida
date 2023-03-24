/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:11:50 by wbouwach          #+#    #+#             */
/*   Updated: 2022/10/30 16:16:09 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == 0)
		*lst = new;
	else
		(ft_lstlast(*lst))->next = new;
}

/*int main()
{
	t_list *f;
	for (int i = 0 ; i < 5 ; i++)
	{
		char s[] = "abcd";
		ft_lstadd_back(&f, ft_lstnew(ft_strdup(str)));
	}	
	
	while (f)
	{
		printf("%s",f->content);
		f = f->next;
	}
}
*/