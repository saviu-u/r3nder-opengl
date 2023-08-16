#include "screen.h"
#include "prebuilt/cube.h"

int main()
{
  Screen screen;
  Cube cube(2.0f);

  screen.addObjectToScene(cube);

  screen.eventLoop();
  screen.close();

  return 0;
}
