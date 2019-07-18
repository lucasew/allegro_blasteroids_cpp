#ifndef AB_SPACESHIP
#define AB_SPACESHIP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "./Point.cc"

class Spaceship {
    float heading;
    float heading_step = M_PI / 18; // 10 graus
    float speed;
    Point position = Point(0, 0);
    ALLEGRO_COLOR color;
    ALLEGRO_DISPLAY *disp;
    public:
    int health;
    Spaceship(ALLEGRO_DISPLAY *disp, Point begin, int health) {
        this->disp = disp;
        this->heading = 0;
        this->position = begin;
        this->health = health;
        this->speed = 10;
        this->color = al_map_rgb(255, 0, 255);
    }
    friend std::ostream& operator<<(std::ostream& out, const Spaceship& obj) {
        return out << "Spaceship(pos: " << obj.position <<
            " heading: " << obj.heading <<
            " health: " << obj.health <<
            " speed: " << obj.speed <<
            ")";
    }
    void fixPosition() {
        int w = al_get_display_width(disp);
        int h = al_get_display_height(disp);
        if (this->position.x > w)
            this->position.x = 0;
        if (this->position.x < 0)
            this->position.x = w;
        if (this->position.y > h)
            this->position.y = 0;
        if (this->position.y < 0)
            this->position.y = h;

    }

    void draw() {
        ALLEGRO_TRANSFORM tr;
        al_identity_transform(&tr);
        al_rotate_transform(&tr, this->heading);
        al_translate_transform(&tr, this->position.x, this->position.y);
        al_use_transform(&tr);
        al_draw_line(-8, 9, 0, -11, this->color, 1);
        al_draw_line(0, -11, 8, 9, this->color, 1);
        al_draw_line(-6, 4, -1, 4, this->color, 1);
        al_draw_line(6, 4, 1, 4, this->color, 1);
    }
    Point getPosition() {
        return this->position;
    }
    float getHeading() {
        return this->heading;
    }
    float getDangerRadius() {
        return 10;
    }
    void left() {
        heading -= heading_step;
    }
    void right() {
        heading += heading_step;
    }
    void ahead() {
        this->position.goAhead(speed, heading);
        fixPosition();
    }
    void reverse() {
        this->position.goAhead(-speed, heading);
        fixPosition();
    }
};

#endif
