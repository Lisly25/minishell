/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:32:01 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/20 15:32:17 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*linked_list;

	linked_list = malloc(sizeof (t_list));
	if (linked_list == NULL)
		return (NULL);
	linked_list->content = content;
	linked_list->next = NULL;
	return (linked_list);
}
