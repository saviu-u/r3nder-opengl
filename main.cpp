#include "screen.h"
#include "prebuilt/cube.h"
#include "prebuilt/camera.h"

int main()
{
  Screen screen;
  Cube cube(2.0f);
  cube.rotateTo({45, 30, 0});

  Camera mainCamera;
  mainCamera.moveTo({0,0,5});
  mainCamera.rotateTo({0,180,0});

  screen.addObjectToScene(mainCamera);
  screen.addObjectToScene(cube);

  screen.setMainCamera(mainCamera);

  screen.eventLoop();
  screen.close();

  return 0;
}
