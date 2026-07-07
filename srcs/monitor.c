/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 22:35:45 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/07 15:17:04 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	coder_burned_out(t_coder *coder)
{
	long	elapsed;
	long	t_burnout;

	if (get_bool(&coder->mutex, &coder->done_compiling))
		return (false);
	elapsed = gettime(MILISEC) - get_long(&coder->mutex, &coder->last_compile);
	t_burnout = coder->args.time_to_burnout / 1e3;
	if (elapsed > t_burnout)
		return (true);
	return (false);
}

void	*monitor_sim(void *data)
{
	int		i;
	t_sim	*sim;

	sim = (t_sim *)data;
	while (!all_threads_running(&sim->sim_mutex, &sim->num_threads_run,
			sim->args.number_of_coders))
		;
	while (!sim_ended(sim))
	{
		i = -1;
		while (++i < sim->args.number_of_coders && !sim_ended(sim))
		{
			if (coder_burned_out(sim->coders + i))
			{
				set_bool(&sim->sim_mutex, &sim->ended_sim, true);
				write_status(BURNED_OUT, sim->coders + i);
			}
		}
	}
	return (NULL);
}
