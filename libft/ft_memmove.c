/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <mmorais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:07:54 by mmorais           #+#    #+#             */
/*   Updated: 2024/05/19 09:07:55 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (s == d)
		return (dst);
	if (s < d)
	{
		while (len--)
		{
			*(d + len) = *(s + len);
		}
		return (dst);
	}
	else
	{
		while (len--)
		{
			*d++ = *s++;
		}
	}
	return (dst);
}
