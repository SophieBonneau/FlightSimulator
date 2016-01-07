#include "GUIElements.hpp"
#include "CGUICompass.hpp"

#include <iostream>


GUIElements::GUIElements()
{
    this->smgr = nullptr;
    this->driver = nullptr;
    this->gui = nullptr;
    this->device = nullptr;

    // display values
    this->wind_speed = 20;
    this->altitude = 1000;
    this->vertical_speed = -20;
    this->gauge_offset = 0;
    this->stall = true;
}

GUIElements::~GUIElements()
{

}

void GUIElements::setDevice(IrrlichtDevice* device)
{
    this->device = device;
    this->smgr = this->device->getSceneManager();
    this->driver = this->device->getVideoDriver();
    this->gui = this->device->getGUIEnvironment();
}


bool GUIElements::initialize2DElements()
{
    if(this->device == nullptr || this->driver == nullptr || this->gui == nullptr || this->smgr == nullptr)
    {
        std::cout<<"Error: you must have set the device" <<
                   "to GUIElements before calling intialize2DElements"<<std::endl;
        return false;
    }

    // Compass
    this->texture_compass = this->driver->getTexture("data/2d/compass.png");
    this->image_compass = this->gui->addImage(ic::rect<s32>(10, 10, 80, 80));
    image_compass->setImage(this->texture_compass);
    image_compass->setScaleImage(true);
    // Level and arrows textures
    this->texture_level = this->driver->getTexture("data/2d/level.png");
    this->texture_arrows = this->driver->getTexture("data/2d/arrows.png");
    // Wind speed
    this->texture_wind_speed = this->driver->getTexture("data/2d/wind-speed.png");
    this->image_wind_speed = this->gui->addImage(ic::rect<s32>(10, 100, 120, 115));
    image_wind_speed->setImage(this->texture_wind_speed);
    image_wind_speed->setScaleImage(true);
    // Altitude
    this->texture_altitude = this->driver->getTexture("data/2d/altitude.png");
    this->image_altitude = this->gui->addImage(ic::rect<s32>(10, 120, 90, 135));
    image_altitude->setImage(this->texture_altitude);
    image_altitude->setScaleImage(true);
    // Vertical speed
    this->texture_vertical_speed = this->driver->getTexture("data/2d/vertical-speed.png");
    this->image_vertical_speed = this->gui->addImage(ic::rect<s32>(10, 140, 140, 155));
    image_vertical_speed->setImage(this->texture_vertical_speed);
    image_vertical_speed->setScaleImage(true);
    // Up/down plane
    this->texture_plane = this->driver->getTexture("data/2d/plane-up.png");
    // Red plane
    this->texture_plane_red = this->driver->getTexture("data/2d/plane-up-red.png");
    //Numbers
    this->numbers[0] = this->driver->getTexture("data/2d/numbers/0.png");
    this->numbers[1] = this->driver->getTexture("data/2d/numbers/1.png");
    this->numbers[2] = this->driver->getTexture("data/2d/numbers/2.png");
    this->numbers[3] = this->driver->getTexture("data/2d/numbers/3.png");
    this->numbers[4] = this->driver->getTexture("data/2d/numbers/4.png");
    this->numbers[5] = this->driver->getTexture("data/2d/numbers/5.png");
    this->numbers[6] = this->driver->getTexture("data/2d/numbers/6.png");
    this->numbers[7] = this->driver->getTexture("data/2d/numbers/7.png");
    this->numbers[8] = this->driver->getTexture("data/2d/numbers/8.png");
    this->numbers[9] = this->driver->getTexture("data/2d/numbers/9.png");
    // Places for the wind speed
    int width = 10;
    int height = 11;
    int height_u = 9;
    int offset = 1;
    this->ws_10000 = this->gui->addImage(ic::rect<s32>(120+offset,112-height, 120+offset+width,112)); ws_10000->setScaleImage(true);
    this->ws_1000  = this->gui->addImage(ic::rect<s32>(120+offset + offset+width,112-height, 120+offset+width + offset+width,112)); ws_1000->setScaleImage(true);
    this->ws_100   = this->gui->addImage(ic::rect<s32>(120+offset + 2*(offset+width),112-height, 120+offset+width + 2*(offset+width),112)); ws_100->setScaleImage(true);
    this->ws_10    = this->gui->addImage(ic::rect<s32>(120+offset + 3*(offset+width),112-height, 120+offset+width + 3*(offset+width),112)); ws_10->setScaleImage(true);
    this->ws_1     = this->gui->addImage(ic::rect<s32>(120+offset + 4*(offset+width),112-height, 120+offset+width + 4*(offset+width),112)); ws_1->setScaleImage(true);
    // Places for the altitude
    this->a_10000 = this->gui->addImage(ic::rect<s32>(90+offset,133-height, 90+offset+width,133)); a_10000->setScaleImage(true);
    this->a_1000  = this->gui->addImage(ic::rect<s32>(90+offset + offset+width,133-height, 90+offset+width + offset+width,133)); a_1000->setScaleImage(true);
    this->a_100   = this->gui->addImage(ic::rect<s32>(90+offset + 2*(offset+width),133-height, 90+offset+width + 2*(offset+width),133)); a_100->setScaleImage(true);
    this->a_10    = this->gui->addImage(ic::rect<s32>(90+offset + 3*(offset+width),133-height, 90+offset+width + 3*(offset+width),133)); a_10->setScaleImage(true);
    this->a_1     = this->gui->addImage(ic::rect<s32>(90+offset + 4*(offset+width),133-height, 90+offset+width + 4*(offset+width),133)); a_1->setScaleImage(true);
    // Places for vertical speed
    this->sign = this->gui->addImage(ic::rect<s32>(140+offset,153-height, 140+offset+width,153)); sign->setScaleImage(true);
    this->texture_plus = this->driver->getTexture("data/2d/+.png");
    this->texture_minus = this->driver->getTexture("data/2d/-.png");
    sign->setImage(this->texture_plus);
    this->vs_10000 = this->gui->addImage(ic::rect<s32>(140+offset+width,153-height, 140+offset+2*width,153)); sign->setScaleImage(true);vs_10000->setScaleImage(true);
    this->vs_1000  = this->gui->addImage(ic::rect<s32>(140+offset+width + offset+width,153-height, 140+offset+2*width + offset+width,153)); vs_1000->setScaleImage(true);
    this->vs_100   = this->gui->addImage(ic::rect<s32>(140+offset+width + 2*(offset+width),153-height, 140+offset+2*width + 2*(offset+width),153)); vs_100->setScaleImage(true);
    this->vs_10    = this->gui->addImage(ic::rect<s32>(140+offset+width + 3*(offset+width),153-height, 140+offset+2*width + 3*(offset+width),153)); vs_10->setScaleImage(true);
    this->vs_1     = this->gui->addImage(ic::rect<s32>(140+offset+width + 4*(offset+width),153-height, 140+offset+2*width + 4*(offset+width),153)); vs_1->setScaleImage(true);
    // Wind speed unity
    this->texture_wind_speed_u = this->driver->getTexture("data/2d/kmh.png");
    this->image_wind_speed_u = this->gui->addImage(ic::rect<s32>(120+offset+2*width + 4*(offset+width), 112-height, 120+offset+2*width+ 4*(offset+width)+40, 112));
    this->image_wind_speed_u->setImage(this->texture_wind_speed_u);
    this->image_wind_speed_u->setScaleImage(true);
    // Altitude unity
    this->texture_altitude_u = this->driver->getTexture("data/2d/m.png");
    this->image_altitude_u = this->gui->addImage(ic::rect<s32>(90+offset+2*width + 4*(offset+width),132-height_u, 90+offset+2*width + 4*(offset+width)+16,132));
    image_altitude_u->setImage(this->texture_altitude_u);
    image_altitude_u->setScaleImage(true);
    // Vertical speed unitys
    this->texture_vertical_speed_u = this->driver->getTexture("data/2d/ms.png");
    this->image_vertical_speed_u = this->gui->addImage(ic::rect<s32>(140+offset+3*width + 4*(offset+width),153-12, 140+offset+3*width + 4*(offset+width)+29,153));
    this->image_vertical_speed_u->setImage(this->texture_vertical_speed_u);
    this->image_vertical_speed_u->setScaleImage(true);
    // Gauge textures
    this->texture_gauge_empty = this->driver->getTexture("data/2d/gauge-empty.png");
    this->texture_gauge_full = this->driver->getTexture("data/2d/gauge-full.png");

    return true;
}

void GUIElements::setGaugeOffset(int& gauge_offset, int percentage, int gauge_height)
{
    if(percentage < 0 || percentage > 100)
    {
        std::cout<<"Error, the percentage must be between 0 and 100."<<std::endl;
    }
    else
    {
        double div = (gauge_height-4)*percentage/100;
        gauge_offset = (gauge_height-4) - int(div);
    }
}


bool GUIElements::update2DElements()
{
    if(this->device == nullptr || this->driver == nullptr || this->gui == nullptr || this->smgr == nullptr)
    {
        std::cout<<"Error: you must have set the device" <<
                   " to GUIElements before calling intialize2DElements"<<std::endl;
        return false;
    }

    //2D plane
    CGUICompass* compass_plane = new CGUICompass(ic::rect<s32>(20,160,50,190), gui, nullptr);
    compass_plane->setCompassTexture(this->texture_plane);
    if(this->vertical_speed <0)
    {
        compass_plane->setCompassHeading(90);
    }
    // Horizontal level
    CGUICompass* compass_level = new CGUICompass(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width/2 - 40,
                                                         this->device->getVideoDriver()->getScreenSize().Height/2 - 30,
                                                         this->device->getVideoDriver()->getScreenSize().Width/2 + 40,
                                                         this->device->getVideoDriver()->getScreenSize().Height/2 + 30), this->gui, nullptr);
    compass_level->setCompassTexture(texture_level);
    compass_level->setCompassHeading(0);
    // Gauge empty
    int gauge_width = 20;
    int gauge_height = 200;
    CGUICompass* compass_gauge_empty = new CGUICompass(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width -10 - gauge_width,
                                                                     10,
                                                                     this->device->getVideoDriver()->getScreenSize().Width -10,
                                                                     10 + gauge_height), this->gui, nullptr);
    compass_gauge_empty->setCompassTexture(texture_gauge_empty);
    //Gauge full
    setGaugeOffset(this->gauge_offset, 30, gauge_height);
    //gauge_offset = 0;
    CGUICompass* compass_gauge_full = new CGUICompass(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width -10 - gauge_width + 4,
                                                                     10 +2+this->gauge_offset,
                                                                     this->device->getVideoDriver()->getScreenSize().Width -10 -4,
                                                                     10 + gauge_height -1), this->gui, nullptr);
    compass_gauge_full->setCompassTexture(texture_gauge_full);

    // Arrows
    CGUICompass* compass_arrows = new CGUICompass(ic::rect<s32>(10, 10, 80, 80), this->gui, nullptr);
    compass_arrows->setCompassTexture(texture_arrows);
    compass_arrows->setCompassHeading(50);
    // Wind speed number update
    ws_10000->setImage(numbers[(this->wind_speed / 10000) % 10]);
    ws_1000->setImage(numbers[(this->wind_speed / 1000) % 10]);
    ws_100->setImage(numbers[(this->wind_speed / 100) % 10]);
    ws_10->setImage(numbers[(this->wind_speed / 10) % 10]);
    ws_1->setImage(numbers[(this->wind_speed / 1) % 10]);
    // altitude number update
    a_10000->setImage(numbers[(this->altitude / 10000) % 10]);
    a_1000->setImage(numbers[(this->altitude / 1000) % 10]);
    a_100->setImage(numbers[(this->altitude / 100) % 10]);
    a_10->setImage(numbers[(this->altitude / 10) % 10]);
    a_1->setImage(numbers[(this->altitude / 1) % 10]);
    // vertical speed number update
    vs_10000->setImage(numbers[(abs(this->vertical_speed) / 10000) % 10]);
    vs_1000->setImage(numbers[(abs(this->vertical_speed) / 1000) % 10]);
    vs_100->setImage(numbers[(abs(this->vertical_speed) / 100) % 10]);
    vs_10->setImage(numbers[(abs(this->vertical_speed) / 10) % 10]);
    vs_1->setImage(numbers[(abs(this->vertical_speed) / 1) % 10]);
    // Update the 2d plane orientation, color and the vertical speed sign
    if(this->vertical_speed >= 0)
    {
        sign->setImage(texture_plus);
        compass_plane->setCompassHeading(0);
    }
    else
    {
        sign->setImage(texture_minus);
        if(this->stall == true)
        {
            compass_plane->setCompassTexture(texture_plane_red);
        }
        compass_plane->setCompassHeading(-55);


    }

    // Draw compass elements
    compass_level->draw();
    compass_arrows->draw();
    compass_plane->draw();
    compass_gauge_empty->draw();
    compass_gauge_full->draw();

    return true;
}

