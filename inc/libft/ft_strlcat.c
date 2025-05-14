/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:09:21 by namenega          #+#    #+#             */
/*   Updated: 2020/01/10 15:06:22 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t compteur;

	i = 0;
	compteur = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	compteur = compteur + i + ft_strlen(src);
	if (i == size)
		return (compteur);
	j = 0;
	while (src[j] && (i + j < size - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (compteur);
}

/*
** concat src a la fin de dest, return dest+src
*/
