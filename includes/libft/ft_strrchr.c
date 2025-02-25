/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:37:55 by szemmour          #+#    #+#             */
/*   Updated: 2024/10/31 15:54:08 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*last_c;

	last_c = NULL;
	i = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
			last_c = (char *)&s[i];
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (last_c);
}
