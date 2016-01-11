#include "GUIElements.hpp"
#include "CGUICompass.hpp"

#include <iostream>


GUIElements::GUIElements()
{
    this->smgr = nullptr;
    this->driver = nullptr;
    this->gui = nullptr;
    this->device = nullptr;

    // Display values
    this->wind_speed = 20;
    this->altitude = 1000;
    this->vertical_speed = -20;
    this->gauge_offset = 0;
    this->stall = true;
    this->gauge_percentage = 70;

    // Positions
    this->background_height = 80;
    this->background_width = 250;
    this->background_offset_x = 10;
    this->background_offset_y = 10;
    this->text_offset_x = 10;
    this->text_offset_y = 10;
    this->text_ws_length = 100;
    this->text_ws_u_length = 37;
    this->text_ws_height = 15;
    this->text_altitude_length = 70;
    this->text_altitude_u_length = 13;
    this->text_altitude_height = 13;
    this->text_vs_length = 110;
    this->text_vs_height = 14;
    this->text_vs_u_length = 25;
    this->text_number_height = 12;
    this->text_number_length = 10;
    this->text_number_offset_x = 1;
    this->text_space_length = 3;
    this->plane_offset_x = 20;
    this->plane_offset_y = 20;
    this->plane_height = 50;
    this->plane_width = 75;
    this->gauge_height = 25;
    this->gauge_width = 250;
    this->gauge_offset_x = 10;
    this->gauge_offset_y = 10;
    this->fuel_offset_x = 10;
    this->fuel_height = 25;
    this->fuel_width = 24;


    // Blinking elements
    plane_red = true;

    // Timer
    this->timer = 0;


}

GUIElements::~GUIElements()
{

}

ic::vector2d<s32> GUIElements::getUpperLeftPoint(ig::IGUIImage* image)
{
    ic::vector2d<s32> point = image->getRelativePosition().getCenter();
    point.X -= image->getRelativePosition().getWidth()/2;
    point.Y -= image->getRelativePosition().getHeight()/2;

    return point;
}

ic::vector2d<s32> GUIElements::getLowerRightPoint(ig::IGUIImage* image)
{
    ic::vector2d<s32> point = image->getRelativePosition().getCenter();
    point.X += image->getRelativePosition().getWidth()/2;
    point.Y -= image->getRelativePosition().getHeight()/2;

    return point;
}



void GUIElements::setDevice(IrrlichtDevice* device)
{
    this->device = device;
    this->smgr = this->device->getSceneManager();
    this->driver = this->device->getVideoDriver();
    this->gui = this->device->getGUIEnvironment();
}

void GUIElements::setStall(const bool& stall)
{
    this->stall = stall;
}


bool GUIElements::initialize2DElements()
{
    if(this->device == nullptr || this->driver == nullptr || this->gui == nullptr || this->smgr == nullptr)
    {
        std::cout<<"Error: you must have set the device" <<
                   "to GUIElements before calling intialize2DElements"<<std::endl;
        return false;
    }

    // Background
    this->texture_background = this->driver->getTexture("data/2d/background.png");
    this->image_background = this->gui->addImage(ic::rect<s32>(background_offset_x,
                                                               this->device->getVideoDriver()->getScreenSize().Height -background_offset_y - background_height,
                                                               background_offset_x + background_width,
                                                               this->device->getVideoDriver()->getScreenSize().Height -background_offset_y));
    this->image_background->setImage(this->texture_compass);
    this->image_background->setScaleImage(true);
    // Compass
    this->texture_compass = this->driver->getTexture("data/2d/compass.png");
    this->image_compass = this->gui->addImage(ic::rect<s32>(10, 10, 85, 85));
    this->image_compass->setImage(this->texture_compass);
    this->image_compass->setScaleImage(true);
    // Level and arrows textures
    this->texture_level = this->driver->getTexture("data/2d/level.png");
    this->texture_arrows = this->driver->getTexture("data/2d/arrows.png");
    // Wind speed
    this->texture_wind_speed = this->driver->getTexture("data/2d/wind-speed.png");

    ic::vector2d<s32> background_ulp = this->getUpperLeftPoint(this->image_background);
    this->image_wind_speed = this->gui->addImage(ic::rect<s32>(background_ulp.X + text_offset_x,
                                                               background_ulp.Y + text_offset_y,
                                                               background_ulp.X + text_offset_x + text_ws_length,
                                                               background_ulp.Y + text_offset_y + text_ws_height));
    image_wind_speed->setImage(this->texture_wind_speed);
    image_wind_speed->setScaleImage(true);
    // Altitude
    this->texture_altitude = this->driver->getTexture("data/2d/altitude.png");
    this->image_altitude = this->gui->addImage(ic::rect<s32>(background_ulp.X + text_offset_x,
                                                             background_ulp.Y + 3*text_offset_y,
                                                             background_ulp.X + text_offset_x + text_altitude_length,
                                                             background_ulp.Y + 3*text_offset_y + text_altitude_height));
    image_altitude->setImage(this->texture_altitude);
    image_altitude->setScaleImage(true);
    // Vertical speed
    this->texture_vertical_speed = this->driver->getTexture("data/2d/vertical-speed.png");
    this->image_vertical_speed = this->gui->addImage(ic::rect<s32>(background_ulp.X + text_offset_x,
                                                                   background_ulp.Y + 5*text_offset_y,
                                                                   background_ulp.X + text_offset_x + text_vs_length,
                                                                   background_ulp.Y + 5*text_offset_y + text_vs_height));
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
    ic::vector2d<s32> ws_lrp = this->getLowerRightPoint(this->image_wind_speed);
    this->ws_10000 = this->gui->addImage(ic::rect<s32>(ws_lrp.X + text_number_offset_x,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + text_number_length,
                                                       ws_lrp.Y + text_number_height)); ws_10000->setScaleImage(true);
    this->ws_1000  = this->gui->addImage(ic::rect<s32>(ws_lrp.X + text_number_offset_x + text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       ws_lrp.Y + text_number_height)); ws_1000->setScaleImage(true);
    this->ws_100   = this->gui->addImage(ic::rect<s32>(ws_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       ws_lrp.Y + text_number_height)); ws_100->setScaleImage(true);
    this->ws_10    = this->gui->addImage(ic::rect<s32>(ws_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       ws_lrp.Y + text_number_height)); ws_10->setScaleImage(true);
    this->ws_1     = this->gui->addImage(ic::rect<s32>(ws_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 5*text_number_length,
                                                       ws_lrp.Y + text_number_height)); ws_1->setScaleImage(true);
    // Places for the altitude
    ic::vector2d<s32> altitude_lrp = this->getLowerRightPoint(this->image_altitude);
    this->a_10000 = this->gui->addImage(ic::rect<s32>(altitude_lrp.X + text_number_offset_x,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + text_number_length,
                                                      altitude_lrp.Y + text_number_height)); a_10000->setScaleImage(true);
    this->a_1000  = this->gui->addImage(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 2*text_number_length,
                                                      altitude_lrp.Y + text_number_height)); a_1000->setScaleImage(true);
    this->a_100   = this->gui->addImage(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + 2*text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 3*text_number_length,
                                                      altitude_lrp.Y + text_number_height)); a_100->setScaleImage(true);
    this->a_10    = this->gui->addImage(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + 3*text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 4*text_number_length,
                                                      altitude_lrp.Y + text_number_height)); a_10->setScaleImage(true);
    this->a_1     = this->gui->addImage(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + 4*text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 5*text_number_length,
                                                      altitude_lrp.Y + text_number_height)); a_1->setScaleImage(true);
    // Places for vertical speed
    ic::vector2d<s32> vs_lrp = this->getLowerRightPoint(this->image_vertical_speed);
    this->sign = this->gui->addImage(ic::rect<s32>(vs_lrp.X + text_number_offset_x,
                                                   vs_lrp.Y ,
                                                   vs_lrp.X + text_number_offset_x + text_number_length,
                                                   vs_lrp.Y + text_number_height)); sign->setScaleImage(true);
    this->texture_plus = this->driver->getTexture("data/2d/+.png");
    this->texture_minus = this->driver->getTexture("data/2d/-.png");
    sign->setImage(this->texture_plus);
    this->vs_10000 = this->gui->addImage(ic::rect<s32>(vs_lrp.X + text_number_offset_x + text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       vs_lrp.Y + text_number_height)); vs_10000->setScaleImage(true);
    this->vs_1000  = this->gui->addImage(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       vs_lrp.Y + text_number_height)); vs_1000->setScaleImage(true);
    this->vs_100   = this->gui->addImage(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       vs_lrp.Y + text_number_height)); vs_100->setScaleImage(true);
    this->vs_10    = this->gui->addImage(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 5*text_number_length,
                                                       vs_lrp.Y + text_number_height)); vs_10->setScaleImage(true);
    this->vs_1     = this->gui->addImage(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 5*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 6*text_number_length,
                                                       vs_lrp.Y + text_number_height)); vs_1->setScaleImage(true);
    // Wind speed unity
    ic::vector2d<s32> ws_last_number_lrp = this->getLowerRightPoint(this->ws_1);
    this->texture_wind_speed_u = this->driver->getTexture("data/2d/kmh.png");
    this->image_wind_speed_u = this->gui->addImage(ic::rect<s32>(ws_last_number_lrp.X + text_number_offset_x + text_space_length,
                                                                 ws_last_number_lrp.Y ,
                                                                 ws_last_number_lrp.X + text_number_offset_x + text_ws_u_length + text_space_length,
                                                                 ws_last_number_lrp.Y + text_number_height));
    this->image_wind_speed_u->setImage(this->texture_wind_speed_u);
    this->image_wind_speed_u->setScaleImage(true);
    // Altitude unity
    ic::vector2d<s32> altitude_last_number_lrp = this->getLowerRightPoint(this->a_1);
    this->texture_altitude_u = this->driver->getTexture("data/2d/m.png");
    this->image_altitude_u = this->gui->addImage(ic::rect<s32>(altitude_last_number_lrp.X + text_number_offset_x + text_space_length,
                                                               altitude_last_number_lrp.Y ,
                                                               altitude_last_number_lrp.X + text_number_offset_x + text_altitude_u_length + text_space_length,
                                                               altitude_last_number_lrp.Y + text_number_height));
    this->image_altitude_u->setImage(this->texture_altitude_u);
    this->image_altitude_u->setScaleImage(true);
    // Vertical speed unity
    this->texture_vertical_speed_u = this->driver->getTexture("data/2d/ms.png");
    ic::vector2d<s32> vs_last_number_lrp = this->getLowerRightPoint(this->vs_1);
    this->image_vertical_speed_u = this->gui->addImage(ic::rect<s32>(vs_last_number_lrp.X + text_number_offset_x + text_space_length,
                                                                     vs_last_number_lrp.Y ,
                                                                     vs_last_number_lrp.X + text_number_offset_x + text_vs_u_length + text_space_length,
                                                                     vs_last_number_lrp.Y + text_number_height));
    this->image_vertical_speed_u->setImage(this->texture_vertical_speed_u);
    this->image_vertical_speed_u->setScaleImage(true);
    // Gauge textures
    this->texture_gauge_empty = this->driver->getTexture("data/2d/gauge-empty.png");
    this->texture_gauge_full_red = this->driver->getTexture("data/2d/gauge-full-red.png");
    this->texture_gauge_full_green = this->driver->getTexture("data/2d/gauge-full-green.png");
    this->texture_gauge_full_orange = this->driver->getTexture("data/2d/gauge-full-orange.png");
    // Gauge empty
    this->image_gauge_empty = this->gui->addImage(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width - this->gauge_width - gauge_offset_x,
                                                                     this->device->getVideoDriver()->getScreenSize().Height - this->gauge_height - gauge_offset_y,
                                                                     this->device->getVideoDriver()->getScreenSize().Width - gauge_offset_x,
                                                                     this->device->getVideoDriver()->getScreenSize().Height - gauge_offset_y));
    this->image_gauge_empty->setImage(this->texture_gauge_empty);
    this->image_gauge_empty->setScaleImage(true);

    // Fuel
    this->texture_fuel = this->driver->getTexture("data/2d/fuel.png");
    ic::vector2d<s32> gauge_ulp = this->getUpperLeftPoint(this->image_gauge_empty);
    this->image_fuel = this->gui->addImage(ic::rect<s32>(gauge_ulp.X - this->fuel_width - this->fuel_offset_x,
                                                                     gauge_ulp.Y,
                                                                     gauge_ulp.X - this->fuel_offset_x,
                                                                     gauge_ulp.Y + this->fuel_height));
    this->image_fuel->setImage(this->texture_fuel);
    this->image_fuel->setScaleImage(true);

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


std::vector<CGUICompass*> GUIElements::update2DElements()
{
    std::vector<CGUICompass*> compasses;
    if(this->device == nullptr || this->driver == nullptr || this->gui == nullptr || this->smgr == nullptr)
    {
        std::cout<<"Error: you must have set the device" <<
                   " to GUIElements before calling intialize2DElements"<<std::endl;
        return compasses;
    }

    // Compass
    this->image_background->setRelativePosition(ic::rect<s32>(background_offset_x,
                                                              this->device->getVideoDriver()->getScreenSize().Height -background_offset_y - background_height,
                                                              background_offset_x + background_width,
                                                              this->device->getVideoDriver()->getScreenSize().Height -background_offset_y));
    // Gauge empty
    this->image_gauge_empty->setRelativePosition(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width - this->gauge_width - gauge_offset_x,
                                                                     this->device->getVideoDriver()->getScreenSize().Height - this->gauge_height - gauge_offset_y,
                                                                     this->device->getVideoDriver()->getScreenSize().Width - gauge_offset_x,
                                                                     this->device->getVideoDriver()->getScreenSize().Height - gauge_offset_y));
    // Fuel
    ic::vector2d<s32> gauge_ulp = this->getUpperLeftPoint(this->image_gauge_empty);
    this->image_fuel->setRelativePosition(ic::rect<s32>(gauge_ulp.X - this->fuel_width - this->fuel_offset_x,
                                                                     gauge_ulp.Y,
                                                                     gauge_ulp.X - this->fuel_offset_x,
                                                                     gauge_ulp.Y + this->fuel_height));
    //Windspeed
    ic::vector2d<s32> background_ulp = this->getUpperLeftPoint(this->image_background);
    this->image_wind_speed->setRelativePosition(ic::rect<s32>(background_ulp.X + text_offset_x,
                                                                   background_ulp.Y + text_offset_y,
                                                                   background_ulp.X + text_offset_x + text_ws_length,
                                                                   background_ulp.Y + text_offset_y + text_ws_height));
    //Altitude
    this->image_altitude->setRelativePosition(ic::rect<s32>(background_ulp.X + text_offset_x,
                                                                 background_ulp.Y + 3*text_offset_y,
                                                                 background_ulp.X + text_offset_x + text_altitude_length,
                                                                 background_ulp.Y + 3*text_offset_y + text_altitude_height));
    // Vertical altitude
    this->image_vertical_speed->setRelativePosition(ic::rect<s32>(background_ulp.X + text_offset_x,
                                                                       background_ulp.Y + 5*text_offset_y,
                                                                       background_ulp.X + text_offset_x + text_vs_length,
                                                                       background_ulp.Y + 5*text_offset_y + text_vs_height));
    // Numbers
    ic::vector2d<s32> ws_lrp = this->getLowerRightPoint(this->image_wind_speed);
    this->ws_10000->setRelativePosition(ic::rect<s32>(ws_lrp.X + text_number_offset_x,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + text_number_length,
                                                       ws_lrp.Y + text_number_height));
    this->ws_1000->setRelativePosition(ic::rect<s32>(ws_lrp.X + text_number_offset_x + text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       ws_lrp.Y + text_number_height));
    this->ws_100->setRelativePosition(ic::rect<s32>(ws_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       ws_lrp.Y + text_number_height));
    this->ws_10->setRelativePosition(ic::rect<s32>(ws_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       ws_lrp.Y + text_number_height));
    this->ws_1->setRelativePosition(ic::rect<s32>(ws_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       ws_lrp.Y ,
                                                       ws_lrp.X + text_number_offset_x + 5*text_number_length,
                                                       ws_lrp.Y + text_number_height));
    ic::vector2d<s32> altitude_lrp = this->getLowerRightPoint(this->image_altitude);
    this->a_10000->setRelativePosition(ic::rect<s32>(altitude_lrp.X + text_number_offset_x,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + text_number_length,
                                                      altitude_lrp.Y + text_number_height));
    this->a_1000->setRelativePosition(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 2*text_number_length,
                                                      altitude_lrp.Y + text_number_height));
    this->a_100->setRelativePosition(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + 2*text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 3*text_number_length,
                                                      altitude_lrp.Y + text_number_height));
    this->a_10->setRelativePosition(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + 3*text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 4*text_number_length,
                                                      altitude_lrp.Y + text_number_height));
    this->a_1->setRelativePosition(ic::rect<s32>(altitude_lrp.X + text_number_offset_x + 4*text_number_length,
                                                      altitude_lrp.Y ,
                                                      altitude_lrp.X + text_number_offset_x + 5*text_number_length,
                                                      altitude_lrp.Y + text_number_height));
    ic::vector2d<s32> vs_lrp = this->getLowerRightPoint(this->image_vertical_speed);
    this->sign->setRelativePosition(ic::rect<s32>(vs_lrp.X + text_number_offset_x,
                                                   vs_lrp.Y ,
                                                   vs_lrp.X + text_number_offset_x + text_number_length,
                                                   vs_lrp.Y + text_number_height));
    this->vs_10000->setRelativePosition(ic::rect<s32>(vs_lrp.X + text_number_offset_x + text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       vs_lrp.Y + text_number_height));
    this->vs_1000->setRelativePosition(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 2*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       vs_lrp.Y + text_number_height));
    this->vs_100->setRelativePosition(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 3*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       vs_lrp.Y + text_number_height));
    this->vs_10->setRelativePosition(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 4*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 5*text_number_length,
                                                       vs_lrp.Y + text_number_height));
    this->vs_1->setRelativePosition(ic::rect<s32>(vs_lrp.X + text_number_offset_x + 5*text_number_length,
                                                       vs_lrp.Y ,
                                                       vs_lrp.X + text_number_offset_x + 6*text_number_length,
                                                       vs_lrp.Y + text_number_height));
    // Unities
    ic::vector2d<s32> ws_last_number_lrp = this->getLowerRightPoint(this->ws_1);
    this->image_wind_speed_u->setRelativePosition(ic::rect<s32>(ws_last_number_lrp.X + text_number_offset_x + text_space_length,
                                                                 ws_last_number_lrp.Y ,
                                                                 ws_last_number_lrp.X + text_number_offset_x + text_ws_u_length + text_space_length,
                                                                 ws_last_number_lrp.Y + text_number_height));
    ic::vector2d<s32> altitude_last_number_lrp = this->getLowerRightPoint(this->a_1);
    this->image_altitude_u->setRelativePosition(ic::rect<s32>(altitude_last_number_lrp.X + text_number_offset_x + text_space_length,
                                                               altitude_last_number_lrp.Y ,
                                                               altitude_last_number_lrp.X + text_number_offset_x + text_altitude_u_length + text_space_length,
                                                               altitude_last_number_lrp.Y + text_number_height));
    ic::vector2d<s32> vs_last_number_lrp = this->getLowerRightPoint(this->vs_1);
    this->image_vertical_speed_u->setRelativePosition(ic::rect<s32>(vs_last_number_lrp.X + text_number_offset_x + text_space_length,
                                                                     vs_last_number_lrp.Y ,
                                                                     vs_last_number_lrp.X + text_number_offset_x + text_vs_u_length + text_space_length,
                                                                     vs_last_number_lrp.Y + text_number_height));
    //2D plane
    CGUICompass* compass_plane = new CGUICompass(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width - this->plane_offset_x - this->plane_width,
                                                               this->plane_offset_y,
                                                               this->device->getVideoDriver()->getScreenSize().Width - this->plane_offset_x,
                                                               this->plane_offset_y + this->plane_height), gui, nullptr);

    if(this->plane_red == true)
        compass_plane->setCompassTexture(texture_plane_red);
    else
        compass_plane->setCompassTexture(texture_plane);
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
    //Gauge full
    setGaugeOffset(this->gauge_offset, this->gauge_percentage, this->gauge_width);
    //gauge_offset = 0;
    CGUICompass* compass_gauge_full = new CGUICompass(ic::rect<s32>(this->device->getVideoDriver()->getScreenSize().Width - this->gauge_width - gauge_offset_x + gauge_offset + 4,
                                                                    this->device->getVideoDriver()->getScreenSize().Height - this->gauge_height - gauge_offset_y + 4,
                                                                    this->device->getVideoDriver()->getScreenSize().Width - gauge_offset_x - 4,
                                                                    this->device->getVideoDriver()->getScreenSize().Height - gauge_offset_y -4), this->gui, nullptr);
    if(this->gauge_percentage > 63)
        compass_gauge_full->setCompassTexture(texture_gauge_full_green);
    else if (this->gauge_percentage<63 && this->gauge_percentage>33)
        compass_gauge_full->setCompassTexture(texture_gauge_full_orange);
    else
    compass_gauge_full->setCompassTexture(texture_gauge_full_red);

    // Arrows
    CGUICompass* compass_arrows = new CGUICompass(ic::rect<s32>(10, 10, 85, 85), this->gui, nullptr);
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
        this->plane_red = false;
    }
    else
    {
        sign->setImage(texture_minus);
        if(this->stall == true && this->timer%10==0)
        {
            this->plane_red = !this->plane_red;
        }


        compass_plane->setCompassHeading(-55);


    }

    compasses.push_back(compass_level);
    compasses.push_back(compass_arrows);
    compasses.push_back(compass_plane);
    compasses.push_back(compass_gauge_full);

    // Update timer
    timer++;

    return compasses;
}

