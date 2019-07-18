#include <assert.h>
#include "./PlayableApp.cc"

int main() {
    auto app = PlayableApp(10);
    while(!app.closeASAP) {
        app.tick();
    }
}
