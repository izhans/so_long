/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:59 by isastre-          #+#    #+#             */
/*   Updated: 2025/01/16 20:52:33 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base(uint64_t nbr, char *base, uint64_t base_len);

int	ft_putaddr(uint64_t addr)
{
	char	*base;
	int		ret;

	if (addr == 0)
		return (ft_putstr("(nil)"));
	base = "0123456789abcdef";
	ret = ft_putstr("0x");
	return (ret + ft_putnbr_base(addr, base, 16));
}

static int	ft_putnbr_base(uint64_t nbr, char *base, uint64_t base_len)
{
	int	ret;

	ret = 0;
	if (nbr < base_len)
		return (ret + ft_putchar(base[nbr]));
	ret += ft_putnbr_base(nbr / base_len, base, base_len);
	ret += ft_putnbr_base(nbr % base_len, base, base_len);
	return (ret);
}
