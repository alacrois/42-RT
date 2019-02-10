/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:01:24 by alacrois          #+#    #+#             */
/*   Updated: 2019/02/07 17:11:03 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <libft.h>
#include <parser/parser.h>

void			check_and_free_vlist(t_vertex **v_list, t_poly_obj *obj)
{
	t_vertex	*tmp;
	t_vertex	*tmp_next;

	tmp = *v_list;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp_next;
	}
	if (obj == NULL)
		ft_exit("parsing failed", 1);
}

static bool		get_next_double_2(char *line, int *index, \
									double *a, double sign)
{
	int			digit_index;
	double		tmp;

	tmp = 0;
	while (ft_isdigit(line[*index]) == 1)
	{
		tmp = (tmp * 10) + (double)(line[*index] - '0');
		(*index)++;
	}
	if (line[*index] != '.')
	{
		*a = tmp * sign;
		return (true);
	}
	(*index)++;
	digit_index = 1;
	while (ft_isdigit(line[*index]) == 1)
	{
		tmp = tmp + ((double)(line[*index] - '0') / pow(10, digit_index));
		(*index)++;
		digit_index++;
	}
	*a = tmp * sign;
	return (true);
}

bool			get_next_double(char *line, int *index, double *a)
{
	double		sign;

	sign = 1;
	while (line[*index] != '-' && ft_isdigit(line[*index]) == 0
		&& line[*index] != '\0')
		(*index)++;
	if (line[*index] == '-')
	{
		sign = -1;
		(*index)++;
	}
	if (line[*index] == '\0')
		return (false);
	if (ft_isdigit(line[*index]) == 0)
		return (get_next_double(line, index, a));
	return (get_next_double_2(line, index, a, sign));
}

static	void	get_face_maxd(t_vertex *f, double *d)
{
	double		tmp_d;
	double		tmp;

	tmp_d = 0;
	while (f != NULL)
	{
		tmp = sqrt(deltasq(set_rpoint(0, 0, 0), f->p));
		if (tmp_d < tmp)
			tmp_d = tmp;
		f = f->next;
	}
	if (tmp_d > *d)
		*d = tmp_d;
}

void			set_obj(t_obj *o)
{
	t_poly_obj	*tmp;
	t_vertex	*face;
	t_rpoint	pos;
	double		tmp_d;

	tmp = (t_poly_obj *)o->obj;
	tmp_d = 0;
	while (tmp != NULL)
	{
		face = tmp->vertices;
		pos = o->position;
		get_face_maxd(face, &tmp_d);
		face->pl.vector = cross_product(get_vector(face->p, face->next->p), \
									get_vector(face->p, face->next->next->p));
		tmp = tmp->next;
	}
	((t_poly_obj *)o->obj)->max_d = tmp_d;
}
