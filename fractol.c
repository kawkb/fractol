/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrissi- <kdrissi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:21:03 by kdrissi-          #+#    #+#             */
/*   Updated: 2022/06/26 03:09:30 by kdrissi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		count_iter(float re, float img)
{
	float 	x;
	float 	y;
	int		iter;
	float	xtemp;
	
	iter = 0;
	xtemp = 0;
	x = 0;
	y = 0;
	while (x * x + y * y < 4 && iter < MAX_ITER)
	{
		xtemp = (x * x) - (y * y) + re;
		y = 2 * x * y + img;
		x = xtemp;
		iter++;
	}
	return (iter);
}


void	escape_time(t_data *data, t_cord cord)
{
	int		i;
	int		j;
	float	real;
	float	imginary;
	int		iter;
	int		color;

	i = 0;
	while(i < HEIGHT)
	{
		j = 0;
		real = cord.min_re + (i * (cord.max_re - cord.min_re) / HEIGHT);
		while(j < WIDTH)
		{
			imginary = cord.max_im - (j * (cord.max_im - cord.min_im) / WIDTH);
			iter = count_iter(real, imginary);
			if (iter == MAX_ITER)
				my_mlx_pixel_put(data, i, j, create_trgb(0, 0, 0, 0));
			else if (iter >= MAX_ITER / 2)
				my_mlx_pixel_put(data, i, j, create_trgb(0, 0, 255, 0));
			else if (iter >= MAX_ITER / 4)
				my_mlx_pixel_put(data, i, j, create_trgb(0, 255, 0, 0));
			else
				my_mlx_pixel_put(data, i, j, create_trgb(0, 0, 0, 255));
			j++;
		}
			printf("\n");
		i++;
	}
}
void	apply_zoom(t_mlx *mlx,t_cord  cord)
{
	t_data	data;

	data.img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);
	escape_time(&data, cord);
	mlx_put_image_to_window(mlx->ptr, mlx->win, data.img, 0, 0);
	mlx_destroy_image(mlx->ptr, data.img);
}

void	zoom(int x, int y, t_mlx *mlx, int dir)
{
	t_cord  cord;
	float  	mouse_re;
	float	mouse_im;
	float stepx;
	float stepy;
	static float max_re = 2.0;
	static float min_re = -2.0;
	static float max_im = 2.0;
	static float min_im = -2.0;

	mouse_re = (x * (max_re - min_re) / WIDTH) + min_re;
	mouse_im = (y * (max_im - min_im) / HEIGHT) + min_im;
	stepx = (max_re - mouse_re) / 10;
	// stepy = (max_im - mouse_im) / 10;
	if (dir == 4)
	{
		max_re -= 0.5;
		min_re += 0.5;
		max_im -= 0.5;
		min_im += 0.5;
	}
	if (dir == 5)
	{
		max_re += 0.5;
		min_re -= 0.5;
		max_im += 0.5;
		min_im -= 0.5;
	}
	cord.max_re = max_re;
	cord.min_re = min_re;
	cord.max_im = max_im;
	cord.min_im = min_im;
	apply_zoom(mlx, cord);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4)
		zoom(x, y, mlx, 4);
	else if (button == 5)
		zoom(x, y, mlx, 5);
	return (0);
}

void	mandelbrot(t_mlx *mlx)
{
	zoom(0, 0, mlx, 0);
	mlx_hook(mlx->win, 17, 1L << 17, exit_success, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_loop(mlx->ptr);
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	
	if (ac == 2 && (ft_strcmp(av[1], "Mandelbrot") == 0 || ft_strcmp(av[1], "Julia")))
	{
		mlx = malloc(sizeof(t_mlx));
		mlx->ptr = mlx_init();
		mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Fractol");
		if (ft_strcmp(av[1], "Mandelbrot") == 0)
			mandelbrot(mlx);
		// else
		// 	julia(mlx);
	}
	else
		printf("Usage: ./fractol <fractol_name>\n<fractol_name> options:\nMandelbrot\nJulia\n");
	return (0);
}