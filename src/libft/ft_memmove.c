/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:34:29 by vdenisse          #+#    #+#             */
/*   Updated: 2023/04/11 11:59:33 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*p;
	char	*q;

	p = (char *)dst;
	q = (char *)src;
	if (dst == src)
		return (dst);
	if (q < p)
	{
		while (len--)
			*(p + len) = *(q + len);
		return (dst);
	}
	while (len--)
		*p++ = *q++;
	return (dst);
}
