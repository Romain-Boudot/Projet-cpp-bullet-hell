class Enemy {

    public:

        sf::CircleShape enemy_circle;

        int weight;
        int radiusHit;

        Enemy(float x, float y, float mx, float my);
        void move();
        bool hit(int dmg);

    private:

        int healthPTS;
        sf::Vector2f mouvement;

};

Enemy::Enemy(float x, float y, float mx, float my) {

    sf::CircleShape enemy(10.f,20);
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(x, y);

    this->weight = 1;
    this->mouvement.x = mx;
    this->mouvement.y = my;
    this->enemy_circle = enemy;
    this->radiusHit = 10;
    this->healthPTS = 50;

}

void Enemy::move() {

    this->enemy_circle.setPosition(this->enemy_circle.getPosition() + this->mouvement);

}

bool Enemy::hit(int dmg) {

    this->healthPTS -= dmg;

    if (this->healthPTS <= 0) {
        return true;
    } else {
        return false;
    }

}