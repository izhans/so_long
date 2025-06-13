/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:40:01 by isastre-          #+#    #+#             */
/*   Updated: 2025/01/16 20:55:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int nbr)
{
	int	ret;

	ret = 0;
	if (nbr < 10)
		ret += ft_putchar(nbr + '0');
	else
	{
		ret += ft_putnbr(nbr / 10);
		ret += ft_putnbr(nbr % 10);
	}
	return (ret);
}
