/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nathan <Nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:17:32 by namenega          #+#    #+#             */
/*   Updated: 2021/03/16 17:13:56 by Nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** compte la size
*/

static int	ft_strlennbr(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

/*
** si n=0, malloc string de 0
** j = nbr de chiffre ds int (needed pour malloc)
** traduit a l'envers et str[0] = - si neg
*/

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		j;

	if (n == 0)
		return (ft_strdup("0"));
	j = ft_strlennbr(n);
	i = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	str[j] = '\0';
	while (j--)
	{
		if (n < 0)
			n *= -1;
		str[j] = (n % 10 + '0');
		n = n / 10;
	}
	if (i < 0)
		str[0] = '-';
	return (str);
}

/*
** malloc et retourne une chaine
** chaine = integer converti
*/
