/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:04:59 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 16:34:55 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// *** defines and typedefs ***

typedef pthread_mutex_t	t_mtx;
typedef pthread_cond_t	t_cond;
typedef struct s_sim	t_sim;

// colors
# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

// *** structs ***

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opcode;

// scheduler
typedef enum e_scheduler
{
	FIFO,
	EDF
}						t_scheduler;

// args
typedef struct s_args
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	t_scheduler			scheduler;
}						t_args;

// dongle
typedef struct s_dongle
{
	t_mtx				dongle;
	int					id;
	int					dongle_cooldown;
	t_cond				cond;
}						t_dongle;

// coder
typedef struct s_coder
{
	int					id;
	pthread_t			thread_id;
	t_dongle			*l_dongle;
	t_dongle			*r_dongle;
	int					time_to_burnout;
	int					index;
	int					priority;
	t_sim				*sim;
}						t_coder;

// simulation
struct					s_sim
{
	t_args				args;
	bool				end_sim;
	t_coder				*coders;
	t_dongle			*dongles;
};

// *** functions ***

// parser
int						parser(int argc, char **argv, t_args *args);

// safe functions
void					*safe_malloc(size_t bytes);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread,
							void *(*f)(void *), void *data, t_opcode opcode);

// utils
void					error_exit(const char *error, const char *arg);

#endif