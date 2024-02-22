/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:05:19 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/19 11:39:20 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_node;
	t_list	*copy_of_lst;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	copy_of_lst = *lst;
	next_node = copy_of_lst->next;
	while (next_node != NULL)
	{
		next_node = copy_of_lst->next;
		ft_lstdelone(copy_of_lst, del);
		copy_of_lst = next_node;
	}
	ft_lstdelone(copy_of_lst, del);
	*lst = NULL;
}
