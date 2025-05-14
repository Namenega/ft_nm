/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:20:09 by namenega          #+#    #+#             */
/*   Updated: 2020/01/14 15:40:45 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
	{
		alst = &((*alst)->next);
	}
	(*alst)->next = new;
}

/*
** add new at the end of list
*/
