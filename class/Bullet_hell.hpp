class Bullet_hell {

    public:
        
        int windowHeight; // hauteur de la fenetre de jeu
        int windowWidth; // largeur de la fenetre de jeu
        int framerate; // taux de rafraichissement du jeu

        Controler controler;
        Player player; // class Player
        std::vector<Enemy> enemy; // tableau de class Enemy
        std::vector<Event> events;

        sf::Mutex mtx_event;
        sf::Mutex mtx_controler;
        sf::Mutex mtx_vect_enemy;
        sf::Mutex mtx_vect_player_bullet;

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

Bullet_hell::Bullet_hell() {

    this->windowHeight = 800;
    this->windowWidth = 500;
    this->framerate = 90;
    this->endb = false;
    this->max_weight = 10;
    this->dmgHit = 1;

    Player player;

    this->player = player;

}


void Bullet_hell::addEvent(int type, int name) {

    Event event(type, name, 0);

    this->events.push_back(event);

}


void Bullet_hell::addEvent(int type, int name, int value) {

    Event event(type, name, value);

    this->events.push_back(event);

}


bool Bullet_hell::isEnded() {
    return this->endb;
}

void Bullet_hell::end() {
    this->endb = true;
}

int Bullet_hell::placesLeft() {
    return (this->max_weight - this->weight());
}


void Bullet_hell::addEnemy(float x, float y, float mx, float my) {

    Enemy enemy(x, y, mx, my);

    this->enemy.push_back(enemy);

}


int Bullet_hell::weight() {

    int weight = 0;

    for (int cpt = 0; cpt < this->enemy.size(); cpt++) {

        weight += this->enemy[cpt].weight;

    }

    return weight;

}

void Bullet_hell::killPlayerBullet(int indice) {

    this->mtx_vect_player_bullet.lock();
    this->player.bullet_list.erase(this->player.bullet_list.begin() + indice);
    this->mtx_vect_player_bullet.unlock();

}


void Bullet_hell::hitEnemy(int indice) {

    if (this->enemy[indice].hit(this->dmgHit)) {

        this->mtx_vect_enemy.lock();
        this->enemy.erase(this->enemy.begin() + indice);
        this->mtx_vect_enemy.unlock();

    }

}