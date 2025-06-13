/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:40:05 by isastre-          #+#    #+#             */
/*   Updated: 2025/01/16 20:55:34 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putxnbr(unsigned int nbr, char *base);

int	ft_putnbr_hex(int nbr, int uppercase)
{
	if (uppercase)
		return (ft_putxnbr(nbr, "0123456789ABCDEF"));
	return (ft_putxnbr(nbr, "0123456789abcdef"));
}

static int	ft_putxnbr(unsigned int nbr, char *base)
{
	int	ret;

	ret = 0;
	if (nbr < 16)
		return (ret + ft_putchar(base[nbr]));
	ret += ft_putxnbr(nbr / 16, base);
	ret += ft_putxnbr(nbr % 16, base);
	return (ret);
}
