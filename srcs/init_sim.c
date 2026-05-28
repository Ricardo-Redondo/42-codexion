/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:29:51 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/05/21 13:13:45 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_list(t_sim *sim)
{
	t_node		*head;
	t_node		*tmp;
	t_coder		*c;
	t_dongle	*d;

	head = sim->head;
	while (head)
	{
		tmp = head;
		if (tmp->type == CODER)
		{
			c = (t_coder *)tmp;
			pthread_join(c->thread, NULL);
			pthread_mutex_destroy(&c->mutex);
			free(c);
		}
		else if (tmp->type == DONGLE)
		{
			d = (t_dongle *)tmp;
			pthread_mutex_destroy(&d->mutex);
			pthread_cond_destroy(&d->cond);
			free(d);
		}
		head = head->next;
	}
}

static t_node *add_values_to_node(t_node *node, t_sim *sim)
{
	t_coder *coder;
	t_dongle *dongle;

	switch (node->type)
	{
	case CODER:
		coder = (t_coder *)node;
		coder->time_to_burnout = sim->args.time_to_burnout;
		coder->get_time_to_burnout = &func1;
		coder->proccess = &func;
		coder->node.next = NULL;
		coder->node.prev = NULL;
		return (coder);
	case DONGLE:
		dongle = (t_dongle *)node;
		dongle->dongle_cooldown = sim->args.dongle_cooldown;
		pthread_mutex_init(&dongle->mutex, NULL);
		pthread_cond_init(&dongle->cond, NULL);
		dongle->node.next = NULL;
		dongle->node.prev = NULL;
		return (dongle);
	}
}

void	*create_node(t_node_type type, t_sim *sim)
{
	t_coder		*coder;
	t_dongle	*dongle;

	switch (type)
	{
	case CODER:
		coder = malloc(sizeof(t_coder));
		if (!coder)
			return (NULL);
		coder->node.type = CODER;
		coder = add_values_to_node(coder, sim);
		return (coder);
	case DONGLE:
		dongle = malloc(sizeof(t_dongle));
		if (!dongle)
			return (NULL);
		dongle->node.type = DONGLE;
		dongle = add_values_to_node(dongle, sim);
		return (dongle);
	}
}

void	add_node(t_node *node, t_sim *sim, int is_last)
{
	t_node	*pos;
	int		i;

	i = 0;
	if (!sim->head)
	{
		sim->head = node;
		return (NULL);
	}
	pos = sim->head;
	while (pos)
	{
		pos = pos->next;
		i++;
	}
	pos->next = node;
	node->prev = pos;
	if (is_last)
		node->next = sim->head;
}

int	init_sim(t_sim *sim)
{
	t_coder		*coder;
	t_dongle	*dongle;
	int			i;

	i = sim->args.number_of_coders;
	while (i > 0)
	{
		coder = (t_coder *)create_node(CODER, sim);
		dongle = (t_dongle *)create_node(DONGLE, sim);
		if (!coder || !dongle)
			return (free_list(sim), 0);
		if (pthread_create(coder->thread, NULL, coder_schedule, coder) != 0)
			return (free(sim), 0);
		add_node(coder, sim, 0);
		pthread_mutex_init(&dongle->mutex, NULL);
		pthread_cond_init(&dongle->cond, NULL);
		if (i - 1 == 0)
			add_node(dongle, sim, 1);
		else
			add_node(dongle, sim, 0);
		i--;
	}
}
