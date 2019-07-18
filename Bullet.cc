#ifndef AB_BULLET
#define AB_BULLET

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "./UpdateableObject.cc"
#include "SingleLinkedList.cc"

class Bullet : public UpdateableObject {
    public:
        int power;
        friend std::ostream& operator<<(std::ostream& out, const Bullet& obj) {
            return out << "Bullet(pos: " << obj.position <<
                " heading: " << obj.heading <<
                " speed: " << obj.speed <<
                " power: " << obj.power <<
                ")";
        }
        Bullet(ALLEGRO_DISPLAY *disp) : UpdateableObject(disp) {
            this->power = rand()%100;
        }
        Bullet(ALLEGRO_DISPLAY *disp, Point position, float heading) : Bullet(disp) {
            this->position = position;
            this->heading = heading;
        }

        void draw() {
            ALLEGRO_TRANSFORM tr;
            al_identity_transform(&tr);
            al_rotate_transform(&tr, this->heading);
            al_translate_transform(&tr, this->position.x, this->position.y);
            al_use_transform(&tr);
            al_draw_line(1, 0, 0, 1, this->color, 2.0f);
            al_draw_line(0, 1, -1, 0, this->color, 2.0f);
            al_draw_line(-1, 0, 0, -1, this->color, 2.0f);
            al_draw_line(0, -1, 1, 0, this->color, 2.0f);
        }
        float getDangerRadius() {
            return 1;
        }
};

bool isValid(Bullet b) {
    return b.power > 0;
}

#endif
