/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:11:50 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/01 12:11:56 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void	wait_all_threads(t_sim *sim)
{
	while (!get_bool(&sim->sim_mutex, &sim->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads, long number_of_coders)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == number_of_coders)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increment_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}
