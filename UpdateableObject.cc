#ifndef AB_UPDATEABLE_OBJECT
#define AB_UPDATEABLE_OBJECT

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

#include "./Point.cc"

class UpdateableObject {
    protected:
        float heading; // Em radianos
        float speed;
        ALLEGRO_COLOR color;
        ALLEGRO_DISPLAY *disp;
        Point position = Point(0, 0);
    public:
        UpdateableObject(ALLEGRO_DISPLAY *disp) {
            this->disp = disp;
            int w = al_get_display_width(disp);
            int h = al_get_display_height(disp);
            this->position.x = (float)(rand()%w);
            this->position.y = (float)(rand()%h);
            this->heading = (float)(rand()%(int)(M_PI*100));
            this->speed = (float)(rand()%50);
            this->color = al_map_rgb(rand()%256, rand()%256, rand()%256);
        }
        void update(float step) {
            int w = al_get_display_width(disp);
            int h = al_get_display_height(disp);
            this->position.goAhead(this->speed*step, heading);
            if (this->position.x > w)
                this->position.x = 0;
            if (this->position.x < 0)
                this->position.x = w;
            if (this->position.y > h)
                this->position.y = 0;
            if (this->position.y < 0)
                this->position.y = h;
        }
        void draw();
        void isInvalidated();
        Point getPosition() {
            return this->position;
        }
};

#endif
