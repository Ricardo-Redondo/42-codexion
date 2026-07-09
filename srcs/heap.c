/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsao-pay <rsao-pay@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 11:43:45 by rsao-pay          #+#    #+#             */
/*   Updated: 2026/07/09 14:10:59 by rsao-pay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void heap_init(t_heap *heap, int size, t_scheduler scheduler)
{
    heap->nodes = safe_malloc(sizeof(t_node) * 2);
	heap->size = size;
	heap->shceduler = scheduler;
}

void heap_free(t_heap *heap)
{
    free(&heap->nodes);
}

t_node heap_pop(t_heap)
{
    
}
t_node heap_peek()
{
    
}