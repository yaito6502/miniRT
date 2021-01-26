/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 04:25:47 by yaito             #+#    #+#             */
/*   Updated: 2020/10/13 08:02:46 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	if (!lst || !*lst)
	{
		ft_lstadd_front(lst, new);
		new->next = NULL;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->next = NULL;
}
