/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 15:30:38 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/07 15:17:09 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
 * @brief simple malloc safety wrapper
 * @param bytes number of bytes to alocate
 * @return allocated container for n bytes
 */
void	*safe_malloc(size_t bytes)
{
	void	*container;

	container = malloc(bytes);
	if (container == NULL)
		error_exit("Allocation error.", NULL);
	return (container);
}

// *** Mutexes ***
/*
 * init
 * destroy
 * lock
 * unlock
 */
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.", NULL);
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.", NULL);
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread "
					"blocked waiting for mutex.",
					NULL);
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock mutex.", NULL);
	else if (status == ENOMEM)
		error_exit("The proccess cannot allocate memory to "
					"create another mutex.",
					NULL);
	else if (status == EBUSY)
		error_exit("Mutex is locked", NULL);
}

/*
 * @brief A safe hadler for mutexes
 * @param *mutex the pointer to the mutex to handle
 * @param opcode code of type enum t_opcode to decide the handling
 */
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid optcode for mutex handling", NULL);
}

// *** Threads ***
/*
 * create
 * join
 * detach
 */
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread", NULL);
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n", NULL);
	if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.", NULL);
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable\n", NULL);
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that "
					"specified by given thread ID, thread.",
					NULL);
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of "
					"thread specifies the calling thread.",
					NULL);
}

/*
 * @brief A safe hadler for threads
 * @param *thread the pointer to the thread to handle
 * @param *f pointer to the function the thread will run
 * @param data the data the thread will use on the function
 * @param opcode code of type enum t_opcode to decide the handling
 */
void	safe_thread_handle(pthread_t *thread, void *(*f)(void *), void *data,
		t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, f, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Invalid optcode for mutex handling", NULL);
}
