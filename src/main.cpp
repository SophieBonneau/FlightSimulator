#include "Scene.hpp"


    /*while(device->run())
    {

        if(inFlight && crash == false)
        {
            //Movements of the plane
            ic::vector3df rotation = parentNode->getRotation();

            rotation.Y = receiver.getRotation();
            parentNode->setRotation(rotation);

            planeSpeed      = receiver.getSpeed();
            planeAltitude   = receiver.getAltitude();

            ic::vector3df position = parentNode->getPosition();

            position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
            position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
            position.Y  = planeAltitude;

            rotation_screw.Z += 30.0;

            parentNode->setPosition(position);
            screw_node->setRotation(rotation_screw);

            receiver.movePlane(parentRotationNode, leftwing_node, rightwing_node, tail_node, lefttail_node, rightttail_node);

        }
        else
        {
            std::cout<<"TD : plane on the ground, in take-off position and in landing position"<<std::endl;
        }

        //Detection of collisions
        ic::vector3df firePosition = ic::vector3df(0.0,-0.1,3.);
        ps->setPosition(parentNode->getPosition() + firePosition); //position of the fire particules
        if(collisionCity->collisionOccurred() == true)
        {
            firePosition.X = collisionCity->getCollisionPoint().X;
            firePosition.Y = collisionCity->getCollisionPoint().Y;
            firePosition.Z = collisionCity->getCollisionPoint().Z;
            ps->setEmitter(em); // this grabs the emitter of fire particules

            crash = true;
        }

        //Camera position
        smgr->addCameraSceneNode(plane_node, ic::vector3df(0, 5, -34), parentNode->getPosition()); //0,5,-34

        //Back color
        driver->beginScene(true,true,iv::SColor(100,150,200,255));

        // Draw the scene
        smgr->drawAll();
        gui->drawAll();

        for(unsigned int i = 0; i < compasses.size(); i++)
        {
            compasses[i]->draw();
        }

        driver->endScene();*/


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
