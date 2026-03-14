/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:02:59 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/23 12:19:09 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->next = NULL;
	if (!new)
		return (NULL);
	new->content = content;
	return (new);
}
// int main(void)
// {
// 	t_list *n = ft_lstnew((void *)"Hello");
// 	printf("content = %s, next = %p\n", (char *)n->content, (void *)n->next);
// 	return (0);
// }