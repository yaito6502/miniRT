/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 04:31:53 by yaito             #+#    #+#             */
/*   Updated: 2020/10/10 06:52:26 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*lst_current;
	int		size;

	size = 0;
	lst_current = lst;
	while (lst_current != NULL)
	{
		size++;
		lst_current = lst_current->next;
	}
	return (size);
}
