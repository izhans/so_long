/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:38 by isastre-          #+#    #+#             */
/*   Updated: 2025/01/16 19:54:34 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nbr)
{
	int	ret;

	ret = 0;
	if (nbr == -2147483648)
	{
		ret = ft_putstr("-2147483648");
		return (ret);
	}
	if (nbr < 0)
	{
		ret = ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr < 10)
		ret += ft_putchar(nbr + '0');
	else
	{
		ret += ft_putnbr(nbr / 10);
		ret += ft_putnbr(nbr % 10);
	}
	return (ret);
}
