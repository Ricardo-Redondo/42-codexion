/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 21:24:18 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/01 12:11:48 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void	write_status(t_status status, t_coder *coder)
{
	long	elapsed;

	elapsed = gettime(MILISEC) - coder->sim->start_sim;
	safe_mutex_handle(&coder->sim->write_mutex, LOCK);
	if (status == TAKE_DONGLE && !sim_ended(coder->sim))
		printf(WHITE "%-6ld" RESET " %d has taken a dongle\n", elapsed,
			coder->id);
	else if (status == DEBUGGING && !sim_ended(coder->sim))
		printf(WHITE "%-6ld" RESET " %d is debuggins\n", elapsed, coder->id);
	else if (status == COMPILING && !sim_ended(coder->sim))
		printf(WHITE "%-6ld" CYAN " %d is compiling\n" RESET, elapsed,
			coder->id);
	else if (status == REFACTORING && !sim_ended(coder->sim))
		printf(WHITE "%-6ld" RESET " %d is refactoring\n", elapsed, coder->id);
	else if (status == BURNED_OUT)
		printf(WHITE "%-6ld" RED " %d burned out\n" RESET, elapsed, coder->id);
	safe_mutex_handle(&coder->sim->write_mutex, UNLOCK);
}
