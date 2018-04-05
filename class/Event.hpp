class Event {

    public:

        int type;
        int name;
        int value;

        Event(int type, int name, int value);

};

/*
 * constructeur
 * 
 * parametre :
 *   int type de l'evenement
 *   int nom de l'evenement
 *   int valeur de l'evenemtn
 * 
 * detailles
 * 
 */

Event::Event(int type, int name, int value) {

    this->type = type;
    this->name = name;
    this->value = value;

}