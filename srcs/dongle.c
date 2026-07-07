/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:22:47 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/07 15:16:52 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
 * @brief requests <dongle>, checks for dongle cooldown and end of simulation
 * @param dongle the dongle which it will request
 * @param *sim a pointer to the simulation struct
 * @return true if it the request was successful and false if the
 * simulation ended while/when request(ing)/(ed)
 */
bool	request_dongle(t_dongle *dongle, t_sim *sim)
{
	safe_mutex_handle(&dongle->dongle, LOCK);
	while (!sim_ended(sim) && (dongle->taken
			|| gettime(MILISEC) < dongle->cooldown_until))
	{
		if (dongle->taken)
			safe_cond_handle(&dongle->cond, &dongle->dongle, 0, WAIT);
		else
			safe_cond_handle(&dongle->cond, &dongle->dongle,
				dongle->cooldown_until, TIMEDWAIT);
	}
	if (sim_ended(sim))
	{
		safe_mutex_handle(&dongle->dongle, UNLOCK);
		return (false);
	}
	dongle->taken = true;
	safe_mutex_handle(&dongle->dongle, UNLOCK);
	return (true);
}

/*
 * @brief releases the dongle
 * @param dongle the dongle which it will be released
 * @param *sim a pointer to the simulation struct
 */
void	release_dongle(t_dongle *dongle, t_sim *sim)
{
	safe_mutex_handle(&dongle->dongle, LOCK);
	dongle->taken = false;
	dongle->cooldown_until = gettime(MILISEC) + sim->args.dongle_cooldown;
	safe_cond_handle(&dongle->cond, &dongle->dongle, 0, BROADCAST);
	safe_mutex_handle(&dongle->dongle, UNLOCK);
}
