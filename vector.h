/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:54:28 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/05 09:54:13 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

typedef struct s_vector_text
{
	char	**text;
	size_t	used_nodes;
	size_t	max_nodes;
}	t_vector;

t_vector	*vector_new(size_t size);

int			vector_add_back(t_vector *old, char *new_data);

char		**vector_array_realloc(char ***old_text, size_t node_max);

int			expand_vector(t_vector *old);

void		free_vector(t_vector *vector);

#endif