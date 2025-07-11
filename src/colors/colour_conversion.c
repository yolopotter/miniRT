/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:50:00 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/03 21:50:03 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Fills pointed t_color 's rgba array with valid RGBA255 values
 * @param [in] *c: pointer to valid t_color type
 */
void	colour_unitrgb_rgba(t_color *c)
{
	c->rgba[0] = (uint8_t)round(fmax(fmin(c->r * 255, 255), 0));
	c->rgba[1] = (uint8_t)round(fmax(fmin(c->g * 255, 255), 0));
	c->rgba[2] = (uint8_t)round(fmax(fmin(c->b * 255, 255), 0));
	if (c->a < 0 || c->a > 1)
		c->a = 1;
	c->rgba[3] = (uint8_t)round(fmax(fmin(c->a * 255, 255), 0));
}

/**
 * @brief Returns a 32 bit integer containing MLX colour value. Converts from
 * 		  (ideal) [0,1] ranged unit RGB colour values.
 * @param [in] c: a valid t_color type
 * @param [in] alpha: a valid unit RGB [0,1] alpha value
 */
uint32_t	colour_unitrgb_hex(t_color c, float alpha)
{
	if (alpha < 0 || alpha > 1)
		c.a = 1;
	else
		c.a = alpha;
	colour_unitrgb_rgba(&c);
	c.hex = c.rgba[0] << 24 | c.rgba[1] << 16 | c.rgba[2] << 8 | c.rgba[3];
	return (c.hex);
}

void	color_convert(t_scene_obj *obj)
{
	obj->mat.col.r = obj->col.r;
	obj->mat.col.g = obj->col.g;
	obj->mat.col.b = obj->col.b;
}
