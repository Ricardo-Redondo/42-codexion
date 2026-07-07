/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:27:33 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/07 15:32:58 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
 * INIT
 * DESTROY
 * WAIT
 * TIMEDWAIT
 * BROADCAST
 */
static void	handle_cond_error(int status, t_opcode opcode)
{
	if (status == ETIMEDOUT || status == 0)
		return ;
	if (status == EAGAIN && (opcode == INIT || opcode == DESTROY))
		error_exit("The system lacked the necessary resources (other than "
			"memory) to initialize another condition variable.", NULL);
	else if (status == ENOMEM && opcode == INIT)
		error_exit("Insufficient memory exists to initialize the "
			"condition variable.", NULL);
	else if (status == ENOTRECOVERABLE)
		error_exit("The state protected by the mutex is not recoverable.",
			NULL);
	else if (status == EOWNERDEAD)
		error_exit("The mutex is a robust mutex and the process containing the "
			"previous owning thread terminated while holding the mutex lock. "
			"The mutex lock shall be acquired by the calling thread and it is "
			"up to the new owner to make the state consistent.", NULL);
	else if (status == EPERM)
		error_exit("The mutex type is PTHREAD_MUTEX_ERRORCHECK or the mutex is "
			"a robust mutex, and the current thread does not own the mutex.",
			NULL);
	else if (status == EINVAL)
		error_exit("The abstime argument specified a nanosecond value less "
			"than zero or greater than or equal to 1000 million.", NULL);
}

/*
 * @brief creates an instance of struct timespec with <ms> values
 * @param ms time to be converted to seconds and nanoseconds for the struct
 * @return the instance of struct timespec
 */
static struct timespec	ms_to_timespec(long ms)
{
	struct timespec	ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	return (ts);
}

/*
 * @brief A safe hadler for conds
 * @param *cond the pointer to the cond to handle
 * @param *mutex pointer to the mutex of the cond
 * @param deadline_ms the deadline for pthread_cond_timedwait
 * 		  (0 if using diferent opcode)
 * @param opcode code of type enum t_opcode to decide the handling
 */
void	safe_cond_handle(t_cond *cond, t_mtx *mutex, long deadline_ms,
		t_opcode opcode)
{
	struct timespec	ts;

	if (opcode == INIT)
		handle_cond_error(pthread_cond_init(cond, NULL), INIT);
	else if (opcode == DESTROY)
		handle_cond_error(pthread_cond_destroy(cond), DESTROY);
	else if (opcode == WAIT)
		handle_cond_error(pthread_cond_wait(cond, mutex), WAIT);
	else if (opcode == TIMEDWAIT)
	{
		ts = ms_to_timespec(deadline_ms);
		handle_cond_error(pthread_cond_timedwait(cond, mutex, &ts), TIMEDWAIT);
	}
	else if (opcode == BROADCAST)
		handle_cond_error(pthread_cond_broadcast(cond), BROADCAST);
	else
		error_exit("Invalid optcode for cond handling", NULL);
}
