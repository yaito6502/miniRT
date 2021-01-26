/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 04:29:26 by yaito             #+#    #+#             */
/*   Updated: 2020/10/12 00:17:52 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *first;
	t_list *last;
	t_list *new;

	if (!lst || !f)
		return (NULL);
	if ((new = ft_lstnew((*f)(lst->content))) == NULL)
		return (NULL);
	first = new;
	last = lst->next;
	while (last != NULL)
	{
		if ((new->next = ft_lstnew((*f)(last->content))) == NULL)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new = new->next;
		last = last->next;
	}
	return (first);
}
