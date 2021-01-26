/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 04:21:43 by yaito             #+#    #+#             */
/*   Updated: 2020/10/09 08:43:30 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *uc_dst;
	unsigned char *uc_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	if (src < dst)
	{
		uc_dst = uc_dst + len - 1;
		uc_src = uc_src + len - 1;
		while (len--)
			*uc_dst-- = *uc_src--;
	}
	else
	{
		while (len--)
			*uc_dst++ = *uc_src++;
	}
	return (dst);
}
