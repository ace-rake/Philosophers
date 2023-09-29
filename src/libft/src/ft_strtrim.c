/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:18:50 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/30 13:47:37 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (ft_is_in_set(s1[start], set) == 0)
		start++;
	if (start == ft_strlen(s1))
	{
		result = ft_strdup("");
		if (!result)
			return (NULL);
		else
			return (result);
	}
	while (ft_is_in_set(s1[end - 1], set) == 0)
		end--;
	result = ft_substr(s1, start, end - start);
	return (result);
}
