#ifndef FRACTOL_H
#define FRACTOL_H
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITER 500

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx {
	void	*ptr;
	void	*win;
}	
			t_mlx;

typedef struct s_cord {
	float	max_re;
	float	min_re;
	float	max_im;
	float	min_im;
}				t_cord;

int 	ft_strlen(char *str);
int		ft_strcmp(char *s1,  char *s2);
int		exit_success(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_pressed(int key, t_mlx *mlx);
int		create_trgb(int t, int r, int g, int b);
#endif