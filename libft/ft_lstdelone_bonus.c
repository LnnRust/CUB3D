/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:25:15 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/22 20:07:50 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void del(void *c)
// {
// 	size_t len = (size_t)ft_strlen((char *)c);
// 	ft_bzero(c, len);
// 	free(c);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free (lst);
}

// int main(void)
// {
// 	t_list *n1 = ft_lstnew(ft_strdup("mais nan"));
// 	ft_lstdelone(n1, del);
// 	n1 = NULL;
// }