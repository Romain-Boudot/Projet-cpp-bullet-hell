class Enemy {

    public:

        sf::CircleShape enemy_circle;

        Enemy(float x, float y);
        Enemy2(float x, float y);
        bool isdead();
        void kill();
        void fire();

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

Enemy::Enemy2(float x, float y) {

    sf::CircleShape enemy(30.f,200);
    enemy.setFillColor(sf::color::red);
    enemy.setPosition(x, y);

    this->enemy_circle = enemy;
    this->dead = false;
}

void Enemy::fire() {

    sf::vector2f pos(this->enemy_circle.getPosition());

    Bullet bullet(pos.x + 3.f, pos.y - 8.f, 0.f, -0.1);

    this->bullet_list.pushback(bullet);

}

