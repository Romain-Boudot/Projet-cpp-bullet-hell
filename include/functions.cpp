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

        sf::Vector2f pos = game->player.player_hit_box.getPosition();
        
        if (game->controler.shiftKey) {
            pos.x += (float) game->controler.keyDir.x / 180;
            pos.y += (float) game->controler.keyDir.y / 180;
        } else {
            pos.x += (float) game->controler.keyDir.x / 80;
            pos.y += (float) game->controler.keyDir.y / 80;
        }

        if (pos.x > 490 || pos.x < 0 || pos.y > 790 || pos.y < 0) {
            // sort de l'ecran
        } else {
            game->player.player_hit_box.setPosition(pos);
        }

    } else {

        sf::Vector2f move(
            (game->controler.axisX + game->controler.correctif.x),
            (game->controler.axisY + game->controler.correctif.y)
        );

        if (move.x < 0) {
            move.x += game->controler.deadzone.x;
            if (move.x > 0) move.x = 0;
        } else {
            move.x -= game->controler.deadzone.x;
            if (move.x < 0) move.x = 0;
        }

        if (move.y < 0) {
            move.y += game->controler.deadzone.y;
            if (move.y > 0) move.y = 0;
        } else {
            move.y -= game->controler.deadzone.y;
            if (move.y < 0) move.y = 0;
        }

        move.x /= 4000;
        move.y /= 4000;

        sf::Vector2f pos(game->player.player_hit_box.getPosition() + move);

        if (pos.x > 490 || pos.x < 0 || pos.y > 790 || pos.y < 0) {
            // sort de l'ecran
        } else {
            game->player.player_hit_box.setPosition(pos);
        }

    }

}


void move_bullet(Bullet_hell *game) {

    for (int cpt = 0; cpt < game->player.bullet_list.size(); cpt++) {

        game->player.bullet_list[cpt].move();

        if (game->player.bullet_list[cpt].out()) {
            game->player.bullet_list.erase(game->player.bullet_list.begin() + cpt);
        }

    }

    for (int cpt = 0; cpt < game->enemy_bullet_list.size(); cpt++) {

        game->enemy_bullet_list[cpt].move();

        if (game->enemy_bullet_list[cpt].out()) {
            game->enemy_bullet_list.erase(game->enemy_bullet_list.begin() + cpt);
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

std::string tostring(int score) {

    std::stringstream ss;

    ss << score;

    std::string sService = ss.str();

    return sService;

}

std::string tostring(Bullet_hell *game) {

    std::stringstream ss;

    ss << game->controler.axisX << " / " << game->controler.axisY;

    std::string sService = ss.str();

    return sService;

}