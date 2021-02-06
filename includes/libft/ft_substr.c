/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:11:03 by yaito             #+#    #+#             */
/*   Updated: 2020/10/18 03:47:14 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		slen;
	size_t				size;
	char				*p;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	size = ft_min(slen - start, len);
	if ((p = malloc(size + 1)) == NULL)
		return (NULL);
	p[size] = '\0';
	return (ft_memcpy(p, s + start, size));
}
