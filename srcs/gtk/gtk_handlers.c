/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:47:04 by adleau            #+#    #+#             */
/*   Updated: 2019/02/07 15:04:36 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <display/display.h>

extern t_global		g_global;

void				handle_edit_validation(t_obj *o)
{
	int		r;

	r = gtk_dialog_run(GTK_DIALOG(g_global.r.gtk_mgr.ui.add_view.win));
	if (r == GTK_RESPONSE_ACCEPT)
	{
		validate_edit(o);
		if (g_global.r.gtk_mgr.ui.add_view.win)
		{
			gtk_widget_destroy(GTK_WIDGET(g_global.r.gtk_mgr.ui.add_view.win));
			g_global.r.gtk_mgr.ui.add_view.win = NULL;
		}
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		handle_edit_reject();
		gtk_widget_destroy(GTK_WIDGET(g_global.r.gtk_mgr.ui.add_view.win));
	}
}

void				destroy_ui_for_poly(void)
{
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.scale_img);
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.scale_spin);
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.file_check);
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.same);
	gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.from_template);
	if (g_global.r.gtk_mgr.ui.add_view.cube)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.cube);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.tetra);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.dode);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.pyramid);
	}
}

void				destroy_interface_for_type(int type)
{
	if (type == 1 || type == 4)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.scale_img);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.scale_spin);
	}
	if (type == 2 || type == 3 || type == 4)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.vector_x);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.vector_y);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.vector_z);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.vector_img);
	}
	if (type == 3 || type == 4)
	{
		if (type == 3)
		{
			gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.angle_img);
			gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.angle_spin);
		}
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.infinite);
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.add_view.inf_img);
	}
	if (type == 6 || type / 10 == 6)
		destroy_ui_for_poly();
}

void				create_inner_obj_for_type(t_obj *tmp, int type)
{
	if (type == 1)
	{
		if (!(tmp->obj = (t_sphere*)malloc(sizeof(t_sphere))))
			exit_properly(1);
		tmp->type = 1;
	}
	else if (type == 2)
	{
		if (!(tmp->obj = (t_plane*)malloc(sizeof(t_plane))))
			exit_properly(1);
		tmp->type = 2;
	}
	else if (type == 3)
	{
		if (!(tmp->obj = (t_cone*)malloc(sizeof(t_cone))))
			exit_properly(1);
		tmp->type = 3;
	}
	else if (type == 4 || type == 6 || type / 10 == 6)
		create_inner_obj_for_type_end(tmp, type);
}

void				create_object(t_obj *o, int type)
{
	t_obj			*tmp;

	if (!(tmp = (t_obj*)malloc(sizeof(t_obj))))
		exit_properly(1);
	create_inner_obj_for_type(tmp, type);
	set_default_values(tmp);
	if (o->type == 6 || o->type / 10 == 6)
		free_poly(((t_poly_obj*)o->obj));
	else
		free(o->obj);
	o->type = tmp->type;
	o->obj = tmp->obj;
}
