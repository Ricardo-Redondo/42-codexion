/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 22:39:53 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/05/21 11:43:01 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int ft_schedulecmp(const char *s1, t_args *arg)
{
	if (strcmp(s1, "fifo") == 0)
		arg->scheduler = FIFO;
	else if (strcmp(s1, "edf") == 0)
		arg->scheduler = EDF;
	else
		return (fprintf(stderr, "Wrong argument: %s", s1), 0);
	return (1);
}

static int	ft_atoi_strict(char *str, t_args *arg)
{
	char *start;

	start = *str;
	if(*str == '-')
		return (0);	
	while(*str)
	{
		if(!(*str >= '0' && *str <= 9))
			return (fprintf(stderr, "Wrong argument: %s", str), 0);
		*str++;
	}
	arg = atoi(start);
	return (1);
}

int	parser(int argc, char **argv, t_args *args)
{
	t_scheduler scheduler;

	if (argc != 9)
		return (fprintf(2, "Wrong number of arguments \"%d\" should be 9",
			argc - 1), 0);
	if (!ft_atoi_strict(argv[1], args->number_of_coders) ||
		!ft_atoi_strict(argv[2], args->time_to_burnout) ||
		!ft_atoi_strict(argv[3], args->time_to_compile) ||
		!ft_atoi_strict(argv[4], args->time_to_debug) ||
		!ft_atoi_strict(argv[5], args->time_to_refactor) ||
		!ft_atoi_strict(argv[6], args->number_of_compiles_required) ||
		!ft_atoi_strict(argv[7], args->dongle_cooldown) ||
		!ft_schedulecmp(argv[8], args))
		return (0);
	return (1);
}
