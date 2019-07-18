#include "./SingleLinkedList.cc"
#include "./Bullet.cc"
#include "./Asteroid.cc"
#include "./Spaceship.cc"

bool isCollision(Bullet b, Asteroid a) {
    std::cout << "COLLISION: " << a << " (" << a.getDangerRadius() << ")" << ", " << b<< " (" << b.getDangerRadius() << ")" << std::endl;
    return (a.getPosition().getDistance(b.getPosition())) < a.getDangerRadius() + b.getDangerRadius();
}

bool isCollision(Spaceship s, Asteroid a) {
    std::cout << "COLLISION: " << a << " (" << a.getDangerRadius() << ")" << ", " << s << " (" << s.getDangerRadius() << ")" << std::endl;
    return (a.getPosition().getDistance(s.getPosition())) < a.getDangerRadius() + s.getDangerRadius();
}

int checkCollisionSpaceship(Spaceship *s, SingleLinkedList<Asteroid> *asteroids) {
    int pts = 0;
    auto iast = asteroids->asIterator();
    while (1) {
        try {
            auto a = iast.next();
            if (isCollision(*s, *a)) {
                s->health -= 1;
                a->health -= 1;
                pts++;
            }
        }
        catch (int) {
            break;
        }
    }
    return pts;
}

int checkCollisions(SingleLinkedList<Bullet> *b, SingleLinkedList<Asteroid> *a) {
    int pts = 0;
    auto ibullet = b->asIterator();
    while (1) {
        try {
            auto bul = ibullet.next();
            auto iasteroid = a->asIterator();
            while (1) {
                try {
                    auto ast = iasteroid.next();
                    if (isCollision(*bul, *ast)) {
                        pts += bul->power;
                        ast->health -= bul->power;
                        bul->power = 0;
                    }
                } catch (int) {
                    break;
                }
            }
        } catch (int) {
            break;
        }
    }
    return pts;
}
