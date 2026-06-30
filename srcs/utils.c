/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 14:20:38 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 14:44:54 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void error_exit(const char *error, const char *arg)
{
    fprintf(STDERR_FILENO, RED"%s\n"RESET, error);
    if (arg)
        fprintf(STDERR_FILENO, RED"%s\n"RESET, arg);
    exit(EXIT_FAILURE);   
}
