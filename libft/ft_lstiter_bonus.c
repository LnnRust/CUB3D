/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 21:57:52 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/22 19:30:09 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tran;

	tran = NULL;
	if (!lst)
		return ;
	while (lst)
	{
		tran = lst->next;
		f(lst->content);
		lst = tran;
	}
	return ;
}
// void f(void *c)
// {
// 	if (!c)
//         return;
//     printf("%s\n", (char *)c);
//     free(c);
// }

// int main(void)
// {
// 	t_list *lst = NULL;
// 	t_list *n1 = ft_lstnew(ft_strdup("Mais NAN"));
// 	t_list *n2 = ft_lstnew(ft_strdup("jure ????"));
// 	t_list *n3 = ft_lstnew(ft_strdup("arrete"));
// 	ft_lstadd_back(&lst, n1);
// 	ft_lstadd_back(&lst, n2);
// 	ft_lstadd_back(&lst, n3);
// 	ft_lstiter(lst, f);
// 	return(0);
// }