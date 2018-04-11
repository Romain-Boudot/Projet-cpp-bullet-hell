class Controler {

    public:

        bool joy;
        sf::Vector2i keyDir;
        sf::Vector2f correctif;
        sf::Vector2f deadzone;
        bool shiftKey;
        float axisX; // vertical move
        float axisY; // horizontal move
        float axisZ;
        float axisR; // fire
        float axisU;
        float axisV;
        float axisPOVX;
        float axisPOVY;

        Controler();

};

/*
 * constructeur
 * 
 * parametre : void
 * 
 * créé les variable de controlleur du jeu
 * 
 */

Controler::Controler() {

    this->joy = false;
    this->keyDir.x = 0;
    this->keyDir.y = 0;    
    this->correctif.x = 0;
    this->correctif.y = 0;
    this->shiftKey = false;
    this->axisX = 0; // vertical move
    this->axisY = 0; // horizontal move
    this->axisZ = 0;
    this->axisR = 0; // fire
    this->axisU = 0;
    this->axisV = 0;
    this->axisPOVX = 0;
    this->axisPOVY = 0;
    this->deadzone.x = 10;
    this->deadzone.y = 10;
    
}