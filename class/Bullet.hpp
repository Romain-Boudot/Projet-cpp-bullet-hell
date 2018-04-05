class Bullet {

    public:

        sf::RectangleShape bullet_hit_box;

        Bullet(float x, float y, float mx, float my);
        Bullet(float x, float y, float mx, float my, float alpha);

        void move();
        bool out();
        sf::Vector2f get_pos();
        int get_radius();

    private:

        sf::Vector2f mouvement;

};

/*
 * constructeur
 * parametre :
 *   float position en x
 *   float position en y
 *   float increment de mouvement x
 *   float increment de mouvement y
 * 
 * detailles
 * 
 * overloaded
 */

Bullet::Bullet(float x, float y, float mx, float my) {

    sf::Vector2f size(4.f, 6.f);

    sf::RectangleShape r(size);
    r.setPosition(x, y);

    this->bullet_hit_box = r;
    this->mouvement.x = mx;
    this->mouvement.y = my;

}

/*
 * constructeur
 * parametre :
 *   float position en x
 *   float position en y
 *   float increment de mouvement x
 *   float increment de mouvement y
 * 
 * detailles
 * 
 * overloaded
 */

Bullet::Bullet(float x, float y, float mx, float my, float alpha) {

    sf::Vector2f size(4.f, 6.f);

    sf::RectangleShape r(size);
    r.setPosition(x, y);
    r.setRotation(alpha);

    this->bullet_hit_box = r;
    this->mouvement.x = mx;
    this->mouvement.y = my;

}

/*
 * fait bouger l'entitée
 * parametre : void
 * 
 * retourne void
 * 
 * fait bouger l'entitée en fonction du mouvement (this->mouvement) donné à la creation du l'objet
 * 
 */

void Bullet::move() {

    this->bullet_hit_box.setPosition(this->bullet_hit_box.getPosition() + this->mouvement);

}

/*
 * retourne vrai ou faux (si l'entitée est hors fentre)
 * parametre : void
 * 
 * retourne bool
 * 
 * check la position de l'entitée et retourne vrai si l'entité est hors fenetre
 * faux si l'entité est dans la fenetre
 * 
 */

bool Bullet::out() {

    if (this->bullet_hit_box.getPosition().y < -5 ||
    this->bullet_hit_box.getPosition().y > 795 ||
    this->bullet_hit_box.getPosition().x < -5 ||
    this->bullet_hit_box.getPosition().x > 495) {
        return true;
    } else {
        return false;
    }

}

/*
 * retourne la position d'une balle
 * parametre : void
 * 
 * retourne sf::vector2f pos
 * 
 * vecteur 2 dimmensions (x, y)
 * la postion est ajuster +(2, 3) car la position renvoyer n'est pas le centre du sprite
 * 
 */

sf::Vector2f Bullet::get_pos() {

    return this->bullet_hit_box.getPosition() + sf::Vector2f(2.f, 3.f);

}

/*
 * retourne le rayon (hit box) d'une balle
 * parametre : void
 * 
 * retourne int radius
 * 
 */

int Bullet::get_radius() {

    return 2;

}