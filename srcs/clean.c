/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:23:40 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/07 15:16:49 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	free_dongle(t_dongle *dongle)
{
	safe_mutex_handle(&dongle->dongle, DESTROY);
	safe_cond_handle(&dongle->cond, &dongle->dongle, 0, DESTROY);
}

void	clean_sim(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->args.number_of_coders)
		safe_thread_handle(&sim->coders[i].thread_id, NULL, NULL, JOIN);
	set_bool(&sim->sim_mutex, &sim->ended_sim, true);
	safe_thread_handle(&sim->monitor, NULL, NULL, JOIN);
	i = -1;
	while (++i < sim->args.number_of_coders)
	{
		free_dongle(&sim->dongles[i]);
		safe_mutex_handle(&sim->coders[i].mutex, DESTROY);
	}
	safe_mutex_handle(&sim->sim_mutex, DESTROY);
	safe_mutex_handle(&sim->write_mutex, DESTROY);
	free(sim->coders);
	free(sim->dongles);
}
