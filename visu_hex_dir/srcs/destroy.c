/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:43:03 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/20 11:43:04 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis_lemin.h"

static void		sdl_destroy(t_vis *vis)
{
	SDL_RemoveTimer(vis->anim_tim);
	vis->anim_tim = 0;
	SDL_RemoveTimer(vis->moves_tim);
	vis->moves_tim = 0;
	SDL_DestroyWindow(vis->window);
	vis->window = NULL;
	SDL_DestroyRenderer(vis->ren);
	vis->ren = NULL;
	SDL_DestroyTexture(vis->antsimg.texture);
	vis->antsimg.texture = NULL;
	SDL_DestroyTexture(vis->buttonsimg.texture);
	vis->buttonsimg.texture = NULL;
	SDL_DestroyTexture(vis->font_text);
	vis->font_text = NULL;
	TTF_CloseFont(vis->font);
	vis->font = NULL;
	TTF_CloseFont(vis->info_font);
	vis->info_font = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

static void		lem_destroy(t_lemin *lem)
{
	ft_array_remove_all(&lem->rooms, free);
	ft_array_remove_all(&lem->links, free);
}

int				vis_destroy(t_vis *vis, int is_err)
{
	if (is_err)
		ft_putendl_fd("Error", 2);
	sdl_destroy(vis);
	ft_memdel((void **)&vis->lemarr);
	ft_array_remove_all(&vis->curlems, NULL);
	lem_destroy(&vis->lem);
	return (1);
}
