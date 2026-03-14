/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:31:58 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/22 18:18:42 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
// int main(void)
// {
// 	t_list *lst = NULL;
// 	t_list *n1 = ft_lstnew("Mais nan");
// 	t_list *n2 = ft_lstnew("jure");
// 	t_list *n3 = ft_lstnew("arrete");

// 	ft_lstadd_front(&lst, n1);
// 	ft_lstadd_front(&lst, n2);
// 	ft_lstadd_front(&lst, n3);
// 	while(lst)
// 	{
// 		printf("%s\n",(char *)lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }