/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:26:45 by vdenisse          #+#    #+#             */
/*   Updated: 2023/05/08 10:45:31 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
void	print_list(t_list *head)
{
	t_list	*temp;
	int		i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		printf("node %i : [%d]\n", i, (int)temp->content);
		temp = temp->next;
		++i;
	}
}

t_list	*create_node(int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = (void *)i;
	new->next = NULL;
	return (new);
}

int	main(void)
{
	t_list	*tmp;
	t_list	*head;

	tmp = NULL;
	head = NULL;
	for (int i = 0; i <= 5; ++i)
	{
		tmp = create_node(i);
		ft_lstadd_front(&head, tmp);
		ft_lstclear(head);
	}
	print_list(head);
	return (0);
}
*/
