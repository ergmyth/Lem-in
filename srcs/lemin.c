/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:23:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/04 12:23:02 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <fcntl.h>

void		print_all(t_lemin *lem)
{
	print_rooms(&lem->rooms);
	print_links(&lem->links);
	print_neighbors(lem->adjm, NULL);
	print_paths(lem->paths);
}

void		init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
	ft_array_init(&lem->strarr, 128);
}

void		print_error(t_lemin *lem, t_result err)
{
	if (!lem->is_debug)
		ft_putendl_fd("ERROR", 2);
	else
	{
		ft_putstr_fd("ERROR ", 2);
		ft_putnbr_fd(err, 2);
		ft_putendl_fd("", 2);
	}
}

static int	parse_option(char *arg, t_lemin *lem)
{
	t_uint	flags;

	flags = 0;
	if (*arg == '-' && *(arg + 1) != '\0')
	{
		while (*++arg)
		{
			if (*arg == 'd')
				flags |= 1u;
			else if (*arg == 'c')
				flags |= 2u;
			else
				return (0);
		}
		if (flags & 1u)
			lem->is_debug = 1;
		if (flags & 2u)
			lem->is_colorize = 1;
		return (1);
	}
	return (0);
}

int			main(int ac, char *av[])
{
	t_lemin		lem;
	t_result	ret;
	int			fd;

	init_lem(&lem);
	while (ac-- > 1)
		if (parse_option(av[ac], &lem) == 0)
			if (lem.fd == 0)
				if ((fd = open(av[ac], O_RDONLY)) != -1)
					lem.fd = fd;
	ret = read_input(lem.fd, &lem);
	if (ret == RET_OK)
		ret = check_all(&lem);
	if (ret == RET_OK)
		ret = find_all_paths(&lem);
	if (ret == RET_OK)
		print_given_data(&lem);
	else
		print_error(&lem, ret);
	if (lem.is_debug)
		print_all(&lem);
	delete_all(&lem);
	return (0);
}
