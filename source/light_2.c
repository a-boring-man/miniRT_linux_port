/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:50:05 by jrinna            #+#    #+#             */
/*   Updated: 2022/07/01 15:36:52 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_light_inter_sph(t_var *m, t_line l, float coef)
{
	int		n;
	t_inter	tool;
	t_sp	s;

	n = m->ele.sp;
	while (n)
	{
		s = m->ele.struc_sp[n - 1];
		if (secure_glitch_sphere(s, l.point) || ((in_sphere
					(s, m->ele.struc_c.coord) ^ in_sphere(s, l.point))))
			return (1);
		tool = inter_sphere(l, s);
		if (tool.exist && (tool.dist - coef < -0.0001))
			return (1);
		n--;
	}
	return (0);
}

bool	in_cylinder(t_cy c, t_coord point)
{
	float	proj;
	t_vec	tool;

	if (side_plan(c.plan_down, point) && side_plan(c.plan_up, point))
	{
		tool = find_normal_line(cy_line(c), point, &proj);
		proj = ft_square_length(tool);
		if (proj - (c.diam * c.diam / 4) < -0.01)
			return (1);
	}
	return (0);
}

bool	secure_glitch_cylinder(t_cy c, t_coord point)
{
	float	proj;
	t_vec	tool;

	if (secure_glitch_plan(c.plan_up, point)
		|| secure_glitch_plan(c.plan_down, point))
	{
		tool = find_normal_line(cy_line(c), point, &proj);
		proj = ft_square_length(tool);
		if (proj - (c.diam * c.diam / 4) < 0.001)
			return (1);
		return (0);
	}
	if (side_plan(c.plan_down, point) && side_plan(c.plan_up, point))
	{
		tool = find_normal_line(cy_line(c), point, &proj);
		proj = ft_square_length(tool) - (c.diam * c.diam / 4);
		if (proj < 0.001 && proj > -0.001)
			return (1);
	}
	return (0);
}

bool	check_light_inter_cyl(t_var *m, t_line l, float coef)
{
	int		n;
	t_inter	tool;
	t_cy	c;

	n = m->ele.cy;
	while (n)
	{
		c = m->ele.struc_cy[n - 1];
		if (secure_glitch_cylinder(c, l.point)
			|| (in_cylinder(c, m->ele.struc_c.coord) ^ in_cylinder(c, l.point)))
			return (1);
		tool = inter_cylinder(l, c);
		if (tool.exist && (tool.dist - coef < -0.01))
			return (1);
		n--;
	}
	return (0);
}

bool	ft_inter_light(t_var *m, t_l light, t_inter inter, float *ratio)
{
	t_line	l_line;
	float	lg_segment;
	float	ratio_l;

	*ratio = 0;
	l_line.point = light.coord;
	l_line.dir = crea_vector(light.coord, inter.point);
	ft_vec_normalization(&l_line.dir);
	lg_segment = coef_point(inter.point, l_line);
	if (ft_check_check(m, l_line, lg_segment))
		return (0);
	ratio_l = ft_dot_product(l_line.dir, inter.normal);
	*ratio = -ratio_l / (pow(inter.point.x - light.coord.x, 2)
			+ pow(inter.point.y - light.coord.y, 2) + pow(inter.point.z
				- light.coord.z, 2));
	return (1);
}
