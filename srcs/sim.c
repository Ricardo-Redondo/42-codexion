/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:42:18 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 23:10:44 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <codexion.h>

static void compile(t_coder *coder)
{
    safe_mutex_handle(&coder->l_dongle->dongle, LOCK);
    write_status(TAKE_DONGLE, coder);
    safe_mutex_handle(&coder->r_dongle->dongle, LOCK);
    write_status(TAKE_DONGLE, coder);
    set_long(&coder->mutex, &coder->last_compile, gettime(MILISEC));
    coder->compiles++;
    write_status(COMPILING, coder);
    precise_usleep(coder->args.time_to_compile, coder->sim);
    if (coder->compiles == coder->args.number_of_compiles_required)
        set_bool(&coder->mutex, &coder->done_compiling, true);
    safe_mutex_handle(&coder->l_dongle->dongle, UNLOCK);
    safe_mutex_handle(&coder->r_dongle->dongle, UNLOCK);
}

static void debug_refactor(t_coder *coder, t_status status)
{
    if (status == DEBUGGING)
    {
        write_status(DEBUGGING, coder);
        precise_usleep(coder->args.time_to_debug, coder->sim);
    }
    else if (status == REFACTORING)
    {
        write_status(REFACTORING, coder);
        precise_usleep(coder->args.time_to_refactor, coder->sim);
    }
}

void *single_coder(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    wait_all_threads(coder->sim);
    set_long(&coder->mutex, &coder->last_compile, gettime(MILISEC));
    increment_long(&coder->sim->sim_mutex, &coder->sim->num_threads_run);
    write_status(TAKE_DONGLE, coder);
    while (!sim_ended(coder->sim))
        usleep(200);
    return (NULL);
}

/*
 * @brief The starting point of every thread, the actual simulation
 * @param *data the coder which thread was created
*/
void *simulation(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;
    wait_all_threads(coder->sim);
    set_long(&coder->mutex, &coder->last_compile, gettime(MILISEC));
    increment_long(&coder->sim->sim_mutex, &coder->sim->num_threads_run);
    while (!sim_ended(coder->sim))
    {
        if (coder->done_compiling)
            break ;
        compile(coder);
        debug_refactor(coder, DEBUGGING);
        debug_refactor(coder, REFACTORING);
    }
    return (NULL);
}

/*
 * @brief Starts the simulation by creating all the threads,
 *        ensures every thread is created before starting the
 *        simulation
 * @param *sim pointer to the simulation struct
*/
void start_sim(t_sim *sim)
{
    int i;

    i = -1;
    if (sim->args.number_of_compiles_required == 0)
        return ;
    else if (sim->args.number_of_coders == 1)
        safe_thread_handle(&sim->coders[0].thread_id, single_coder,
            &sim->coders[0], CREATE);
    else
    {
        while(++i < sim->args.number_of_coders)
            safe_thread_handle(&sim->coders[i].thread_id, simulation,
                &sim->coders[i], CREATE);
    }
    safe_thread_handle(&sim->monitor, monitor_sim, sim, CREATE);
    sim->start_sim = gettime(MILISEC);
    set_bool(&sim->sim_mutex, &sim->all_threads_ready, true);

    i = -1;
    while(++i < sim->args.number_of_coders)
        safe_thread_handle(&sim->coders[i].thread_id, NULL, NULL, JOIN);
    set_bool(&sim->sim_mutex, &sim->ended_sim, true);
    safe_thread_handle(&sim->monitor, NULL, NULL, JOIN);
}
