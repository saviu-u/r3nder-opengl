#include "screen.h"
#include "custom_cube.h"
#include "prebuilt/camera.h"

int main()
{
  Screen screen;
  CustomCube cube(2.0f, 1.0f, 0.5f);
  cube.rotateTo({45, 30, 0});

  Camera mainCamera;
  mainCamera.moveTo({0,0,-5});
  mainCamera.rotateTo({0,0,0});

  screen.addObjectToScene(mainCamera);
  screen.addObjectToScene(cube);

  screen.setMainCamera(mainCamera);

  screen.eventLoop();
  screen.close();

  return 0;
}
