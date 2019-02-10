/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_view3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:02:31 by adleau            #+#    #+#             */
/*   Updated: 2019/02/07 15:08:50 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

GtkWidget			*create_new_dialog(GtkWidget *parent)
{
	return (gtk_dialog_new_with_buttons("Edit Object", GTK_WINDOW(parent),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
	"_OK", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL));
}

void				edit_win_img_init(t_obj *o)
{
	g_global.r.gtk_mgr.ui.add_view.saved_type = o->type;
	g_global.r.gtk_mgr.ui.add_view.sphere_img = gtk_image_new_from_file(
		"uiconfig/sphere.png");
	g_global.r.gtk_mgr.ui.add_view.plane_img = gtk_image_new_from_file(
		"uiconfig/plane.png");
	g_global.r.gtk_mgr.ui.add_view.cone_img = gtk_image_new_from_file(
		"uiconfig/cone.png");
	g_global.r.gtk_mgr.ui.add_view.cylinder_img = gtk_image_new_from_file(
		"uiconfig/cylinder.png");
	g_global.r.gtk_mgr.ui.add_view.obj_file_img = gtk_image_new_from_file(
		"uiconfig/poly_obj.png");
}

void				edit_win_4(void)
{
	gtk_button_set_image(GTK_BUTTON(g_global.r.gtk_mgr.ui.add_view.cone_button),
		g_global.r.gtk_mgr.ui.add_view.cone_img);
	gtk_container_add(GTK_CONTAINER(g_global.r.gtk_mgr.ui.add_view.buttonbox),
		g_global.r.gtk_mgr.ui.add_view.cone_button);
	g_global.r.gtk_mgr.ui.add_view.cylinder_button = gtk_button_new();
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.add_view.cylinder_button),
	"clicked", G_CALLBACK(switch_type), NULL);
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.cylinder_button,
		"Cylinder");
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.add_view.cone_button,
		"Cone");
}
