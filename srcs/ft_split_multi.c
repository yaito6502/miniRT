/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaito <yaito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:22:07 by yaito             #+#    #+#             */
/*   Updated: 2021/02/06 18:28:15 by yaito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static	size_t	ft_strclen(char const *s, char *div)
{
	size_t i;

	i = 0;
	while (s[i] && !ft_strchr(div, s[i]))
		i++;
	return (i);
}

static size_t	culcwordslen(char const *s, char *div)
{
	size_t wordslen;

	wordslen = 0;
	while (*s)
	{
		while (ft_strchr(div, *s))
			s++;
		if (!*s)
			break ;
		s += ft_strclen(s, div);
		wordslen++;
	}
	return (wordslen);
}

static	void	*clear(char **words, int i)
{
	while (i--)
	{
		free(*words);
		words++;
	}
	free(words);
	return (NULL);
}

char			**ft_split_multi(char const *s, char *div)
{
	size_t	wordslen;
	size_t	len;
	char	**words;
	int		i;

	if (!s)
		return (NULL);
	wordslen = culcwordslen(s, div);
	if ((words = (char **)malloc(sizeof(char *) * (wordslen + 1))) == NULL)
		return (NULL);
	i = 0;
	while (wordslen--)
	{
		while (ft_strchr(div, *s))
			s++;
		len = ft_strclen(s, div);
		if ((words[i] = malloc(len + 1)) == NULL)
			return (clear(words, i));
		ft_strlcpy(words[i], s, len + 1);
		s += len;
		i++;
	}
	words[i] = NULL;
	return (words);
}
