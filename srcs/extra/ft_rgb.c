/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:51:39 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/07 17:24:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <geometry/geometry.h>

t_rgb		ft_rgb(int r, int g, int b, int alpha)
{
	t_rgb	rgb;

	rgb.r = (unsigned char)r;
	rgb.g = (unsigned char)g;
	rgb.b = (unsigned char)b;
	rgb.trans = (unsigned char)alpha;
	return (rgb);
}

void		usage(char *s, int i)
{
	ft_putendl(s);
	exit_properly(i);
}
