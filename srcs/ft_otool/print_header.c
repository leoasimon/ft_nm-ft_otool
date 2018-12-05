/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 09:00:51 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/05 09:01:36 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static void	print_header_fat(char *fname, char *archname)
{
	ft_putstr(fname);
	ft_putstr(" (");
	ft_putstr("for architecture ");
	ft_putstr(archname);
	ft_putstr("):\n");
}

static void	print_header_simple(char *fname)
{
	ft_putstr(fname);
	ft_putstr(":\n");
}

static void print_header_lib(char *fname, char *oname)
{
	ft_putstr(fname);
	ft_putchar('(');
	ft_putstr(oname);
	ft_putstr("):\n");
}

void		print_header(enum ftype type, char *name, t_print_infos *curr)
{
	if (type == LIB)
		print_header_lib(name, curr->name);
	if (type == FAT && curr->cputype != CPU_TYPE_X86_64)
		print_header_fat(name, get_archname(curr->cputype, curr->cpusubtype));
	else
		print_header_simple(name);
}