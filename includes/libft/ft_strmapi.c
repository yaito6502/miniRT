/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 05:52:08 by yaito             #+#    #+#             */
/*   Updated: 2020/10/12 18:28:15 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			len;
	unsigned int	index;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if ((str = malloc(len + 1)) == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		str[index] = (*f)(index, s[index]);
		index++;
	}
	str[len] = '\0';
	return (str);
}
