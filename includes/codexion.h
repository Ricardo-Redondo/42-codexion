/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:04:59 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/05/21 12:51:00 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}					t_scheduler;

typedef enum e_node_type
{
	CODER,
	DONGLE
}					t_node_type;

typedef struct s_args
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
}					t_args;

typedef struct s_node
{
	t_node_type		type;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_coder
{
	t_node			node;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				time_to_burnout;
	int				index;
	int				priority;
	int				(*get_time_to_burnout)(struct s_coder *this);
	void			(*queue)(struct s_coder *this);
	void			(*proccess)(void *this);
}					t_coder;

typedef struct s_dongle
{
	t_node			node;
	int				dongle_cooldown;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}					t_dongle;

typedef struct s_sim
{
	t_args			args;
	t_node			*head;
}					t_sim;

int					parser(int argc, char **argv, t_args *args);
int					init_sim(t_sim *sim);
void				free_list(t_sim *sim);
void				*create_node(t_node_type type);
void				add_node(t_node *node, t_sim *sim, int is_last);
void				*(*coder_schedule(void *arg))(t_coder *coder);

#endif