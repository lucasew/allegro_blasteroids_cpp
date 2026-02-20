#include "./PlayableApp.cc"
#include <assert.h>

int main() {
  auto app = PlayableApp(10);
  while (!app.closeASAP) {
    app.tick();
  }
}
