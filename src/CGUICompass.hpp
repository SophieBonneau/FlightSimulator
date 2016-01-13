#include <irrlicht.h>

#include <iostream>


using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

class CGUICompass : public ig::IGUIElement
{
    public:
    CGUICompass(ic::rect<s32> rect, ig::IGUIEnvironment* env, ig::IGUIElement* parent)
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
        //Mesh.getMaterial().BackfaceCulling = false;
        //Mesh.getMaterial().Wireframe = true;
        //Mesh.getMaterial().MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;

        Mesh.getMaterial().MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
    }

    //
    void setCompassTexture(iv::ITexture* texture)
    {
        Mesh.getMaterial().setTexture(0,texture);
        //Environment->getVideoDriver()->makeColorKeyTexture(Mesh.getMaterial().getTexture(0),video::SColor(0,0,0,1));
        //Environment->getVideoDriver()->makeColorKeyTexture(Mesh.getMaterial().getTexture(0),video::SColor(0,0,0,1));
    }

    void setCompassHeading(f32 deg)
    {
        Matrix.makeIdentity();
        Matrix.setRotationDegrees(ic::vector3df(0, 0, deg));
    }


    //! render the compass
    virtual void draw()
    {
        if(this->rectangle.getHeight() >0 && this->rectangle.getWidth() >0)
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

            //driver->makeColorKeyTexture(Mesh.getMaterial().getTexture(0),video::SColor(255,255,255,1));


            // restore view matrix
            driver->setTransform(iv::ETS_VIEW, oldViewMat);

            // restore projection matrix
            driver->setTransform(iv::ETS_PROJECTION, oldProjMat);

            // restore the view area
            driver->setViewPort(oldViewPort);
        }

    }

    private:
    is::SMeshBuffer Mesh;
    ic::matrix4 Matrix;
    ic::rect<s32> rectangle;
};
