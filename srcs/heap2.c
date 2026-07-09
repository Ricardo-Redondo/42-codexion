/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:10:22 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/09 14:11:24 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	node_beats(t_heap *heap, long a, long b)
{
	if (heap->nodes[a].key != heap->nodes[b].key)
		return (heap->nodes[a].key < heap->nodes[b].key);
	return (heap->nodes[a].coder->id < heap->nodes[b].coder->id);
}

static void	swap_nodes(t_node *a, t_node *b)
{
	t_node	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_push(t_heap *heap, t_coder *coder, long key)
{
	long	i;

	i = heap->size;
	heap->nodes[i].coder = coder;
	heap->nodes[i].key = key;
	heap->size++;
	while (i > 0 && node_beats(heap, i, (i - 1) / 2))
	{
		swap_nodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
