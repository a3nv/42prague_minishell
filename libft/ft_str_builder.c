/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:41:52 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/26 23:51:38 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_str_builder(char *res, size_t res_size, ...)
{
	va_list		ap;
	const char	*current;
	size_t		rem_space;
	size_t		offset;
	size_t		coppied;

	va_start(ap, res_size);
	current = va_arg(ap, const char *);
	rem_space = res_size;
	offset = 0;
	while (current != NULL)
	{
		coppied = ft_strlcpy(res + offset, current, rem_space);
		if (coppied >= rem_space)
			break ;
		offset += coppied;
		rem_space -= coppied;
		current = va_arg(ap, const char *);
	}
	va_end(ap);
}
