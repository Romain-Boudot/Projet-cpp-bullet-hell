class Player {

    public:

        std::vector<Bullet> bullet_list;
        sf::CircleShape player_hit_box;
        int radiusHit;

        Player();

        void fire();

};

Player::Player() {

    sf::CircleShape player_hit_box(5.f,20);
    player_hit_box.setFillColor(sf::Color::Green);

    this->player_hit_box = player_hit_box;
    this->radiusHit = 5;

}

void Player::fire() {

    sf::Vector2f pos(this->player_hit_box.getPosition());

    Bullet bullet(pos.x + 3.f, pos.y - 8.f, 0.f, -0.1);

    this->bullet_list.push_back(bullet);
    
}