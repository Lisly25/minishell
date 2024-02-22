/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:44:09 by skorbai           #+#    #+#             */
/*   Updated: 2023/10/24 11:39:26 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	int	islower;
	int	isupper;

	if (c >= 65 && c <= 90)
		isupper = 1;
	else
		isupper = 0;
	if (c >= 97 && c <= 122)
		islower = 1;
	else
		islower = 0;
	if (islower != 0 || isupper != 0)
		return (1);
	else
		return (0);
}
