/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:39:22 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/04 14:08:17 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *head)
{
	t_list	*temp;
	int		count;

	temp = head;
	count = 0;
	while (temp != NULL)
	{
		++count;
		temp = temp->next;
	}
	return (count);
}
