/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:14:47 by namenega          #+#    #+#             */
/*   Updated: 2020/01/10 13:02:30 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (!(tab = malloc(size * nmemb)))
		return (NULL);
	ft_bzero(tab, (nmemb * size));
	return (tab);
}

/*
** alloue un tab de nmemb elements de taille size octets
** on le remplit avec des \0
*/
