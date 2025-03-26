#include "../include/cub3d.h"

void init_player(t_player *player)
{
    player->x = WINDOW_WIDTH / 2;
    player->y = WINDOW_HEIGHT / 2;
    player->angle = PI / 2;
    

    player -> key_up = false;
    player -> key_down = false;
    player -> key_left = false;
    player -> key_right = false;
    player -> left_rot = false;
    player -> right_rot = false;
}

int key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == D)
        player->key_right = true;
    if (keycode == LEFT)
        player->left_rot = true;
    if (keycode == RIGHT)    
        player->right_rot = true;
    return (0);
}

int key_release(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = false;
    if (keycode == S)
        player->key_down = false;
    if (keycode == A)
        player->key_left = false;
    if (keycode == D)
        player->key_right = false;
    if (keycode == LEFT)
        player->left_rot = false;
    if (keycode == RIGHT)    
        player->right_rot = false;
    return (0);
}

void move_player(t_player *player)
{
    //int speed = 5; //mac
    float speed = 0.5; //dell
    float rot_speed = 0.1;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rot)
        player->angle -= rot_speed; 
    if (player->right_rot)
        player->angle += rot_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
    {
        player->x += cos_angle * speed;
        player->y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->x -= cos_angle * speed;
        player->y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->x += sin_angle * speed;
        player->y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        player->x -= sin_angle * speed;
        player->y += cos_angle * speed;
    }
}
