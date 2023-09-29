/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:34:06 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/30 13:46:48 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/libft.h"

static int	ft_int_len(long n)
{
	size_t	len;
	int		isneg;

	len = 0;
	isneg = 0;
	if (n < 0)
	{
		len++;
		isneg++;
		n = -n;
	}
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_gen(char *result, long nbr, int len, int isneg)
{
	if (nbr != 0)
		result = malloc(sizeof(char) * (len + 1));
	else
		return (result = ft_strdup("0"));
	if (!result)
		return (0);
	isneg = 0;
	if (nbr < 0)
	{
		isneg++;
		nbr = -nbr;
	}
	result[len] = '\0';
	while (--len)
	{
		result[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (isneg == 1)
		result[0] = '-';
	else
		result[0] = (nbr % 10) + '0';
	return (result);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	nbr;
	int		isneg;

	nbr = n;
	len = ft_int_len(nbr);
	result = 0;
	isneg = 0;
	result = ft_gen(result, nbr, len, isneg);
	if (!result)
		return (0);
	return (result);
}
