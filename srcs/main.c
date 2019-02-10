/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 09:06:03 by adleau            #+#    #+#             */
/*   Updated: 2019/02/07 14:21:12 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>

t_global		g_global;

void				ft_exit(char *msg_error, int i)
{
	if (msg_error != NULL)
	{
		ft_putstr(msg_error);
		ft_putstr("\n");
	}
	exit_properly(i);
}

static void			init_ray(t_point p)
{
	g_global.r.rays[p.y][p.x].p = g_global.r.cam_position;
	g_global.r.rays[p.y][p.x].vector.x = p.x - (WIN_W / 2);
	g_global.r.rays[p.y][p.x].vector.y = -p.y + (WIN_H / 2);
	g_global.r.rays[p.y][p.x].vector.z = g_global.r.screen_distance;
}

void				init_obj_tab(void)
{
	int			y;

	y = -1;
	g_global.r.checker = NULL;
	if (!(g_global.r.checker = malloc(sizeof(t_obj**) * WIN_H)))
		ft_exit("Malloc error ('main.c' --> Ln 47)", 1);
	while (++y < WIN_H)
	{
		g_global.r.checker[y] = NULL;
		if (!(g_global.r.checker[y] = malloc(sizeof(t_obj*) * WIN_W)))
			ft_exit("Malloc error ('main.c' --> Ln 52)", 1);
	}
}

void				init_rt(void)
{
	t_point			p;

	init_obj_tab();
	g_global.r.gtk_mgr.pixmap = NULL;
	g_global.r.cam_position.x = 0;
	g_global.r.cam_position.y = 0;
	g_global.r.cam_position.z = 0;
	g_global.r.screen_distance = (WIN_W / 2) / tan((PI / FOV) / 2) * SDF;
	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
			init_ray(p);
	}
}

int					main(int ac, char **av)
{
	g_global.drawn = 1;
	init_gtk(ac, av);
	return (0);
}
