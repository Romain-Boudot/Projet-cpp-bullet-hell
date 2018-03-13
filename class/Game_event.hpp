class Game_event {

    public:

        int type;
        int keycode;

        Game_event(int type);

};

Game_event::Game_event(int type) {

    this->type = type;

}