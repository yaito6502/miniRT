/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 05:27:21 by yaito             #+#    #+#             */
/*   Updated: 2020/10/11 23:56:11 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dlen;
	size_t slen;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (dstsize <= dlen)
		return (slen + dstsize);
	dst += dlen;
	while (*src && dstsize-- > dlen + 1)
		*dst++ = *src++;
	*dst = '\0';
	return (dlen + slen);
}
