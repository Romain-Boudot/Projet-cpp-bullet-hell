class Enemy {

    public:

        sf::CircleShape enemy_circle;

        Enemy(float x, float y);
        bool isdead();
        void kill();

    private:

        bool dead;

};

bool Enemy::isdead() {

    return this->dead;

}

void Enemy::kill() {

    this->dead = true;

}

Enemy::Enemy(float x, float y) {

    sf::CircleShape enemy(10.f,100);
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(x, y);

    this->enemy_circle = enemy;
    this->dead = false;

}