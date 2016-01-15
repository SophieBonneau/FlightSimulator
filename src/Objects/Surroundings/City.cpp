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
void City::initialize()
{
    this->mesh = smgr->getMesh(this->meshPath);
    this->node = smgr->addOctreeSceneNode(this->mesh,nullptr,-1,1024);
    this->node->setMaterialFlag(iv::EMF_LIGHTING,false);
    this->node->setScale(this->scale);
}
