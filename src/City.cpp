#include "City.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
City::City(is::ISceneManager* smgr, irr::io::path meshPath)
    :smgr(smgr), meshPath(meshPath)
{
    this->scale = ic::vector3df(10,10,10);
}

// To initialize mesh and node
int City::initialize()
{
    is::IMesh *city_mesh = smgr->getMesh(this->meshPath);
    is::ISceneNode *city_node;
    city_node = smgr->addOctreeSceneNode(city_mesh,nullptr,-1,1024);
    city_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    city_node->setScale(this->scale);

    return 0;
}
