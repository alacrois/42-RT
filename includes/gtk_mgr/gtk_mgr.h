/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_mgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 21:18:21 by adleau            #+#    #+#             */
/*   Updated: 2019/02/07 15:04:37 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTK_MGR_H
# define GTK_MGR_H
# include <gtk/gtk.h>
# include <stdbool.h>
# include <objects/object.h>

enum
{
	TYPE_COLUMN,
	POS_X_COLUMN,
	POS_Y_COLUMN,
	POS_Z_COLUMN,
	CHECKED_COLUMN,
	CHECKED_ACTIVE,
	OBJ_REF,
	N_COLUMNS
};

enum						e_state
{
	STATE_A,
	STATE_B
};

typedef struct				s_switcher
{
	t_obj					*o;
	int						type;
	int						saved;
	t_rpoint				rotation;
}							t_switcher;

typedef struct				s_filter_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*buttonbox;
	GtkWidget				*bw_button;
	GtkWidget				*bw_img;
	GtkWidget				*sepia_button;
	GtkWidget				*sepia_img;
	GtkWidget				*reversed_button;
	GtkWidget				*reversed_img;
}							t_filter_view;

typedef struct				s_scene_view
{
	GtkWidget				*win;
	GtkWidget				*tree;
	GtkWidget				*button;
	GtkTreeStore			*store;
	GtkWidget				*fixed;
}							t_scene_view;

typedef struct				s_progress_data
{
	GtkWidget				*pbar;
	GtkWidget				*window;
	int						bprogressup;
	int						nlastpct;
	long					pos;
	long					len;
	enum e_state			g_state;
	pthread_mutex_t			g_mutex;
	pthread_cond_t			g_cond_a;
	pthread_cond_t			g_cond_b;
}							t_progress_data;

typedef struct				s_light_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*x_label;
	GtkWidget				*y_label;
	GtkWidget				*z_label;
	GtkWidget				*translate_img;
	GtkWidget				*translate_x_spin;
	GtkWidget				*translate_y_spin;
	GtkWidget				*translate_z_spin;
	GtkWidget				*color;
}							t_light_view;

typedef struct				s_add_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*buttonbox;
	GtkWidget				*sphere_button;
	GtkWidget				*plane_button;
	GtkWidget				*cylinder_button;
	GtkWidget				*cone_button;
	GtkWidget				*obj_file_button;
	GtkWidget				*sphere_img;
	GtkWidget				*plane_img;
	GtkWidget				*cylinder_img;
	GtkWidget				*cone_img;
	GtkWidget				*obj_file_img;
	GtkWidget				*x_label;
	GtkWidget				*y_label;
	GtkWidget				*z_label;
	GtkWidget				*translate_img;
	GtkWidget				*rotate_img;
	GtkWidget				*scale_img;
	GtkWidget				*translate_x_spin;
	GtkWidget				*translate_y_spin;
	GtkWidget				*translate_z_spin;
	GtkWidget				*rotate_x_spin;
	GtkWidget				*rotate_y_spin;
	GtkWidget				*rotate_z_spin;
	GtkWidget				*scale_spin;
	GtkWidget				*vector_x;
	GtkWidget				*vector_y;
	GtkWidget				*vector_z;
	GtkWidget				*vector_img;
	GtkWidget				*inf_img;
	GtkWidget				*infinite;
	GtkWidget				*angle_img;
	GtkWidget				*angle_spin;
	GtkWidget				*ok_button;
	GtkWidget				*cancel_button;
	GtkWidget				*color;
	GtkWidget				*reflex_spin;
	GtkWidget				*reflex_img;
	t_switcher				sw;
	GtkWidget				*file_check;
	GtkWidget				*same;
	GtkWidget				*from_template;
	GtkWidget				*cube;
	GtkWidget				*cube_img;
	GtkWidget				*tetra;
	GtkWidget				*tetra_img;
	GtkWidget				*dode;
	GtkWidget				*dode_img;
	GtkWidget				*pyramid;
	GtkWidget				*pyramid_img;
	GtkWidget				*height_img;
	GtkWidget				*height_spin;
	GtkWidget				*file_opener;
	char					*obj_file_path;
	int						saved_type;
}							t_add_view;

typedef struct				s_main_view
{
	GtkWidget				*win;
	GtkWidget				*grid;
	GtkWidget				*buttonbox;
	GtkWidget				*list_button;
	GtkWidget				*add_button;
	GtkWidget				*add_img;
	GtkWidget				*filters_button;
	GtkWidget				*filters_img;
	GtkWidget				*select_button;
	GtkWidget				*select_img;
	GtkWidget				*export_button;
	GtkWidget				*export_img;
	GtkWidget				*render_area;
	GtkWidget				*event_box;
}							t_main_view;

typedef struct				s_ui
{
	t_main_view				main_view;
	t_add_view				add_view;
	t_light_view			light_view;
	t_filter_view			filter_view;
	t_scene_view			scene_view;
	t_progress_data			progress_data;
}							t_ui;

typedef struct				s_gtk_mgr
{
	cairo_surface_t			*pixmap;
	unsigned char			*saved;
	unsigned char			*buf;
	char					editmode;
	t_ui					ui;
}							t_gtk_mgr;

void						draw_px(unsigned char *buf, int x, int y,
t_rgb cols);
void						init_gtk_variables(void);
void						edit_win(t_obj *o, GtkWidget *parent);
void						filter_win(void);
void						redraw(bool display);
void						init_add_view(void);
void						on_key_press(GtkWidget *w, GdkEventKey *event);
void						handle_x_button(GtkWidget *w);
void						validate_edit(t_obj *o);
void						deactivate_buttons(GtkWidget *except);
void						deactivate_buttons_from_tp(GtkWidget *except);
void						handle_main_view(void);
void						handle_main_view_2(void);
void						handle_main_view_3(void);
void						add_view(void);
void						validate_objects(t_obj *o);
void						black_white(unsigned char *ptr);
void						sepia(unsigned char *ptr);
void						reversed(unsigned char *ptr);
void						get_color_values(t_rgb col, GdkRGBA *c);
void						init_rt(void);
void						open_file(void);
void						dialog_keyhook(GtkWidget *w, GdkEventKey *event);
void						init_scene_view(void);
void						append_column_with_text(GtkWidget *tree, char *text,
									GtkCellRenderer *renderer, int en_column);
void						scene_win(void);
gboolean					is_obj(int type);
void						progress_bar();
void						progress_thread_handler(gdouble x);
void						progress_main_handler();
unsigned char				*ft_ustrdup(unsigned char *s, int size);
void						edit_light(t_light *l, GtkWidget *parent);
void						add_height_spin(void);
void						init_light_view(void);
void						init_filter_img(void);
void						handle_reflex_edit(t_obj *o);
void						attach_base_elens_edit(t_obj *o);
void						handle_base_elems_edit(t_obj *o);
void						add_cube(void);
void						add_tetra(void);
void						add_dode(void);
void						add_height_spin(void);
void						add_pyramid(void);
void						radio_toggle_2(void);
void						radio_toggle(GtkWidget *button);
void						handle_cube_template(void);
void						for_template(void);
void						for_file(GtkWidget *button);
bool						go_throu_lights(t_light *curr);
void						init_scene_view2(GtkCellRenderer *render);
void						for_template(void);
void						handle_drawing_end(void);
void						edit_win_4(void);
void						edit_win_img_init(t_obj *o);
void						progress_bar_init(void);
void						end_filters2(void);
GtkWidget					*create_new_dialog(GtkWidget *parent);
void						handle_edit_reject(void);
void						setup_scrollbar(void);
void						create_inner_obj_for_type_end(t_obj *tmp, int type);

#endif
