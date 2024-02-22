/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:07:27 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/08 11:30:34 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		list_size;
	int		i;
	t_list	*copy_of_lst;

	copy_of_lst = lst;
	list_size = ft_lstsize(copy_of_lst);
	i = 0;
	while (i < (list_size - 1))
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
