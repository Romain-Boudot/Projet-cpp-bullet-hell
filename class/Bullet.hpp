class Bullet {

    public:

        sf::RectangleShape bullet_hit_box;

        Bullet(float x, float y, float mx, float my);

        bool isDead();
        void move();

    private:

        bool dead;
        sf::Vector2f mouvement;

};

Bullet::Bullet(float x, float y, float mx, float my) {

    sf::Vector2f size(3.f, 6.f);

    sf::RectangleShape r(size);
    r.setPosition(x, y);

    this->bullet_hit_box = r;
    this->mouvement.x = mx;
    this->mouvement.y = my;
    this->dead = false;

}

bool Bullet::isDead() {

    return this->dead;
    
}

void Bullet::move() {

    this->bullet_hit_box.setPosition(this->bullet_hit_box.getPosition() + this->mouvement);

}