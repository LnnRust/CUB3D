/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:29:41 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/23 12:19:20 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	new_list = NULL;
	while (lst)
	{
		new_elem = malloc(sizeof(t_list));
		if (!new_elem)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_elem->content = f(lst->content);
		new_elem->next = NULL;
		ft_lstadd_back(&new_list, new_elem);
		lst = lst -> next;
	}
	return (new_list);
}
// static void *f(void *content)
// {
// 	if (!content)
// 		return (NULL);
// 	return(ft_strdup((char *)content));
// }
// static void del(void *content)
// {
// 	free(content);
// }
// int main(void)
// {
// 	t_list *lst = NULL;
//     t_list *newlst = NULL;
//     t_list *tmp;

// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Mais NAN")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("JURE")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("ARRETTE")));
// 	newlst = ft_lstmap(lst, f, del);
// 	tmp = newlst;
// 	while(tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp -> next;
// 	}
// 	return (0);
// }