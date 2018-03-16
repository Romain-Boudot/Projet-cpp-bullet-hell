class Bullet_hell {

    public:
        
        int windowHeight; // hauteur de la fenetre de jeu
        int windowWidth; // largeur de la fenetre de jeu
        int framerate; // taux de rafraichissement du jeu
        Player player; // class Player
        std::vector<Enemy> enemy; // tableau de class Enemy
        sf::Vector2i mouse_posi;
        std::vector<Event> events;

        sf::Mutex mtx_event;
        sf::Mutex mtx_pos_player;


        Bullet_hell();

        bool isEnded();
        void end();
        void pause();
        void resume();
        bool isPaused();
        void addEvent(int type, int code);

    private:

        bool endb;
        bool pauseb;

};

Bullet_hell::Bullet_hell() {

    this->windowHeight = 800;
    this->windowWidth = 500;
    this->framerate = 90;
    this->endb = false;

    Player player;

    this->player = player;

    Enemy enemy1(250.f, 60.f);
    Enemy enemy2(250.f, 90.f);
    Enemy enemy3(220.f, 60.f);
    Enemy enemy4(280.f, 60.f);
    Enemy2 enemy5(250.f, 40.f);

    this->enemy.push_back(enemy1);
    this->enemy.push_back(enemy2);
    this->enemy.push_back(enemy3);
    this->enemy.push_back(enemy4);
    this->enemy.push_back(enemy5);

}


void Bullet_hell::addEvent(int type, int code) {

    Event event(type, code);

    this->events.push_back(event);

}


bool Bullet_hell::isEnded() {
    return this->endb;
}

void Bullet_hell::end() {
    this->endb = true;
}

void Bullet_hell::pause() {
    this->pauseb = true;
}

void Bullet_hell::resume() {
    this->pauseb = false;
}

bool Bullet_hell::isPaused() {
    return this->pauseb;
}