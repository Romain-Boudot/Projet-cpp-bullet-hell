int eventPull(Bullet_hell *game) {

    if (game->events.size() > 0) {
        int event = game->events.front();
        game->events.erase(game->events.begin());
        return event;
    }

    return -1;

}


void move(Bullet_hell *game) {

    sf::Vector2f mouse_posf;

    mouse_posf.x = ((int) game->mouse_posi.x) - game->player.player_hit_box.getRadius();
    mouse_posf.y = ((int) game->mouse_posi.y) - game->player.player_hit_box.getRadius();

    game->player.player_hit_box.setPosition(mouse_posf);

}

void move_bullet(Bullet_hell *game) {

    for (int cpt = 0; cpt < game->player.bullet_list.size(); cpt++) {

        game->player.bullet_list[cpt].move();

        if (game->player.bullet_list[cpt].bullet_hit_box.getPosition().y < -10) {
            game->player.bullet_list.erase(game->player.bullet_list.begin() + cpt);
        }

    }

}