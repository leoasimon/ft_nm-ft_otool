/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 08:14:24 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap)
{
	struct load_command		*lc;
	struct mach_header_64		*header;
	uint32_t				ncmds;

	header = (struct mach_header_64 *)ptr;
	if (swap)
		sw_mach_header_64(header);
	if (!CHECKED(header, end))
		return (NULL);
	lc = (struct load_command *)(header + 1);
	if (!CHECKED((struct load_command *)((void *)lc + header->sizeofcmds), end))
		return (NULL);
	if (swap)
		sw_load_command(lc);
	ncmds = header->ncmds;
	while (ncmds)
	{
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
		if (!CHECKED(lc ,end))
			return (NULL);
		if (swap)
			sw_load_command(lc);
		if (lc->cmd == LC_SYMTAB)
			return (struct symtab_command *)lc;
		ncmds--;
	}
	return (NULL);
}

// static struct section_64	*get_section(struct segment_command_64 *segc, uint32_t i, bool swap)
// {
// 	struct section_64	*section;
// 	uint32_t			nsects;

// 	if (i == NO_SECT)
// 		return (NULL);
// 	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
// 	if (i <= nsects)
// 	{
// 		section = (struct section_64 *)(segc + 1);
// 		i -= 1; // index starts at one
// 		return (section + i);
// 	}
// 	return get_section((struct segment_command_64 *)((void *)segc + segc->cmdsize), i - nsects, swap);
// }