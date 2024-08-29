/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afocant <afocant@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:53:20 by afocant           #+#    #+#             */
/*   Updated: 2024/04/17 20:53:21 by afocant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node_ptr;

	node_ptr = malloc(sizeof(t_list));
	if (!node_ptr)
		return (NULL);
	node_ptr->content = content;
	node_ptr->next = NULL;
	return (node_ptr);
}
