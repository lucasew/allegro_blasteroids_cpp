#ifndef AB_ASTEROID
#define AB_ASTEROID

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "./SingleLinkedList.cc"
#include "./UpdateableObject.cc"

const int asteroid_points[][2] = {
            {-20, 20},
            {-25, 5},
            {-25, -10},
            {-5, -10},
            {-10, -20},
            {5, -20},
            {20, -10},
            {20, -5},
            {0, 0},
            {20, 10},
            {10, 20},
            {0, 15}
        };

class Asteroid : public UpdateableObject {
    protected:
        float scale;
        float rot_velocity;
    public:
        int health;
        friend std::ostream& operator<<(std::ostream& out, const Asteroid& obj) {
            return out << "Asteroid(pos: " << obj.position << 
                " scale: " << obj.scale << 
                " heading: " << obj.heading << 
                " speed: " << obj.speed << 
                " rot_velocity: " << obj.rot_velocity << 
                " health: " << obj.health << 
                ")";
        }
        Asteroid(ALLEGRO_DISPLAY *disp) : UpdateableObject(disp) {
            this->disp = disp;
            int w = al_get_display_width(disp);
            int h = al_get_display_height(disp);
            this->scale = (float)(rand()%30) / 10;
            this->heading = (float)(rand()%(int)(M_PI*100));
            this->health = (float)(rand()%200);
            this->rot_velocity = (float)(rand()%(int)(M_PI*10))/100;
            this->speed = (float)(rand()%50);
        }
        void update(float step) {
            UpdateableObject::update(step);
            this->heading += this->rot_velocity*step;
        }
        void draw() {
            ALLEGRO_TRANSFORM tr;
            al_identity_transform(&tr);
            al_rotate_transform(&tr, this->heading);
            al_translate_transform(&tr, this->position.x, this->position.y);
            al_use_transform(&tr);
            for (int i = 0; i < 12; i++) {
                al_draw_line(
                    asteroid_points[i][0]*this->scale,
                    asteroid_points[i][1]*this->scale,
                    asteroid_points[(i + 1)%12][0]*this->scale,
                    asteroid_points[(i + 1)%12][1]*this->scale,
                    this->color, 1
                );
            }
        }
        float getDangerRadius() {
            return 22*this->scale;
        }
};

bool isValid(Asteroid a) {
    return a.health > 0;
}

#endif
