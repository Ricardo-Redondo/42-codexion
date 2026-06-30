/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 14:20:38 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 22:18:56 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

/*
 *
 *
 * 
*/
long gettime(t_time_code time_code)
{
    struct timeval tv;
    
    if (gettimeofday(&tv, NULL))
        error_exit("Failed getting time of day.", NULL);
    if (time_code == SEC)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (time_code == MILISEC)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (time_code == MICROSEC)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Invalid input to gettime.", NULL);
    return (42);
}

/*
 * @brief sleeps thread for <usec> ms, uses usleep to relieve cpu,
 *        when the thread is 1ms away from waking up it spinlocks
 *        to prevent imprecise time calculation
 * @param usec number of ms to sleep
 * @param *sim pointer to the simulation struct
*/
void precise_usleep(long usec, t_sim *sim)
{
    long start;
    long elapsed;
    long rem;

    start = gettime(MICROSEC);
    while (gettime(MICROSEC) - start < usec)
    {
        if (sim_ended(sim))
            break ;
        elapsed = gettime(MICROSEC) - start;
        rem = usec - elapsed;
        if (rem > 1e3)
            usleep(usec / 2);
        else
        {
            while (gettime(MICROSEC) - start < usec)
                ;
        }
    }
}

void error_exit(const char *error, const char *arg)
{
    fprintf(stderr, RED"%s\n"RESET, error);
    if (arg)
        fprintf(stderr, RED"%s\n"RESET, arg);
    exit(EXIT_FAILURE);   
}
