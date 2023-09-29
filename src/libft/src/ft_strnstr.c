/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:00:42 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/30 13:47:34 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/libft.h"

static int	ft_check(char *hay, const char *needle, size_t i, size_t c)
{
	if (hay[i + c] != '\0' && needle[c] != '\0')
		if (hay[i + c] == needle[c])
			return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		c = 0;
		while (ft_check(hay, needle, i, c) && i + c < len)
			c++;
		if (c == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}
