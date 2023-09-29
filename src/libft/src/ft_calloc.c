/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:58:37 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/30 13:46:42 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, (nmemb * size));
	return (p);
}
