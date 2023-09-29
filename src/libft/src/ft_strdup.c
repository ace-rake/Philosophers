/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:26:23 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/30 13:47:21 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(src) + 1;
	new_str = (char *)malloc(len * sizeof(char));
	if (new_str == NULL)
		return ((void *)0);
	ft_strlcpy(new_str, src, len);
	return (new_str);
}
