#include "Scene.hpp"

int main()
{
    Scene* scene = new Scene();
    scene->initializeIrrlicht();
    scene->initializeData();

    while(scene->getDevice()->run())
    {
        scene->render();
    }

    scene->getDevice()->drop();
    delete scene;

    return 0;
}
