class Bullet {

    public:

        sf::RectangleShape bullet_hit_box;
        int radiusHit;

        Bullet(float x, float y, float mx, float my);

        void move();

    private:

        sf::Vector2f mouvement;

};

Bullet::Bullet(float x, float y, float mx, float my) {

    sf::Vector2f size(4.f, 6.f);

    sf::RectangleShape r(size);
    r.setPosition(x, y);

    this->bullet_hit_box = r;
    this->mouvement.x = mx;
    this->mouvement.y = my;
    this->radiusHit = 4;

}

void Bullet::move() {

    this->bullet_hit_box.setPosition(this->bullet_hit_box.getPosition() + this->mouvement);

}