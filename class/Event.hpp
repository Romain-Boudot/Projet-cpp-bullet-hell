class Event {

    public:

        int type;
        int code;

        Event(int type, int code);

};

Event::Event(int type, int code) {

    this->code = code;
    this->type = type;

}