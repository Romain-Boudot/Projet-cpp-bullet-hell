void tickcounter(sf::Clock *tick_clock, int *ticks) {

    while (tick_clock->getElapsedTime().asSeconds() <= 0.00005) { /* wait */ }

    *ticks += 1;

    tick_clock->restart();

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

    if (game->controler.joy == false) {

        sf::Vector2f mouse_posf;

        mouse_posf.x = ((int) game->controler.mouse_posi.x) - game->player.player_hit_box.getRadius();
        mouse_posf.y = ((int) game->controler.mouse_posi.y) - game->player.player_hit_box.getRadius();

        game->player.player_hit_box.setPosition(mouse_posf);

    } else {

        sf::Vector2f move(
            game->controler.axisX / 4000,
            game->controler.axisY / 4000
        );

        game->player.player_hit_box.setPosition(game->player.player_hit_box.getPosition() + move);

    }

}


void move_bullet(Bullet_hell *game) {

    for (int cpt = 0; cpt < game->player.bullet_list.size(); cpt++) {

        game->player.bullet_list[cpt].move();

        if (game->player.bullet_list[cpt].bullet_hit_box.getPosition().y < -10) {
            game->player.bullet_list.erase(game->player.bullet_list.begin() + cpt);
        }

    }

}

bool collision(sf::Vector2f pos1, int rad1, sf::Vector2f pos2, int rad2) {

    if (sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y)) <= rad1 + rad2) {
        return true;
    } else {
        return false;
    }

}