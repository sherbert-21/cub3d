#include "cub3d.h"

void	turn_left(t_game *win)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = win->plr->dirX;
    oldPlaneX = win->plr->planeX;
    win->plr->dirX = win->plr->dirX
                     * cos(-win->plr->rotation) - win->plr->dirY
                                                  * sin(-win->plr->rotation);
    win->plr->dirY = oldDirX * sin(-win->plr->rotation)
                     + win->plr->dirY * cos(-win->plr->rotation);
    win->plr->planeX = win->plr->planeX
                       * cos(-win->plr->rotation) - win->plr->planeY
                                                    * sin(-win->plr->rotation);
    win->plr->planeY = oldPlaneX
                       * sin(-win->plr->rotation) + win->plr->planeY
                                                    * cos(-win->plr->rotation);
}

void	turn_right(t_game *win)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = win->plr->dirX;
    oldPlaneX = win->plr->planeX;
    win->plr->dirX = win->plr->dirX
                     * cos(win->plr->rotation) - win->plr->dirY
                                                 * sin(win->plr->rotation);
    win->plr->dirY = oldDirX * sin(win->plr->rotation)
                     + win->plr->dirY * cos(win->plr->rotation);
    win->plr->planeX = win->plr->planeX
                       * cos(win->plr->rotation) - win->plr->planeY
                                                   * sin(win->plr->rotation);
    win->plr->planeY = oldPlaneX
                       * sin(win->plr->rotation) + win->plr->planeY
                                                   * cos(win->plr->rotation);
}

