class Event {

    public:

        int type;
        int name;
        int value;

        Event(int type, int name, int value);

};

Event::Event(int type, int name, int value) {

    this->type = type;
    this->name = name;
    this->value = value;

}