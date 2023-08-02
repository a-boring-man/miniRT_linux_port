/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:16:04 by jrinna            #+#    #+#             */
/*   Updated: 2023/08/02 11:41:57 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	ft_atol(char *string, float *r)
{
	int		i;
	int		counter;
	int		signe;
	long	nbr;

	i = 0;
	counter = 0;
	signe = 1;
	nbr = 0;
	while ((string[i] > 8 && string[i] < 14) || string[i] == 32)
		i++;
	while ((string[i] == 43 || string[i] == 45) && counter == 0)
	{
		counter++;
		if (string[i] == 45)
			signe = -signe;
		i++;
	}
	while (string[i] > 47 && string[i] < 58)
	{
		nbr = nbr * 10 + (string[i] - '0');
		i++;
	}
	*r = signe * nbr;
	return (1);
}

int	ft_atoi(char *string)
{
	int	i;
	int	counter;
	int	signe;
	int	nbr;

	i = 0;
	counter = 0;
	signe = 1;
	nbr = 0;
	while ((string[i] > 8 && string[i] < 14) || string[i] == 32)
		i++;
	while ((string[i] == 43 || string[i] == 45) && counter == 0)
	{
		counter++;
		if (string[i] == 45)
			signe = -signe;
		i++;
	}
	while (string[i] > 47 && string[i] < 58)
	{
		nbr = nbr * 10 + (string[i] - '0');
		i++;
	}
	return (signe * nbr);
}

static float	ft_atof_suite(float r, float tmp, char *line, char **split)
{
	int		i;

	i = 0;
	if (split[1])
		i = ft_strlen_s(split[1]);
	else
		i = ft_strlen_s(split[0]);
	ft_free_split(split);
	while (i--)
		tmp *= 0.1;
	if (line[0] == '-')
		r -= tmp;
	else
		r += tmp;
	return (r);
}

float	ft_atof(char *line)
{
	float	r;
	float	second;
	float	tmp;
	char	**split;

	r = 0;
	tmp = 0;
	second = 0;
	if (!ft_strchr(line, '.') && ft_atol(line, &r))
		return (r);
	split = ft_split(line, '.');
	if (!(!split[1] && ft_strchr(line, '.') == line))
		ft_atol(split[0], &r);
	if (split[1])
		ft_atol(split[1], &second);
	else if (ft_strchr(line, '.') == line)
		ft_atol(split[0], &second);
	tmp = second;
	return (ft_atof_suite(r, tmp, line, split));
}
