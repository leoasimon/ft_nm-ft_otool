/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_32.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/04 11:41:22 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static struct section	*get_text_section(struct segment_command *segc, bool swap, void *end)
{
	struct section	*section;
	uint32_t			nsects;
	uint32_t			cmdsize;
	unsigned int		i;

	cmdsize = swap ? swap_int32(segc->cmdsize) : segc->cmdsize;
	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
	if (!ft_strcmp(segc->segname, SEG_TEXT))
	{
		section = (struct section *)(segc + 1);
		if (!CHECKED(section + nsects, end))
			return (NULL);
		i = 0;
		while (i < nsects)
		{
			if (!ft_strcmp(section[i].sectname, SECT_TEXT))
				return (section + i);
			i++;
		}
		return (NULL);
	}
	//todo: stop at some point 
	return get_text_section((struct segment_command *)((void *)segc + cmdsize), swap, end);
}

static t_hex_dump			*init_hex_dump(struct section *sec, void *ptr, void *end)
{
	char		*datas;
	t_hex_dump	*hd;
	datas = (char *)(ptr + sec->offset);
	if (!CHECKED(datas + sec->size, end))
		return (NULL);
	if (!(hd = (t_hex_dump *)malloc(sizeof(t_hex_dump))))
		return (NULL);
	hd->datas = datas;
	hd->sec32 = sec;
	return (hd);
}

t_hex_dump					*get_hex_dump_32(void *ptr, void *end, bool swap)
{
	struct segment_command	*segc;
	struct section			*sec;

	segc = (struct segment_command *)((struct mach_header *)ptr + 1);
	if (!(sec = get_text_section(segc, swap, end)))
		return (NULL);
	if (swap)
		sw_section_32(sec);
	return (init_hex_dump(sec, ptr, end));
}