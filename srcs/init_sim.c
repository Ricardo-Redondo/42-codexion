/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:29:51 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 16:37:39 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void init_sim(t_sim *sim)
{
	int i;

	i = -1;
	sim->end_sim = false;
	sim->coders = safe_malloc(sizeof(sim->args.number_of_coders));
	sim->dongles = safe_malloc(sizeof(sim->args.number_of_coders));
	while (++i < sim->args.number_of_coders)
	{
		safe_mutex_handle(&sim->dongles[i].dongle, INIT);
		sim->dongles[i].id = i;
	}
}
