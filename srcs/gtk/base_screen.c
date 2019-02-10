/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:15:01 by adleau            #+#    #+#             */
/*   Updated: 2019/02/07 15:07:42 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <display/display.h>

extern t_global		g_global;

void			handle_drawing(void)
{
	if (!g_global.r.gtk_mgr.buf)
	{
		g_global.r.gtk_mgr.buf = NULL;
		if (!(g_global.r.gtk_mgr \
		.buf = (unsigned char*)malloc(sizeof(unsigned char)
			* (WIN_H * cairo_format_stride_for_width(
				CAIRO_FORMAT_RGB24, WIN_W)))))
			exit_properly(1);
	}
	draw_image();
	if (g_global.r.gtk_mgr.pixmap)
	{
		cairo_surface_destroy(g_global.r.gtk_mgr.pixmap);
		g_global.r.gtk_mgr.pixmap = NULL;
	}
	g_global.r.gtk_mgr.pixmap = cairo_image_surface_create_for_data(
		g_global.r.gtk_mgr.buf, CAIRO_FORMAT_RGB24, WIN_W, WIN_H,
		cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
	if (cairo_surface_status(g_global.r.gtk_mgr.pixmap) != CAIRO_STATUS_SUCCESS)
		exit_properly(1);
	cairo_surface_mark_dirty(g_global.r.gtk_mgr.pixmap);
	g_global.r.gtk_mgr.ui.main_view.render_area = gtk_image_new_from_surface(
		g_global.r.gtk_mgr.pixmap);
	g_global.r.gtk_mgr.ui.main_view.event_box = gtk_event_box_new();
	handle_drawing_end();
}

void			end_base_view(void)
{
	g_signal_connect(G_OBJECT(g_global.base_view.win),
	"key-press-event", G_CALLBACK(on_key_press), NULL);
	g_signal_connect(G_OBJECT(g_global.base_view.win),
	"delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(g_global.base_view.win);
}

void			handle_base_view(void)
{
	g_global.base_view.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(g_global.base_view.win), false);
	gtk_window_set_position(GTK_WINDOW(g_global.base_view.win),
	GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(g_global.base_view.win), "RT");
	g_global.base_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(g_global.base_view.win),
	g_global.base_view.grid);
	g_global.base_view.open_button = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.open_button),
	"Open Scene");
	g_signal_connect(G_OBJECT(g_global.base_view.open_button),
	"clicked", G_CALLBACK(open_file), NULL);
	g_global.base_view.exit_button = gtk_button_new_from_icon_name(
	"application-exit", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_label(GTK_BUTTON(g_global.base_view.exit_button), "Exit");
	gtk_button_set_always_show_image(GTK_BUTTON(g_global.base_view.exit_button),
	true);
	g_signal_connect(G_OBJECT(g_global.base_view.exit_button), "clicked",
	G_CALLBACK(gtk_main_quit), NULL);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid),
	g_global.base_view.open_button, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(g_global.base_view.grid),
	g_global.base_view.exit_button, 0, 1, 2, 1);
	end_base_view();
}

static void		init_base_view(void)
{
	g_global.base_view.win = NULL;
	g_global.base_view.grid = NULL;
	g_global.base_view.open_button = NULL;
	g_global.base_view.exit_button = NULL;
}

void			init_gtk(int ac, char **av)
{
	init_base_view();
	gtk_init(&ac, &av);
	handle_base_view();
	gtk_main();
}
