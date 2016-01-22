#include "CGUICompass.hpp"


#include <irrlicht.h>

#include <iostream>


using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;

CGUICompass::CGUICompass(ic::rect<s32> rect, ig::IGUIEnvironment* env, ig::IGUIElement* parent)
    : ig::IGUIElement(ig::EGUIET_ELEMENT, env, parent, -1, rect)
{
    this->rectangle = rect;
    Mesh.Vertices.set_used(4);
    Mesh.Indices .set_used(6);

    video::SColor white(255, 255, 255, 255);

    Mesh.Vertices[0] = video::S3DVertex(-1.f, -1.f, 0.f, 0.f, 0.f, 1.f, white, 0.f, 1.f);
    Mesh.Vertices[1] = video::S3DVertex(-1.f, 1.f, 0.f, 0.f, 0.f, 1.f, white, 0.f, 0.f);
    Mesh.Vertices[2] = video::S3DVertex( 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, white, 1.f, 0.f);
    Mesh.Vertices[3] = video::S3DVertex( 1.f, -1.f, 0.f, 0.f, 0.f, 1.f, white, 1.f, 1.f);

    Mesh.Indices[0] = 0;
    Mesh.Indices[1] = 1;
    Mesh.Indices[2] = 2;
    Mesh.Indices[3] = 2;
    Mesh.Indices[4] = 3;
    Mesh.Indices[5] = 0;

    Mesh.getMaterial().Lighting = false;

    Mesh.getMaterial().MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
}

void CGUICompass::setCompassRelativePosition(ic::rect<s32> rect)
{
    this->RelativeRect = rect;
    this->AbsoluteRect = rect;
    this->AbsoluteClippingRect = rect;
    this->DesiredRect = rect;
}

void CGUICompass::setCompassTexture(iv::ITexture* texture)
{
    Mesh.getMaterial().setTexture(0,texture);
}

void CGUICompass::setCompassHeading(f32 deg)
{
    Matrix.makeIdentity();
    Matrix.setRotationDegrees(ic::vector3df(0, 0, deg));
}


void CGUICompass::draw()
{
    if(this->RelativeRect.getHeight() >1 && this->RelativeRect.getWidth() >1)
    {
        //position.X
        iv::IVideoDriver* driver = Environment->getVideoDriver();
        if (! (driver && IsVisible))
            return;

        ic::rect<s32> oldViewPort = driver->getViewPort();
        driver->setViewPort(getAbsolutePosition());

        // clear the projection matrix
        ic::matrix4 oldProjMat = driver->getTransform(video::ETS_PROJECTION);
        driver->setTransform(iv::ETS_PROJECTION, ic::matrix4());

        // clear the view matrix
        core::matrix4 oldViewMat = driver->getTransform(video::ETS_VIEW);
        driver->setTransform(iv::ETS_VIEW, core::matrix4());

        driver->setTransform(iv::ETS_WORLD, Matrix);

        driver->setMaterial(Mesh.Material);

        driver->drawMeshBuffer(&Mesh);

        // restore view matrix
        driver->setTransform(iv::ETS_VIEW, oldViewMat);

        // restore projection matrix
        driver->setTransform(iv::ETS_PROJECTION, oldProjMat);

        // restore the view area
        driver->setViewPort(oldViewPort);
    }

}

