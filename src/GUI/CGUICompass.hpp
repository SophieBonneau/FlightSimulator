#pragma once

#ifndef CGUICOMPASS
#define CGUICOMPASS


#include <irrlicht.h>

#include <iostream>


/* Class CGUICompass: This class inherits from IGUIElement Irrlicht class and manages the rotation of images
*/
class CGUICompass : public irr::gui::IGUIElement
{
    public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor EventReceiver: Creates a mesh that will contain the image and make it manage transparency.
     *  * params:   irr::core::rect<irr::s32>: the rectangle defining the image boundaries
     *              irr::gui::IGUIEnvironment*: the gui environment
     *              irr::gui::IGUIElement*: the parent GUI element. Can be set to nullptr
    */
    CGUICompass(irr::core::rect<irr::s32> rect, irr::gui::IGUIEnvironment* env, irr::gui::IGUIElement* parent);


    /************************************************************************************/
    /******************************** Public functions *********************************/
    /************************************************************************************/
    /* void setCompassRelativePosition: to define new position and dimensions of the image with a new bounding rectangle
    */
    void setCompassRelativePosition(irr::core::rect<irr::s32> rect);

    /* void setCompassTexture: to assign a texture to the image
    */
    void setCompassTexture(irr::video::ITexture* texture);

    /* void setCompassHeading: apply a rotation to the mesh containing the image
    */
    void setCompassHeading(irr::f32 deg);

    /* void draw: draw the rotated image in the screen by setting the corresponding transform to the driver
    */
    virtual void draw();

    private:

    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    irr::scene::SMeshBuffer Mesh;
    irr::core::matrix4 Matrix;
    irr::core::rect<irr::s32> rectangle;

};

#endif
