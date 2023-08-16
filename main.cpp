#include "screen.h"
#include "prebuilt/cube.h"

int main()
{
  Screen screen;
  Cube cube(2.0f);
  cube.rotateTo({45, 30, 0});

  screen.addObjectToScene(cube);

  screen.eventLoop();
  screen.close();

  return 0;
}
