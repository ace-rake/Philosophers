/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:54:25 by vdenisse          #+#    #+#             */
/*   Updated: 2023/04/11 13:16:23 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p;
	const unsigned char	*q;
	size_t				s;

	if (n == 0)
		return (0);
	s = 0;
	p = (const unsigned char *)s1;
	q = (const unsigned char *)s2;
	while (*p == *q && ++s < n)
	{
		p++;
		q++;
	}
	return (*p - *q);
}
