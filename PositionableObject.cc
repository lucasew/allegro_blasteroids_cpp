#ifndef AB_POSITIONABLE_OBJECT
#define AB_POSITIONABLE_OBJECT

#include "./Point.cc"

class PositionableObject {
    public:
        virtual Point getPosition() = 0;
};

#endif
