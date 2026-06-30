/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:38:41 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 22:06:03 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
 * ./codexion 5 800 200 200 200 5 0 fifo
*/
int main(int argc, char **argv)
{
    t_sim sim;

    parser(argc, argv, &sim.args);
    init_sim(&sim);
    start_sim(&sim);
    // clean_sim(&sim);
}
