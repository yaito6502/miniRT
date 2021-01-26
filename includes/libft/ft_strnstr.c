/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 06:59:57 by yaito             #+#    #+#             */
/*   Updated: 2020/10/14 01:58:20 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t nlen;

	nlen = ft_strlen(needle);
	if (!nlen)
		return ((char *)haystack);
	while (len-- >= nlen)
	{
		if (ft_strncmp(haystack, needle, nlen) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
