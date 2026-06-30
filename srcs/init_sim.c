/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:29:51 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 22:39:59 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void assign_dongles(t_coder *coder, t_dongle *dongles, int pos)
{
	int coder_nbr;

	coder_nbr = coder->args.number_of_coders;
	coder->r_dongle = &dongles[(pos + 1) % coder_nbr];
	coder->l_dongle = &dongles[pos];
	if (coder->id % 2 == 0)
	{
		coder->r_dongle = &dongles[pos];
		coder->l_dongle = &dongles[(pos + 1) % coder_nbr];
	}
}

static void coder_init(t_sim *sim)
{
	int i;
	t_coder *coder;

	i = -1;
	while(++i < sim->args.number_of_coders)
	{
		coder = sim->coders + i;
		coder->id = i + 1;
		coder->compiles = 0;
		coder->done_compiling = false;
		coder->sim = sim;
		coder->args = sim->args;
		safe_mutex_handle(&coder->mutex, INIT);
		assign_dongles(coder, sim->dongles, i);
	}
}

/*
 * @brief initializes all coders, dongles and additional simulation variables
 * @param *sim pointer to the simulation struct
*/
void init_sim(t_sim *sim)
{
	int i;

	i = -1;
	sim->ended_sim = false;
	sim->all_threads_ready = false;
	sim->num_threads_run = 0;
	sim->coders = safe_malloc(sizeof(t_coder) * sim->args.number_of_coders);
	safe_mutex_handle(&sim->sim_mutex, INIT);
	safe_mutex_handle(&sim->write_mutex, INIT);
	sim->dongles = safe_malloc(sizeof(t_dongle) * sim->args.number_of_coders);
	while (++i < sim->args.number_of_coders)
	{
		safe_mutex_handle(&sim->dongles[i].dongle, INIT);
		sim->dongles[i].id = i;
	}
	coder_init(sim);
}
