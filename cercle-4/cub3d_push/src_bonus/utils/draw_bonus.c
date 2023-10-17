/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:37:28 by anshimiy          #+#    #+#             */
/*   Updated: 2023/10/07 13:26:13 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief  Using Bresenham's line drawing algorithm
 * @note
 * @param  *img:
 * @param  p1:
 * @param  p2:
 * @param  color:
 * @retval None
 */
void	draw_line(mlx_image_t *img, t_point p1, t_point p2, int color)
{
	t_line_data	line_data;

	lh_init(&line_data, &p1, &p2);
	while (1)
	{
		put_pixel(img, line_data.x, line_data.y, color);
		if ((line_data.x == p2.x) && (line_data.y == p2.y))
			break ;
		line_data.e2 = 2 * line_data.err;
		if (line_data.e2 >= line_data.dy)
		{
			line_data.err += line_data.dy;
			line_data.x += line_data.sx;
		}
		if (line_data.e2 <= line_data.dx)
		{
			line_data.err += line_data.dx;
			line_data.y += line_data.sy;
		}
	}
}

void	draw_rectangle(mlx_image_t *image, t_rectangle rec, uint32_t color)
	{
	int32_t	i;
	int32_t	j;

	i = rec.x;
	while (i < rec.width + rec.x)
	{
		j = rec.y;
		while (j < rec.height + rec.y)
		{
			put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	set_background(t_raycaster_data rc)
{
	draw_rectangle(rc.background, init_rectangle(0, 0, rc.screen_width,
			rc.screen_height / 2 + rc.vertical_view), rc.ceiling_color);
	draw_rectangle(rc.background, init_rectangle(0, rc.screen_height / 2
			+ rc.vertical_view, rc.screen_width, rc.screen_height / 2
			- rc.vertical_view), rc.floor_color);
}

void	draw_triangle(mlx_image_t *image, t_point points[3], uint32_t color)
{
	draw_line(image, points[0], points[1], color);
	draw_line(image, points[1], points[2], color);
	draw_line(image, points[2], points[0], color);
}

void	draw_pointer(t_raycaster_data *rc)
{
	int	to_remove_x;
	int	to_remove_y;
	int	abs_px;
	int	abs_py;

	abs_px = (int)floor(rc->px);
	abs_py = (int)floor(rc->py);
	to_remove_x = abs_px + (int)round(rc->pdx);
	to_remove_y = abs_py + (int)round(rc->pdy);
	if (rc->map[to_remove_y][to_remove_x] == 1 && block_forbidden(rc,
			to_remove_x, to_remove_y) == 0)
		draw_rectangle(rc->screen, init_rectangle(rc->screen_width / 2,
				rc->screen_height / 2, 5, 5), GREEN);
	else if (block_forbidden(rc, to_remove_x, to_remove_y) == 1)
		draw_rectangle(rc->screen, init_rectangle(rc->screen_width / 2,
				rc->screen_height / 2, 5, 5), RED);
	else
		draw_rectangle(rc->screen, init_rectangle(rc->screen_width / 2,
				rc->screen_height / 2, 5, 5), WHITE);
}
