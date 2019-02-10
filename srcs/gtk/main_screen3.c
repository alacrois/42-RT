/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:50:05 by adleau            #+#    #+#             */
/*   Updated: 2019/02/07 14:18:48 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>

extern t_global		g_global;

void	set_poly(t_rpoint pos, t_obj *o, t_rpoint rot)
{
	if (o->type == 66)
		set_cube(pos, o->size * 2, o);
	else if (o->type == 67)
		set_tetrahedron(pos, o->size, o);
	else if (o->type == 68)
		get_pyramid(o, o->size, 5);
	else if (o->type == 69)
		get_dodecahedron(o, o->size);
	rotate_obj(o, o->type, rot);
}

void	handle_edit_reject(void)
{
	g_global.r.gtk_mgr.ui.add_view.sw.o->type = g_global.r.gtk_mgr.ui.
	add_view.sw.saved;
	if (g_global.r.gtk_mgr.ui.add_view.sw.saved == 6 || g_global.r.gtk_mgr.
		ui.add_view.sw.saved / 10 == 6)
		set_poly(g_global.r.gtk_mgr.ui.add_view.sw.o->position,
		g_global.r.gtk_mgr.ui.add_view.sw.o,
		g_global.r.gtk_mgr.ui.add_view.sw.rotation);
	redraw(false);
	if (!(ft_strcmp(gtk_window_get_title(GTK_WINDOW(
		g_global.r.gtk_mgr.ui.add_view.win)), "Add Object")))
	{
		g_global.r.objects = g_global.r.gtk_mgr.ui.add_view.sw.o->next;
		free(g_global.r.gtk_mgr.ui.add_view.sw.o->obj);
		free(g_global.r.gtk_mgr.ui.add_view.sw.o);
		g_global.r.gtk_mgr.ui.add_view.sw.o = NULL;
	}
}

void	switch_type(GtkButton *button)
{
	t_obj			*o;

	o = g_global.r.gtk_mgr.ui.add_view.sw.o;
	if (g_global.r.gtk_mgr.ui.add_view.sw.o->type == 6
		|| g_global.r.gtk_mgr.ui.add_view.sw.o->type / 10 == 6)
		g_global.r.gtk_mgr.ui.add_view.sw.rotation = ((t_poly_obj*)
		g_global.r.gtk_mgr.ui.add_view.sw.o->obj)->rotation;
	destroy_interface_for_type(o->type);
	if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.sphere_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 1;
	else if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.plane_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 2;
	else if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.cone_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 3;
	else if (button == GTK_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.cylinder_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 4;
	else if (button == GTK_BUTTON(
	g_global.r.gtk_mgr.ui.add_view.obj_file_button))
		g_global.r.gtk_mgr.ui.add_view.sw.type = 6;
	create_object(o, g_global.r.gtk_mgr.ui.add_view.sw.type);
	if (o)
		actual_edit_view(o);
	gtk_widget_show_all(g_global.r.gtk_mgr.ui.add_view.win);
}
