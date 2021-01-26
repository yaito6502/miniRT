/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:25:47 by yaito             #+#    #+#             */
/*   Updated: 2020/10/18 03:47:02 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_searchbegin(char *str, char	const *set, size_t len)
{
	char	*head;
	int		flag;

	head = (char *)set;
	while (len--)
	{
		set = head;
		flag = 0;
		while (*set)
		{
			if (*str == *set)
			{
				flag = 1;
				break ;
			}
			set++;
		}
		if (!flag)
			break ;
		str++;
	}
	return (str);
}

static	char	*ft_searchend(char *str, char const *set, size_t len)
{
	char	*head;
	int		flag;

	head = (char *)set;
	str += len - 1;
	while (len--)
	{
		set = head;
		flag = 0;
		while (*set)
		{
			if (*str == *set)
			{
				flag = 1;
				break ;
			}
			set++;
		}
		if (!flag)
			break ;
		str--;
	}
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*begin;
	char	*end;
	char	*p;
	int		len;

	if (!s1 || !set)
		return ((char *)s1);
	len = ft_strlen(s1);
	begin = ft_searchbegin((char *)s1, set, len);
	end = ft_searchend((char *)s1, set, len);
	len = end - begin + 1;
	if (begin > end)
		return (ft_strdup(""));
	if ((p = malloc(len + 1)) == NULL)
		return (NULL);
	ft_strlcpy(p, begin, len + 1);
	return (p);
}
