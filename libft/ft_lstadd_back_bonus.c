/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:37:58 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/22 18:56:44 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}
// int main(void)
// {
// 	t_list *temp;
// 	t_list *n1 = ft_lstnew("Mais nan");
// 	t_list *n2 = ft_lstnew("jure");
// 	t_list *n3 = ft_lstnew("arrete");

// 	ft_lstadd_back(&n1, n2);
// 	ft_lstadd_back(&n2, n3);
// 	temp = n1;
// 	while(temp)
// 	{
// 		printf("%s\n",(char *)temp->content);
// 		temp = temp->next;
// 	}
// 	printf("%s\n", (char *)n1->content);
// 	return (0);
// }