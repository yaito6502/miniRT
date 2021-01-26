/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 09:36:06 by yaito             #+#    #+#             */
/*   Updated: 2020/10/13 07:55:34 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*p;

	size = ft_strlen(s1) * sizeof(char) + 1;
	if ((p = malloc(size)) == NULL)
		return (NULL);
	return (ft_memcpy(p, s1, size));
}
