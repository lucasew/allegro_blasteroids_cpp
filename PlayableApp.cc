#include "./App.cc"

class PlayableApp: public App {
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    int heartBeat = 0;
    int fps;
    public:
    PlayableApp(int fps) : App() {
        assert(al_install_keyboard());
        this->fps = fps;
        this->queue = al_create_event_queue();
        this->timer = al_create_timer(1. / fps);
        al_start_timer(this->timer);
        al_register_event_source(this->queue, al_get_display_event_source(this->disp));
        al_register_event_source(this->queue, al_get_timer_event_source(this->timer));
        al_register_event_source(this->queue, al_get_keyboard_event_source());
    }
    void handleKey(ALLEGRO_KEYBOARD_EVENT key) {
        switch(key.keycode) {
            case ALLEGRO_KEY_LEFT:
                this->ship.left();
                break;
            case ALLEGRO_KEY_RIGHT:
                this->ship.right();
                break;
            case ALLEGRO_KEY_UP:
                this->ship.ahead();
                break;
            case ALLEGRO_KEY_SPACE:
                shotBullet();
                break;
            case ALLEGRO_KEY_DOWN:
                this->ship.reverse();
                break;
            case ALLEGRO_KEY_ESCAPE:
                closeASAP = true;
                break;
        }

    }
    ~PlayableApp() {
        al_destroy_timer(this->timer);
        al_destroy_event_queue(this->queue);
    }
    void tick() {
        ALLEGRO_EVENT ev;
        al_wait_for_event(this->queue, &ev);
        switch (ev.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                closeASAP = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                handleKey(ev.keyboard);
                break;
            case ALLEGRO_EVENT_TIMER:
                if (handleApp()) {
                    spawnAsteroid();
                }
                heartBeat++;
                if (!(heartBeat % (fps*10))) // 10 segundos
                    spawnAsteroid();
                break;
        }
    }
};
