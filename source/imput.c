/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imput.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:41:15 by jrinna            #+#    #+#             */
/*   Updated: 2023/08/02 13:16:00 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_imput_cylinder(int key, t_var *m)
{
	static int	i = 0;

	if (key == K_SPHERE)
		return (1);
	if (key == K_CAMERA)
		return (0);
	if (key == K_PLANE)
		return (3);
	if (key == K_LIGHT)
		return (4);
	if (key == K_PLUS)
		i++;
	if (key == K_MINUS)
		i--;
	if (i > m->ele.cy - 1)
		i = 0;
	if (i < 0)
		i = m->ele.cy - 1;
	ft_change_cylinder(key, m, i);
	dprintf(1, "cylinder %d i = %d\n", key, i);
	return (2);
}

int	ft_imput_plane(int key, t_var *m)
{
	static int	i = 0;

	if (key == K_SPHERE)
		return (1);
	if (key == K_CYLINDER)
		return (2);
	if (key == K_CAMERA)
		return (0);
	if (key == K_LIGHT)
		return (4);
	if (key == K_PLUS)
		i++;
	if (key == K_MINUS)
		i--;
	if (i > m->ele.pl - 1)
		i = 0;
	if (i < 0)
		i = m->ele.pl - 1;
	ft_change_plane(key, m, i);
	dprintf(1, "plane %d i = %d\n", key, i);
	return (3);
}

int	ft_imput_light(int key, t_var *m)
{
	if (key == K_SPHERE)
		return (1);
	if (key == K_CYLINDER)
		return (2);
	if (key == K_PLANE)
		return (3);
	if (key == K_CAMERA)
		return (0);
	ft_change_light(key, m);
	dprintf(1, "light %d\n", key);
	return (4);
}

int	ft_imput_camera(int key, t_var *m)
{
	static int	i = 0;

	dprintf(1, "camera : %d i = %d\n", key, i);
	if (key == K_SPHERE)
		return (1);
	if (key == K_CYLINDER)
		return (2);
	if (key == K_PLANE)
		return (3);
	if (key == K_LIGHT)
		return (4);
	if (key == K_RIGHT)
		m->ele.struc_c.angle_x += -5 * (2 * PI / 360);
	if (key == K_LEFT)
		m->ele.struc_c.angle_x += 5 * (2 * PI / 360);
	if (key == K_UP)
		m->ele.struc_c.angle_z += -5 * (2 * PI / 360);
	if (key == K_DOWN)
		m->ele.struc_c.angle_z += 5 * (2 * PI / 360);
	if (key == K_FRONT)
		ft_move_cam(m, 1);
	if (key == K_BACK)
		ft_move_cam(m, -1);
	return (0);
}

int	ft_imput_first(int key, void *mm)
{
	t_var		*m;
	static int	i = 0;

	m = (t_var *)mm;
	dprintf(1, "start%d mode = %d\n", key, i);
	if (key == K_ESC)
		ft_exit (0);
	else if (i == 0)
		i = ft_imput_camera(key, m);
	else if (i == 1)
		i = ft_imput_sphere(key, m);
	else if (i == 2)
		i = ft_imput_cylinder(key, m);
	else if (i == 3)
		i = ft_imput_plane(key, m);
	else if (i == 4)
		i = ft_imput_light(key, m);
	dprintf(1, "end%d mode = %d\n", key, i);
	return (0);
}
