/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:49:25 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/05/21 12:45:32 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void *get_sim_value(void *value, int is_args)
{
    static t_args *args;
    void *res;

    if (is_args)
    {
        args = (t_args *)value;
        return ;
    }
    if (strcmp(value, "time_to_compile") == 0)
        res = (int)args->time_to_compile;
    else if (strcmp(value, "time_to_debug") == 0)
        res = (int)args->time_to_debug;
    else if (strcmp(value, "time_to_refactor") == 0)
        res = (int)args->time_to_refactor;
    else if (strcmp(value, "number_of_compiles_required") == 0)
        res = (int)args->number_of_compiles_required;
    else if (strcmp(value, "scheduler") == 0)
        res = (t_scheduler)args->scheduler;
}

void *(*coder_schedule(void *arg))(t_coder *coder)
{
    t_coder *coder;
    t_args wa;

    coder = (t_coder *)arg;
    wa.number_of_coders
    
}
