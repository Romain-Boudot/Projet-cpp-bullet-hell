class Bullet_hell {

    public:

        Controler controler;
        Player player; // class Player
        std::vector<Enemy> enemy; // tableau de class Enemy
        std::vector<Event> events;
        std::vector<Bullet> enemy_bullet_list;

        sf::Mutex mtx_event;
        sf::Mutex mtx_controler;
        sf::Mutex mtx_vect_enemy;
        sf::Mutex mtx_vect_enemy_bullet;
        sf::Mutex mtx_vect_player_bullet;

        sf::Vector2f corectif_hit_box_enemy;
        sf::Vector2f corectif_hit_box_bullet_player;
        sf::Vector2f corectif_hit_box_player;

        Bullet_hell();

        bool isEnded();
        void end();
        void addEvent(int type, int code);
        void addEvent(int type, int code, int value);
        int  placesLeft();
        void addEnemy(float x, float y, float mx, float my);
        int  weight();
        void killPlayerBullet(int indice);
        void hitEnemy(int indice);

    private:

        bool endb;
        int max_weight;
        int dmgHit;

};

/*
 * constructeur
 * parametre : void
 * 
 * creer la classe de jeu
 * 
 */

Bullet_hell::Bullet_hell() {

    this->endb = false;
    this->max_weight = 10;
    this->dmgHit = 1;

    Player player;

    this->player = player;

}

/*
 * ajoute un event au tableau d'evenement
 * parametre :
 *   int type de l'evenement
 *   int nom de l'evenement (un chiffre...)
 * 
 * retourne void
 * 
 * ajoute un evenement au tableau des evenement (communication entre thread)
 * 
 * overloaded
 */

void Bullet_hell::addEvent(int type, int name) {

    Event event(type, name, 0);

    this->events.push_back(event);

}

/*
 * parametre :
 *   int type de l'evenement
 *   int nom de l'evenement (un chiffre...)
 *   int valeur de l'evenement  
 * 
 * overloaded
 */

void Bullet_hell::addEvent(int type, int name, int value) {

    Event event(type, name, value);

    this->events.push_back(event);

}

/*
 * renseigne sur la fin du jeu
 * 
 * parametre : void
 *
 * retourne bool
 * 
 * retourne vrai si le jeu est fini (mort du joueur)
 * et faux si le jeu n'est pas fini
 * 
 */

bool Bullet_hell::isEnded() {
    return this->endb;
}

/*
 * termine le jeu
 * 
 * parametre : void
 *
 * retourne void
 * 
 * fini le jeu
 * 
 */

void Bullet_hell::end() {
    this->endb = true;
}

/*
 * informe sur le nombre de place restante sur le plateau
 * 
 * parametre : void
 *
 * retourne : int nombre de places
 * 
 * retourne le nombre de place en fonction de la place deja occuper par les ennemis et la place total disponible
 * 
 */

int Bullet_hell::placesLeft() {
    return (this->max_weight - this->weight());
}

/*
 * créé un ennemi et l'ajoute à la liste des ennemis
 * 
 * parametre :
 *   float position de l'ennemi en x
 *   float position de l'ennemi en y
 *   float mouvement de l'ennemi en x
 *   float mouvement de l'ennemi en y
 *
 * retourne void
 * 
 * créé une entiter ennemi et l'ajoute a la lite des ennemis
 * 
 */

void Bullet_hell::addEnemy(float x, float y, float mx, float my) {

    Enemy enemy(x, y, mx, my);

    this->enemy.push_back(enemy);

}

/*
 * informe sur le poids qu'occupe les ennemis sur le plateau
 * 
 * parametre : void
 *
 * retourne int
 * 
 * retourne le poids occuper par les ennemis sur le plateau
 * 
 */

int Bullet_hell::weight() {

    int weight = 0;

    for (int cpt = 0; cpt < this->enemy.size(); cpt++) {

        weight += this->enemy[cpt].weight;

    }

    return weight;

}

/*
 * detruit une balle du joueur
 * 
 * parametre : int emplacement de la balle dans le tableau des balles du player
 *
 * retourne void
 * 
 * detruit une balle du joueur (player)
 * 
 */

void Bullet_hell::killPlayerBullet(int indice) {

    this->mtx_vect_player_bullet.lock();
    this->player.bullet_list.erase(this->player.bullet_list.begin() + indice);
    this->mtx_vect_player_bullet.unlock();

}

/*
 * enleve des points de vie a un ennemi
 * 
 * parametre : int emplacement de la balle dans le tableau des balles du player
 *
 * retourne void
 * 
 * enleve autant de points de vie a l'ennemi indiquer que de degas que possede le joueur
 * 
 */

void Bullet_hell::hitEnemy(int indice) {

    if (this->enemy[indice].hit(this->dmgHit)) {

        this->mtx_vect_enemy.lock();
        this->enemy.erase(this->enemy.begin() + indice);
        this->mtx_vect_enemy.unlock();

    }

}