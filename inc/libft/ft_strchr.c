/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:47 by namenega          #+#    #+#             */
/*   Updated: 2020/01/10 14:55:23 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if (c == '\0')
		return (str + ft_strlen(s));
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

/*
** renvoie pointeur sur premiere occurence avec c dans s
*/
