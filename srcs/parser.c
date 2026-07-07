/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 22:39:53 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/07 15:17:06 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	ft_schedulecmp(const char *s1, t_args *arg)
{
	if (strcmp(s1, "fifo") == 0)
		arg->scheduler = FIFO;
	else if (strcmp(s1, "edf") == 0)
		arg->scheduler = EDF;
	else
		error_exit("Wrong argument: ", s1);
}

static inline int	is_digit(char i)
{
	return (i >= '0' && i <= '9');
}

static int	ft_atoi_strict(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		error_exit("Invalid number, cannot be negative", NULL);
	while (str[i])
	{
		if (!is_digit(str[i]))
			error_exit("Wrong argument: ", str);
		i++;
	}
	return (atoi(str));
}

/*
 * @brief parses all arguments and adds the values to the args struct
 * @param argc argument counter
 * @param argv argument vector
 * @param args pointer to the argument struct
 */
void	parser(int argc, char **argv, t_args *args)
{
	if (argc != 9)
		error_exit("Wrong number of arguments, should be 8", NULL);
	args->number_of_coders = ft_atoi_strict(argv[1]);
	if (args->number_of_coders == 0)
		error_exit("Invalid field, simulation cannot have 0 coders", NULL);
	args->time_to_burnout = ft_atoi_strict(argv[2]) * 1e3;
	args->time_to_compile = ft_atoi_strict(argv[3]) * 1e3;
	args->time_to_debug = ft_atoi_strict(argv[4]) * 1e3;
	args->time_to_refactor = ft_atoi_strict(argv[5]) * 1e3;
	args->number_of_compiles_required = ft_atoi_strict(argv[6]);
	if (args->number_of_compiles_required == 0)
		error_exit("Invalid field, simulation needs at least"
					" 1 compilation loop",
					NULL);
	args->dongle_cooldown = ft_atoi_strict(argv[7]);
	ft_schedulecmp(argv[8], args);
}
