/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 14:04:59 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/08 12:01:32 by rsao-pay         ###   ########.fr       */
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
typedef struct s_coder	t_coder;

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

// coder status
typedef enum e_status
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
	TAKE_DONGLE,
	BURNED_OUT
}						t_status;

// opcodes
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
	WAIT,
	TIMEDWAIT,
	BROADCAST
}						t_opcode;

// time codes
typedef enum e_time_code
{
	MILISEC,
	MICROSEC
}						t_time_code;

// schedulers
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

// heap
typedef struct s_node
{
	t_coder				*coder;
	long				key;
}						t_node;

typedef struct s_heap
{
	t_node				*nodes;
	long				size;
	t_scheduler			shceduler;
}						t_heap;

// dongle
typedef struct s_dongle
{
	t_mtx				dongle;
	t_cond				cond;
	int					id;
	bool				taken;
	long				cooldown_until;
	long				next_ticket;
	t_heap				heap;
}						t_dongle;

// coder
struct					s_coder
{
	int					id;
	pthread_t			thread_id;
	t_mtx				mutex;
	long				compiles;
	long				last_compile;
	bool				done_compiling;
	t_dongle			*l_dongle;
	t_dongle			*r_dongle;
	t_args				args;
	t_sim				*sim;
};

// simulation
struct					s_sim
{
	t_args				args;
	bool				all_threads_ready;
	bool				ended_sim;
	long				start_sim;
	long				num_threads_run;
	t_mtx				sim_mutex;
	t_mtx				write_mutex;
	pthread_t			monitor;
	t_coder				*coders;
	t_dongle			*dongles;
};

// *** functions ***

// parser
void					parser(int argc, char **argv, t_args *args);

// init
void					init_sim(t_sim *sim);

// clean
void					clean_sim(t_sim *sim);

// sim
void					start_sim(t_sim *sim);
void					*single_coder(void *data);
bool					request_dongle(t_dongle *dongle, t_sim *sim);
void					release_dongle(t_dongle *dongle, t_sim *sim);

// monitor
void					*monitor_sim(void *data);

// safe functions
void					*safe_malloc(size_t bytes);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread,
							void *(*f)(void *), void *data, t_opcode opcode);
void					safe_cond_handle(t_cond *cond, t_mtx *mutex,
							long deadline_ms, t_opcode opcode);

// setter/getter
void					set_bool(t_mtx *mutex, bool *dst, bool value);
void					set_long(t_mtx *mutex, long *dst, long value);
bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
bool					sim_ended(t_sim *sim);

// write status
void					write_status(t_status status, t_coder *coder);

// utils
void					error_exit(const char *error, const char *arg);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_sim *sim);

// sync utils
void					wait_all_threads(t_sim *sim);
void					increment_long(t_mtx *mutex, long *value);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long number_of_coders);

#endif