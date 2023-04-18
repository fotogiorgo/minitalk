/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:49:26 by jofoto            #+#    #+#             */
/*   Updated: 2022/11/08 20:45:25 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*root;
	t_list	*new_node;

	if (lst)
	{
		root = ft_lstnew(f(lst->content));
		if (root == 0)
			return (0);
		lst = lst->next;
	}
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (new_node == 0)
		{
			ft_lstclear(&root, del);
			return (0);
		}
		ft_lstadd_back(&root, new_node);
		lst = lst->next;
	}
	return (root);
}
