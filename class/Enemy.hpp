class Enemy {

    public:

        sf::CircleShape enemy_circle;
        //sf::CircleShape overcircle;

        std::vector<Bullet> bulletList;

        int weight;
        int radiusHit;

        Enemy(float x, float y, float mx, float my);
        void move();
        bool hit(int dmg);
        Bullet fire(float x, float y, float alpha);
        sf::Vector2f get_pos();
        int get_radius();
        void rotation(float alpha);

    private:

        int healthPTS;
        sf::Vector2f mouvement;
        sf::Vector2f rectifPosAngle;
        float inertie;

};

/*
 * constructeur
 * 
 * parametre :
 *   float position de l'ennemi en x
 *   float position de l'ennemi en y
 *   float mouvement de l'ennemi en x
 *   float mouvement de l'ennemi en y
 * 
 * créé une entité ennemi avec toute les infos neccessaire
 * 
 */

Enemy::Enemy(float x, float y, float mx, float my) {

    sf::CircleShape enemy(10.f,7);
    //sf::CircleShape overcircle(10.f,5);
    enemy.setFillColor(sf::Color::Red);
    //overcircle.setFillColor(sf::Color::Red);
    enemy.setPosition(x, y);
    //overcircle.setPosition(x, y);

    this->rectifPosAngle.x = 10;
    this->rectifPosAngle.y = 10;
    this->weight = 1;
    this->mouvement.x = mx;
    this->mouvement.y = my;
    this->enemy_circle = enemy;
    //this->overcircle = overcircle;
    this->radiusHit = 10;
    this->healthPTS = 30;
    this->inertie = ENEMY_MOVEMENT_DEC;

}


void Enemy::rotation(float offset) { // dead

    float init_angle = this->enemy_circle.getRotation();
    float alpha = init_angle + offset;

    std::cout << this->enemy_circle.getRotation() << " / ";

    this->enemy_circle.setRotation(alpha);

    std::cout << this->enemy_circle.getRotation() << std::endl;

    sf::Vector2f pos;

    pos.y = (sin(alpha) - sin(alpha)) * 14.1421356;
    pos.x = (cos(alpha) - cos(alpha)) * 14.1421356;

    std::cout << pos.x << " / " << pos.y << std::endl;

    this->enemy_circle.setPosition(this->enemy_circle.getPosition() + pos);

}


/*
 * fait bouger l'entité
 * 
 * parametre : void
 *
 * retourne void
 * 
 * fait bouger l'entité en fonction du muvement qu'elle possede
 * gestion de l'inertie de l'entité
 * 
 */

void Enemy::move() {

    this->mouvement.y *= this->inertie;

    if (this->mouvement.y < 0.0008) {
        this->inertie = ENEMY_MOVEMENT_INC;
    }

    this->enemy_circle.setPosition(this->enemy_circle.getPosition() + this->mouvement);
    //this->overcircle.setPosition(this->overcircle.getPosition() + this->mouvement);
    //this->overcircle.setRotation(this->overcircle.getRotation() - 0.01);

}

/*
 * inflige des degas a l'ennemi
 * 
 * parametre : int nombre de degas a enlever
 *
 * retourne bool
 * 
 * inflige des degas a l'ennemi en fonction des degas indiquer
 * retourne vrai si l'entiter est morte
 * faux si elle reste en vie
 * 
 */

bool Enemy::hit(int dmg) {

    this->healthPTS -= dmg;

    if (this->healthPTS <= 0) {
        return true;
    } else {
        return false;
    }

}

/*
 * fait tirer l'ennemi
 * 
 * parametre : Bullet_hell class de jeu
 *
 * retourne void
 * 
 * ajoute une balle dans la liste des tires
 * 
 */

Bullet Enemy::fire(float x, float y, float alpha) {

    Bullet bullet = Bullet(this->enemy_circle.getPosition().x, this->enemy_circle.getPosition().y, x, y);
    return bullet;

}

/*
 * retourne la postion de l'ennemi
 * 
 * parametre : void
 *
 * retourne sf::vector2f
 * 
 * retourne la position de l'ennemi en ajoutant un decallage pour centrer le points sur la sprite
 * 
 */

sf::Vector2f Enemy::get_pos() {

    return this->enemy_circle.getPosition() + sf::Vector2f(10.f, 10.f);

}

/*
 * retourne le rayon de l'ennemi
 * 
 * parametre : void
 *
 * retourne int rayon
 * 
 * retourne le rayon de l'ennemi
 * 
 */

int Enemy::get_radius() {

    return (int) this->enemy_circle.getRadius();

}