/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:30:38 by vdenisse          #+#    #+#             */
/*   Updated: 2023/04/11 12:50:54 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				i;

	i = 0;
	p = (const unsigned char *)s;
	while (i < n)
	{
		if (*p == (unsigned char)c)
		{
			return ((char *)p);
		}
		p++;
		i++;
	}
	return (0);
}
