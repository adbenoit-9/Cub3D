/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Adeline <Adeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:45:39 by adbenoit          #+#    #+#             */
/*   Updated: 2020/05/28 19:00:52 by Adeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include "get_next_line.h"
# include <math.h>
# include "error.h"
# include "key.h"
# include "cub3d_macros.h"
# include "cub3d_struct.h"

# define TRUE 1
# define FALSE 0

void			init_game(t_all **all);
void    		finish_init(t_all **all, t_sprite *sp);
void 			init_player(t_all **all, char o);
int				mlx_handle(t_all *all);

//utils
double			**realloc_doub(double **ptr, int newsize);
void			all_null(t_all **all);
void			clear_sprites(t_all **all);
void			clear_textures(t_all **all);
void			clear_img(t_all **all);
void			clear_utils(t_all **all);
void			exit_error(t_all **all, char *line, int err);
void			exit_game(t_all **all);
void			free_tab_char(char **ptr, int alloc);
void			free_tab_nb(void **ptr, int size, int alloc);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_putnbr_fd(int n, int fd);
void			*ft_realloc(void *ptr, int newsize);
void			print_error(int err);
char			*ft_strtrim(char *s1, char const *set, int size);
char			**realloc_tab(char **ptr, int newsize);
int				ft_atoi(const char *str);
int				ft_rgb(int r, int g, int b);
int				ft_strlen(char *str);
int				ft_strncmp(char *s1, char *s2, int n);


//move
void			ft_turnleft(t_all **all);
void			ft_turnright(t_all **all);
void			ft_forward(t_all **all);
void			ft_backward(t_all **all);
void			ft_rightward(t_all **all);
void			ft_leftward(t_all **all);

//parsing
int				parse_color(t_all **all, char *line, int ident);
int				parse_res(t_all **all, char *line);
int				ft_parsing(t_all **all);
int				info(char *line, t_all **all);
int				map(char *line, t_all **all);
int				check_map_border(t_all **all);
int				check_line_border(t_all **all);
int				open_f(char *arg, t_all **all, int save);

//raycasting
double			dist_screen(t_all **all, int x, int y);
double			set_wall_dist(t_all **all, t_wall *wall);
void			add_dist(t_all **all, t_sprite *sp, void (*sort)(t_sprite *));
void			complete_text(t_all **all);
void			init_wall(t_all **all, t_wall *wall);
void			ft_move(t_all **all);
void			draw_wall(t_all **all);
void			set_wall_side(t_all **all);
void			draw_sprite(t_all **all, t_sprite *sp);
void    		load_image(t_all **all, t_img *img, char *path);
void			load_tab_of_image(t_all **all, t_tab_img *tab_img, char **path, int start_game);
void			raycast_sprite(t_all **all, t_sprite *sp, t_img *sp_img);
void			draw_wall_pixel(t_all **all, int i);
void			save_bmp(t_all **all);
void			set_side_dist(t_all **all, t_wall *wall);
void			sort_sprite(t_sprite *sp);
void			start_game(t_all **all);
int				create_image(t_all **all);
int				ft_close(t_all **all);
int 			key_init(t_all **all);
int				ft_key_release(int key, t_all **all);
int				ft_key_press(int key, t_all **all);


//bonus
void			draw_mini_map(t_all **all);
void 			check_door(t_all **all);
void			open_door(t_all **all);
void			ft_door(t_all **all);
void			init_game_sprite(t_all **all, t_sprite *sp);
void    		manage_life(t_all **all, char c);
void			draw_all_sprites(t_all **all, t_sprite *sp);
void    		draw_replay(t_all **all, t_img *im, int k1, int k2);
void    		draw_hearts(t_all **all);
void    		draw_weapon(t_all **all);
void			put_all_sprites(t_all **all);
void			put_door(t_all **all);
int				bonus(char *line, t_all **all);
int     		ft_mouse(int button, int x, int y, t_all **all);

#endif
