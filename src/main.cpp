#include "Scene.hpp"

<<<<<<< HEAD
=======

>>>>>>> 4674281f0599dde88edadcdc79c9a4a70916c023
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

    return 0;
}
