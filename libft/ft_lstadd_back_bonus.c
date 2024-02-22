/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:09 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/08 14:00:37 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	int		list_size;
	t_list	*copy_of_list;

	if (new == NULL)
		return ;
	copy_of_list = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	list_size = ft_lstsize(copy_of_list);
	while ((list_size - 1) > 0)
	{
		copy_of_list = copy_of_list->next;
		list_size--;
	}
	copy_of_list->next = new;
}
