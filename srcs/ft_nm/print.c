/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/22 10:15:39 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

//This files contains functions to print the symbols previously store in a 
//binary tree of t_sym

//Todo: remove printf
static void	print_nm(t_sym	*sym)
{
	if (sym->value)
		printf("0000000%lx %c %s\n", sym->value, get_type_c(sym->sectname, sym->type), sym->name);
	else
		printf("                 %c %s\n", get_type_c(sym->sectname, sym->type), sym->name);

}

//The binary tree has been sorted previously, for no reasons this function has
//to handle the sorting
void 		print_tree(t_sym *curr)
{
	if (curr->right)
		print_tree(curr->right);
	print_nm(curr);
	if (curr->left)
		print_tree(curr->left);
}