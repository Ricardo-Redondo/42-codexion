/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 22:39:53 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/06/30 16:09:47 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void ft_schedulecmp(const char *s1, t_args *arg)
{
	if (strcmp(s1, "fifo") == 0)
		arg->scheduler = FIFO;
	else if (strcmp(s1, "edf") == 0)
		arg->scheduler = EDF;
	else
		error_exit("Wrong argument: ", s1);
}

static inline is_digit(char i)
{
	return (i >= '0' && i <= '9');
}

static int	ft_atoi_strict(const char *str)
{
	char *start;

	start = *str;
	if(*str == '-')
		return (0);	
	while(*str)
	{
		if(!is_digit(*str))
			error_exit("Wrong argument: ", str);
		*str++;
	}
	return(atoi(start));
}

/*
 * @brief parses all arguments and adds the values to the args struct
 * @param argc argument counter
 * @param argv argument vector
 * @param args pointer to the argument struct
*/ 
int	parser(int argc, char **argv, t_args *args)
{
	t_scheduler scheduler;

	if (argc != 9)
		error_exit("Wrong number of arguments, should be 8", NULL);
	args->number_of_coders = ft_atoi_strict(argv[1]);
	args->time_to_burnout = ft_atoi_strict(argv[2]) * 1e3;
	args->time_to_compile = ft_atoi_strict(argv[3]) * 1e3;
	args->time_to_debug = ft_atoi_strict(argv[4]) * 1e3;
	args->time_to_refactor = ft_atoi_strict(argv[5]) * 1e3;
	args->number_of_compiles_required = ft_atoi_strict(argv[6]);
	args->dongle_cooldown = ft_atoi_strict(argv[7]);
	ft_schedulecmp(argv[8], args);
}
