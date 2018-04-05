class Player {

    public:

        std::vector<Bullet> bullet_list;
        sf::CircleShape player_hit_box;
        int radiusHit;

        Player();

        void fire();
        sf::Vector2f get_pos();
        int get_radius();

};

/*
 * constructeur
 * 
 * parametre : void
 * 
 * créé une entiter joueur avec les information neccessair
 * 
 */

Player::Player() {

    sf::CircleShape player_hit_box(5.f,20);
    player_hit_box.setFillColor(sf::Color::Green);
    player_hit_box.setPosition(250.f, 400.f);

    this->player_hit_box = player_hit_box;
    this->radiusHit = 5;

}

/*
 * fait tirer le joueur
 * 
 * parametre : void
 *
 * retourne void
 * 
 * creer une balle avec la position du joueur comme position (plus leger décalage vers le haut [esthetique])
 * et un mouvement (vers le haut)
 * 
 */

void Player::fire() {

    sf::Vector2f pos(this->player_hit_box.getPosition());

    Bullet bullet(pos.x + 3.f, pos.y - 8.f, 0.f, -0.1);

    this->bullet_list.push_back(bullet);
    
}

/*
 * informe sur la position du joueur
 * 
 * parametre : void
 *
 * retourne sf::vector2f position du joueur
 * 
 * retourne la postion du joueur avec un correctif pour que la position sois au centre du sprite
 * 
 */

sf::Vector2f Player::get_pos() {

    return this->player_hit_box.getPosition() + sf::Vector2f(5.f, 5.f);

}

/*
 * informe sur le rayon du joueur
 * 
 * parametre : void
 *
 * retourne int rayon
 * 
 * retourne le rayon du joueur
 * 
 */

int Player::get_radius() {

    return (int) this->player_hit_box.getRadius();

}