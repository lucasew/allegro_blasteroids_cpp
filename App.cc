#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "SingleLinkedList.cc"
#include "./Asteroid.cc"
#include "./Bullet.cc"
#include "Spaceship.cc"
#include "./Collision.cc"

template<class T>
void updateAll(T *o) {
    (*o).update(1);
}

template<class T>
void drawAll(T *o) {
    (*o).draw();
    std::cout << *o << std::endl;
}

class App {
    void draw() {
        al_clear_to_color(al_map_rgb(0,0,0));
        asteroids.forEach(drawAll);
        bullets.forEach(drawAll);
        ship.draw();
        al_flip_display();
        std::cout << ship << "   " << std::endl;
        std::cout << "PONTOS: " << this->pontos << std::endl;
        std::cout << "-------------------" << std::endl;
    }

    void update() {
        asteroids.forEach(updateAll);
        bullets.forEach(updateAll);
    }

    int gc() {
        int deleted = 0;
        deleted += asteroids.gc(isValid);
        deleted += bullets.gc(isValid);
        if (this->ship.health <= 0)
            closeASAP = true;
        return deleted;
    }
    int checkCollision() {
        return checkCollisions(&this->bullets, &this->asteroids) + checkCollisionSpaceship(&this->ship, &this->asteroids);
    }
    protected:
    ALLEGRO_DISPLAY *disp;
    SingleLinkedList<Asteroid> asteroids = SingleLinkedList<Asteroid>();
    SingleLinkedList<Bullet> bullets = SingleLinkedList<Bullet>();
    public:
    bool closeASAP = false;
    int pontos = 0;
    Spaceship ship = Spaceship(NULL, Point(), 0);
    App() {
        assert(al_init());
        assert(al_init_primitives_addon());
        this->disp = al_create_display(800, 600);
        this->ship = Spaceship(disp, Point(100, 100), 100);
        assert(this->disp);
    }
    void spawnAsteroid() {
        this->asteroids.add(Asteroid(disp));
    }
    void shotBullet() {
        auto bullet = Bullet(this->disp, ship.getPosition(), ship.getHeading());
        bullets.add(bullet);
        this->ship.reverse();
    }
    int handleApp() {
        update();
        this->pontos += checkCollision();
        int deleted = gc();
        draw();
        return deleted;
    }

    ~App() {
        al_destroy_display(disp);
        printf("GAME OVER!\n");
        printf("Pontos feitos: %i\n", this->pontos);
    }
};
