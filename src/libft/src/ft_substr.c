/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:58:45 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/30 13:47:39 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sublen;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	sublen = 0;
	if ((size_t)start > s_len)
		return (ft_strdup(""));
	else
		sublen = s_len - start;
	if (sublen > len)
		sublen = len;
	substr = (char *)malloc((sublen + 1) * sizeof(char));
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, sublen + 1);
	return (substr);
}
