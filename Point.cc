#ifndef AB_POINT
#define AB_POINT

#include <math.h>
#include <iostream>

class Point {
    public:
        friend std::ostream& operator<<(std::ostream& out, const Point& obj) {
            return out << "Point(x: " << obj.x << 
                " y: " << obj.y << 
                ")";
        }
        float x, y;
        Point() {
            Point(0,0);
        }
        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }
        float getDistance(Point p) {
            return sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
        }
        void goAhead(float amount, float heading) {
            this->x += amount*sin(heading);
            this->y -= amount*cos(heading);
        }
};

#endif
