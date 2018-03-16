void tickcounter(sf::Clock *tick_clock, int *ticks) {

    while (tick_clock->getElapsedTime().asSeconds() <= 1.00005) { /* wait */ }

    *ticks += 1;

}


void eventPull(Bullet_hell *game, std::vector<Event> *events, int eventPullType) {

    for (int cpt = 0; cpt < game->events.size(); cpt++) {

        if (game->events[cpt].type == eventPullType) {

            events->push_back(game->events[cpt]);
            game->events.erase(game->events.begin() + cpt);

        }

    }

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