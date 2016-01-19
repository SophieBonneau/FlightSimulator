#include "GUIElements.hpp"


#include <iostream>


GUIElements::GUIElements()
{
    m_smgr = nullptr;
    m_driver = nullptr;
    m_gui = nullptr;
    m_device = nullptr;

    // Display values
    m_speed = 20;
    m_altitude = 1000;
    m_verticalSpeed = -20;
    m_gaugeHOffset = 0;
    m_gaugeVOffset = 0;
    m_stall = false;
    m_almostStall = false;
    m_gaugeHPercentage = 50;
    m_gaugeVSlope = 0.1;
    m_orientation = 0;

    // Positions
    m_compassLength = 55;
    m_compassOffsetX = 10;
    m_compassOffsetY = 10;
    m_backgroundHeight = 80;
    m_backgroundWidth = 350;
    m_backgroundOffsetX = 10;
    m_backgroundOffsetY = 10;
    m_textOffsetX = 10;
    m_textOffsetY = 10;
    m_textSpeedLength = 100;
    m_textSpeedULength = 37;
    m_textSpeedHeight = 15;
    m_textAltitudeLength = 70;
    m_textAltitudeULength = 13;
    m_textAltitudeHeight = 13;
    m_textVsLength = 110;
    m_textVsHeight = 14;
    m_textVsULength = 25;
    m_textNumberHeight = 12;
    m_textNumberLength = 10;
    m_textNumberOffsetX = 1;
    m_textSpaceLength = 8;
    m_planeOffsetX = 20;
    m_planeOffsetY = 20;
    m_planeHeight = 50;
    m_planeWidth = 75;
    m_gaugeVHeight = 25;
    m_gaugeVWidth = 250;
    m_gaugeHOffsetX = 10;
    m_gaugeHOffsetY = 10;
    m_gaugeVOffsetX = 20;
    m_gaugeVOffsetY = 100;
    m_fuelOffsetX = 10;
    m_fuelHeight = 25;
    m_fuelWidth = 24;

    // Window size
    m_precedentWindowSize.Height = 0;
    m_precedentWindowSize.Width = 0;


    // Blinking elements
    m_planeRed = false;
    m_planeOrange = false;

    // Timer
    m_timer = 0;

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
    m_device = device;
    m_smgr = m_device->getSceneManager();
    m_driver = m_device->getVideoDriver();
    m_gui = m_device->getGUIEnvironment();
}


void GUIElements::updateDimensions()
{
    ic::dimension2d<u32> windowDimension = m_device->getVideoDriver()->getScreenSize();
    // Background
    m_backgroundHeight = windowDimension.Height*0.15;
    m_backgroundWidth = windowDimension.Width*0.4;

    // Fuel
    m_fuelHeight = m_gaugeHHeight;
    m_fuelWidth = m_fuelHeight;

    // Text
    m_textOffsetY = m_backgroundHeight*0.15;

    // Speed text
    m_textSpeedLength = m_backgroundWidth*0.45;
    m_textSpeedHeight = m_backgroundHeight*0.21;

    // Altitude text
    m_textAltitudeLength = m_backgroundWidth*0.35;
    m_textAltitudeHeight = m_backgroundHeight*0.194;

    // Vertical speed text
    m_textVsLength = m_backgroundWidth*0.47;
    m_textVsHeight = m_backgroundHeight*0.21;

    // Numbers
    m_textNumberLength = m_backgroundWidth*0.043;
    m_textNumberHeight = m_backgroundHeight*0.17;

    // Speed unity text
    m_textSpeedULength = windowDimension.Width*0.060;
    // Altitude unity text
    m_textAltitudeULength = windowDimension.Width*0.023;
    // Vertical speed unity text
    m_textVsULength = m_backgroundWidth*0.13;

    // Vertical gauge
    m_gaugeVOffsetY = windowDimension.Height*0.2;
    m_gaugeVHeight = windowDimension.Height*0.4;
    m_gaugeVWidth = windowDimension.Width*0.05;

    // Horizontal gauge
    m_gaugeHHeight = windowDimension.Height*0.05;
    m_gaugeHWidth = windowDimension.Width*0.45;

    // Compass
    m_compassLength = windowDimension.Height*0.13;

    // 2D plane
    m_planeHeight = windowDimension.Height*0.10;
    m_planeWidth = windowDimension.Width*0.12;
}

void GUIElements::updatePositions()
{
    // Background
    m_imageBackground->setRelativePosition(ic::rect<s32>(m_backgroundOffsetX,
                                                              m_device->getVideoDriver()->getScreenSize().Height -m_backgroundOffsetY - m_backgroundHeight,
                                                              m_backgroundOffsetX + m_backgroundWidth,
                                                              m_device->getVideoDriver()->getScreenSize().Height -m_backgroundOffsetY));
    // Fuel
    ic::vector2d<s32> gaugeUlp = getUpperLeftPoint(m_imageGaugeEmptyH);
    m_imageFuel->setRelativePosition(ic::rect<s32>(gaugeUlp.X - m_fuelWidth - m_fuelOffsetX,
                                                                     gaugeUlp.Y,
                                                                     gaugeUlp.X - m_fuelOffsetX,
                                                                     gaugeUlp.Y + m_fuelHeight));
    //Speed text
    ic::vector2d<s32> backgroundUlp = getUpperLeftPoint(m_imageBackground);
    m_imageSpeed->setRelativePosition(ic::rect<s32>(backgroundUlp.X + m_textOffsetX,
                                                                   backgroundUlp.Y + m_textOffsetY,
                                                                   backgroundUlp.X + m_textOffsetX + m_textSpeedLength,
                                                                   backgroundUlp.Y + m_textOffsetY + m_textSpeedHeight));
    //Altitude text
    m_imageAltitude->setRelativePosition(ic::rect<s32>(backgroundUlp.X + m_textOffsetX,
                                                                 backgroundUlp.Y + 3*m_textOffsetY,
                                                                 backgroundUlp.X + m_textOffsetX + m_textAltitudeLength,
                                                                 backgroundUlp.Y + 3*m_textOffsetY + m_textAltitudeHeight));
    // Vertical speed text
    m_imageVerticalSpeed->setRelativePosition(ic::rect<s32>(backgroundUlp.X + m_textOffsetX,
                                                                       backgroundUlp.Y + 5*m_textOffsetY,
                                                                       backgroundUlp.X + m_textOffsetX + m_textVsLength,
                                                                       backgroundUlp.Y + 5*m_textOffsetY + m_textVsHeight));
    // Numbers
    ic::vector2d<s32> wsLrp = getLowerRightPoint(m_imageSpeed);
    m_s1000->setRelativePosition(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                               wsLrp.Y +1,
                                               wsLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                               wsLrp.Y + m_textNumberHeight +1));
    m_s100->setRelativePosition(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                              wsLrp.Y +1,
                                              wsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + m_textSpaceLength,
                                              wsLrp.Y + m_textNumberHeight +1));
    m_s10->setRelativePosition(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y +1,
                                             wsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y + m_textNumberHeight +1));
    m_s1->setRelativePosition(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + m_textSpaceLength,
                                            wsLrp.Y +1,
                                            wsLrp.X + m_textNumberOffsetX + 4*m_textNumberLength + m_textSpaceLength,
                                            wsLrp.Y + m_textNumberHeight +1));
    ic::vector2d<s32> altitudeLrp = getLowerRightPoint(m_imageAltitude);
    m_a1000->setRelativePosition(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                               altitudeLrp.Y +1,
                                               altitudeLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                               altitudeLrp.Y + m_textNumberHeight +1));
    m_a100->setRelativePosition(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                              altitudeLrp.Y +1,
                                              altitudeLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + m_textSpaceLength,
                                              altitudeLrp.Y + m_textNumberHeight +1));
    m_a10->setRelativePosition(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + m_textSpaceLength,
                                             altitudeLrp.Y +1,
                                             altitudeLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + m_textSpaceLength,
                                             altitudeLrp.Y + m_textNumberHeight +1));
    m_a1->setRelativePosition(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + m_textSpaceLength,
                                            altitudeLrp.Y +1,
                                            altitudeLrp.X + m_textNumberOffsetX + 4*m_textNumberLength + m_textSpaceLength,
                                            altitudeLrp.Y + m_textNumberHeight +1));
    ic::vector2d<s32> vsLrp = getLowerRightPoint(m_imageVerticalSpeed);
    m_sign->setRelativePosition(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                   vsLrp.Y +1,
                                                   vsLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                                   vsLrp.Y + m_textNumberHeight +1));
    m_vs1000->setRelativePosition(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y +1,
                                                vsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y + m_textNumberHeight +1));
    m_vs100->setRelativePosition(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y +1,
                                                vsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y + m_textNumberHeight +1));
    m_vs10->setRelativePosition(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y +1,
                                                vsLrp.X + m_textNumberOffsetX + 4*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y + m_textNumberHeight +1));
    m_vs1->setRelativePosition(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + 4*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y +1,
                                                vsLrp.X + m_textNumberOffsetX + 5*m_textNumberLength + 3*m_textSpaceLength/2,
                                                vsLrp.Y + m_textNumberHeight +1));
    // Unities
    ic::vector2d<s32> wsLastNumberLrp = getLowerRightPoint(m_s1);
    m_imageSpeedU->setRelativePosition(ic::rect<s32>(wsLastNumberLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                                 wsLastNumberLrp.Y ,
                                                                 wsLastNumberLrp.X + m_textNumberOffsetX + m_textSpeedULength + m_textSpaceLength,
                                                                 wsLastNumberLrp.Y + m_textNumberHeight));
    ic::vector2d<s32> altitudeLastNumberLrp = getLowerRightPoint(m_a1);
    m_imageAltitudeU->setRelativePosition(ic::rect<s32>(altitudeLastNumberLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                               altitudeLastNumberLrp.Y +1,
                                                               altitudeLastNumberLrp.X + m_textNumberOffsetX + m_textAltitudeULength + m_textSpaceLength,
                                                               altitudeLastNumberLrp.Y + m_textNumberHeight -1));
    ic::vector2d<s32> vsLastNumberLrp = getLowerRightPoint(m_vs1);
    m_imageVerticalSpeedU->setRelativePosition(ic::rect<s32>(vsLastNumberLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                                     vsLastNumberLrp.Y ,
                                                                     vsLastNumberLrp.X + m_textNumberOffsetX + m_textVsULength + m_textSpaceLength,
                                                                     vsLastNumberLrp.Y + m_textNumberHeight));

    // Compass
    m_compassCompass->setCompassRelativePosition(ic::rect<s32>(m_compassOffsetX, m_compassOffsetY,
                                                            m_compassOffsetX + m_compassLength, m_compassOffsetY + m_compassLength));

    // 2D plane
    m_compassPlane->setCompassRelativePosition(ic::rect<s32>(m_device->getVideoDriver()->getScreenSize().Width - m_planeOffsetX - m_planeWidth,
                                                              m_planeOffsetY,
                                                              m_device->getVideoDriver()->getScreenSize().Width - m_planeOffsetX,
                                                              m_planeOffsetY + m_planeHeight));
    // Horizontal gauge full
    computeHorizontalGaugeOffset(m_gaugeHOffset, m_gaugeHPercentage, m_gaugeHWidth);
    m_compassHGaugeFull->setCompassRelativePosition(ic::rect<s32>(m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHWidth - m_gaugeHOffsetX + m_gaugeHOffset + 4,
                                                                    m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHHeight - m_gaugeHOffsetY + 4,
                                                                    m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHOffsetX - 4,
                                                                    m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHOffsetY -4));

    // Vertical gauge full
    computeVerticalGaugeOffset(m_gaugeVOffset, m_gaugeVSlope, m_gaugeVHeight);
    int y1 = m_gaugeVOffsetY + m_gaugeVHeight/2;
    int y2 = m_gaugeVOffsetY + m_gaugeVHeight/2 - 4 + m_gaugeVOffset;
    if(y1 > y2)
    {
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
        y1 += m_gaugeVHeight/20;
    }
    m_compassVGaugeFull->setCompassRelativePosition(ic::rect<s32>(m_gaugeVOffsetX + m_gaugeVWidth/4,
                                                                     y1,
                                                                     m_gaugeVOffsetX + m_gaugeVWidth - m_gaugeVWidth/4,
                                                                     y2));

    // Horizontal gauge empty
    m_imageGaugeEmptyH->setRelativePosition(ic::rect<s32>(m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHWidth - m_gaugeHOffsetX,
                                                                     m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHHeight - m_gaugeHOffsetY,
                                                                     m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHOffsetX,
                                                                     m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHOffsetY));
    // Vertical gauge empty
    m_imageGaugeEmptyV->setRelativePosition(ic::rect<s32>(m_gaugeVOffsetX,
                                                                     m_gaugeVOffsetY,
                                                                     m_gaugeVOffsetX + m_gaugeVWidth,
                                                                     m_gaugeVOffsetY + m_gaugeVHeight));

}

bool GUIElements::initialize2DElements()
{
    if(m_device == nullptr || m_driver == nullptr || m_gui == nullptr || m_smgr == nullptr)
    {
        std::cout<<"Error: you must have set the device" <<
                   "to GUIElements before calling intialize2DElements"<<std::endl;
        return false;
    }

    // Background
    m_textureBackground = m_driver->getTexture("data/2d/background.png");
    m_imageBackground = m_gui->addImage(ic::rect<s32>(m_backgroundOffsetX,
                                                               m_device->getVideoDriver()->getScreenSize().Height -m_backgroundOffsetY - m_backgroundHeight,
                                                               m_backgroundOffsetX + m_backgroundWidth,
                                                               m_device->getVideoDriver()->getScreenSize().Height -m_backgroundOffsetY));
    m_imageBackground->setImage(m_textureBackground);
    m_imageBackground->setScaleImage(true);
    // Compass
    m_textureCompass = m_driver->getTexture("data/2d/compass.png");
    // Level and arrows textures
    m_textureLevel = m_driver->getTexture("data/2d/level.png");
    // Speed
    m_textureSpeed = m_driver->getTexture("data/2d/speed.png");

    ic::vector2d<s32> backgroundUlp = getUpperLeftPoint(m_imageBackground);
    m_imageSpeed = m_gui->addImage(ic::rect<s32>(backgroundUlp.X + m_textOffsetX,
                                                               backgroundUlp.Y + m_textOffsetY,
                                                               backgroundUlp.X + m_textOffsetX + m_textSpeedLength,
                                                               backgroundUlp.Y + m_textOffsetY + m_textSpeedHeight));
    m_imageSpeed->setImage(m_textureSpeed);
    m_imageSpeed->setScaleImage(true);
    // Altitude
    m_textureAltitude = m_driver->getTexture("data/2d/altitude.png");
    m_imageAltitude = m_gui->addImage(ic::rect<s32>(backgroundUlp.X + m_textOffsetX,
                                                             backgroundUlp.Y + 3*m_textOffsetY,
                                                             backgroundUlp.X + m_textOffsetX + m_textAltitudeLength,
                                                             backgroundUlp.Y + 3*m_textOffsetY + m_textAltitudeHeight));
    m_imageAltitude->setImage(m_textureAltitude);
    m_imageAltitude->setScaleImage(true);
    // Vertical speed
    m_textureVerticalSpeed = m_driver->getTexture("data/2d/vertical-speed.png");
    m_imageVerticalSpeed = m_gui->addImage(ic::rect<s32>(backgroundUlp.X + m_textOffsetX,
                                                                   backgroundUlp.Y + 5*m_textOffsetY,
                                                                   backgroundUlp.X + m_textOffsetX + m_textVsLength,
                                                                   backgroundUlp.Y + 5*m_textOffsetY + m_textVsHeight));
    m_imageVerticalSpeed->setImage(m_textureVerticalSpeed);
    m_imageVerticalSpeed->setScaleImage(true);
    // Up/down plane
    m_texturePlane = m_driver->getTexture("data/2d/plane-up.png");
    // Red plane
    m_texturePlaneRed = m_driver->getTexture("data/2d/plane-up-red.png");
    // Orange plane
    m_texturePlaneOrange = m_driver->getTexture("data/2d/plane-up-orange.png");
    //Numbers
    m_numbers[0] = m_driver->getTexture("data/2d/numbers/0.png");
    m_numbers[1] = m_driver->getTexture("data/2d/numbers/1.png");
    m_numbers[2] = m_driver->getTexture("data/2d/numbers/2.png");
    m_numbers[3] = m_driver->getTexture("data/2d/numbers/3.png");
    m_numbers[4] = m_driver->getTexture("data/2d/numbers/4.png");
    m_numbers[5] = m_driver->getTexture("data/2d/numbers/5.png");
    m_numbers[6] = m_driver->getTexture("data/2d/numbers/6.png");
    m_numbers[7] = m_driver->getTexture("data/2d/numbers/7.png");
    m_numbers[8] = m_driver->getTexture("data/2d/numbers/8.png");
    m_numbers[9] = m_driver->getTexture("data/2d/numbers/9.png");
    // Places for the speed
    ic::vector2d<s32> wsLrp = getLowerRightPoint(m_imageSpeed);
    m_s1000  = m_gui->addImage(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                             wsLrp.Y ,
                                             wsLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y + m_textNumberHeight)); m_s1000->setScaleImage(true);
    m_s100   = m_gui->addImage(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y ,
                                             wsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y + m_textNumberHeight)); m_s100->setScaleImage(true);
    m_s10    = m_gui->addImage(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y ,
                                             wsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y + m_textNumberHeight)); m_s10->setScaleImage(true);
    m_s1     = m_gui->addImage(ic::rect<s32>(wsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y ,
                                             wsLrp.X + m_textNumberOffsetX + 4*m_textNumberLength + m_textSpaceLength,
                                             wsLrp.Y + m_textNumberHeight)); m_s1->setScaleImage(true);
    // Places for the altitude
    ic::vector2d<s32> altitudeLrp = getLowerRightPoint(m_imageAltitude);
    m_a1000  = m_gui->addImage(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX,
                                             altitudeLrp.Y ,
                                             altitudeLrp.X + m_textNumberOffsetX + m_textNumberLength,
                                             altitudeLrp.Y + m_textNumberHeight)); m_a1000->setScaleImage(true);
    m_a100   = m_gui->addImage(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + m_textNumberLength,
                                             altitudeLrp.Y ,
                                             altitudeLrp.X + m_textNumberOffsetX + 2*m_textNumberLength,
                                             altitudeLrp.Y + m_textNumberHeight)); m_a100->setScaleImage(true);
    m_a10    = m_gui->addImage(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + 2*m_textNumberLength,
                                             altitudeLrp.Y ,
                                             altitudeLrp.X + m_textNumberOffsetX + 3*m_textNumberLength,
                                             altitudeLrp.Y + m_textNumberHeight)); m_a10->setScaleImage(true);
    m_a1     = m_gui->addImage(ic::rect<s32>(altitudeLrp.X + m_textNumberOffsetX + 3*m_textNumberLength,
                                             altitudeLrp.Y ,
                                             altitudeLrp.X + m_textNumberOffsetX + 4*m_textNumberLength,
                                             altitudeLrp.Y + m_textNumberHeight)); m_a1->setScaleImage(true);
    // Places for vertical speed
    ic::vector2d<s32> vsLrp = getLowerRightPoint(m_imageVerticalSpeed);
    m_sign = m_gui->addImage(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX,
                                                   vsLrp.Y ,
                                                   vsLrp.X + m_textNumberOffsetX + m_textNumberLength,
                                                   vsLrp.Y + m_textNumberHeight)); m_sign->setScaleImage(true);
    m_texturePlus = m_driver->getTexture("data/2d/+.png");
    m_textureMinus = m_driver->getTexture("data/2d/-.png");
    m_sign->setImage(m_texturePlus);
    m_vs1000  = m_gui->addImage(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + m_textNumberLength,
                                              vsLrp.Y ,
                                              vsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength,
                                              vsLrp.Y + m_textNumberHeight)); m_vs1000->setScaleImage(true);
    m_vs100   = m_gui->addImage(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + 2*m_textNumberLength,
                                              vsLrp.Y ,
                                              vsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength,
                                              vsLrp.Y + m_textNumberHeight)); m_vs100->setScaleImage(true);
    m_vs10    = m_gui->addImage(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + 3*m_textNumberLength,
                                              vsLrp.Y ,
                                              vsLrp.X + m_textNumberOffsetX + 4*m_textNumberLength,
                                              vsLrp.Y + m_textNumberHeight)); m_vs10->setScaleImage(true);
    m_vs1     = m_gui->addImage(ic::rect<s32>(vsLrp.X + m_textNumberOffsetX + 4*m_textNumberLength,
                                              vsLrp.Y ,
                                              vsLrp.X + m_textNumberOffsetX + 5*m_textNumberLength,
                                              vsLrp.Y + m_textNumberHeight)); m_vs1->setScaleImage(true);
    // Speed unity
    ic::vector2d<s32> wsLastNumberLrp = getLowerRightPoint(m_s1);
    m_textureSpeedU = m_driver->getTexture("data/2d/kmh.png");
    m_imageSpeedU = m_gui->addImage(ic::rect<s32>(wsLastNumberLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                                 wsLastNumberLrp.Y ,
                                                                 wsLastNumberLrp.X + m_textNumberOffsetX + m_textSpeedULength + m_textSpaceLength,
                                                                 wsLastNumberLrp.Y + m_textNumberHeight));
    m_imageSpeedU->setImage(m_textureSpeedU);
    m_imageSpeedU->setScaleImage(true);
    // Altitude unity
    ic::vector2d<s32> altitudeLastNumberLrp = getLowerRightPoint(m_a1);
    m_textureAltitudeU = m_driver->getTexture("data/2d/m.png");
    m_imageAltitudeU = m_gui->addImage(ic::rect<s32>(altitudeLastNumberLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                               altitudeLastNumberLrp.Y ,
                                                               altitudeLastNumberLrp.X + m_textNumberOffsetX + m_textAltitudeULength + m_textSpaceLength,
                                                               altitudeLastNumberLrp.Y + m_textNumberHeight));
    m_imageAltitudeU->setImage(m_textureAltitudeU);
    m_imageAltitudeU->setScaleImage(true);
    // Vertical speed unity
    m_textureVerticalSpeedU = m_driver->getTexture("data/2d/ms.png");
    ic::vector2d<s32> vsLastNumberLrp = getLowerRightPoint(m_vs1);
    m_imageVerticalSpeedU = m_gui->addImage(ic::rect<s32>(vsLastNumberLrp.X + m_textNumberOffsetX + m_textSpaceLength,
                                                                     vsLastNumberLrp.Y ,
                                                                     vsLastNumberLrp.X + m_textNumberOffsetX + m_textVsULength + m_textSpaceLength,
                                                                     vsLastNumberLrp.Y + m_textNumberHeight));
    m_imageVerticalSpeedU->setImage(m_textureVerticalSpeedU);
    m_imageVerticalSpeedU->setScaleImage(true);
    // Gauge textures
    m_textureGaugeEmptyH = m_driver->getTexture("data/2d/gauge-empty.png");
    m_textureGaugeFullRedH = m_driver->getTexture("data/2d/gauge-full-red.png");
    m_textureGaugeFullGreenH = m_driver->getTexture("data/2d/gauge-full-green.png");
    m_textureGaugeFullOrangeH = m_driver->getTexture("data/2d/gauge-full-orange.png");
    m_textureGaugeEmptyV = m_driver->getTexture("data/2d/gauge-empty-vertical.png");
    // Gauge empty horizontal
    m_imageGaugeEmptyH= m_gui->addImage(ic::rect<s32>(m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHWidth - m_gaugeHOffsetX,
                                                                     m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHHeight - m_gaugeHOffsetY,
                                                                     m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHOffsetX,
                                                                     m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHOffsetY));
    m_imageGaugeEmptyH->setImage(m_textureGaugeEmptyH);
    m_imageGaugeEmptyH->setScaleImage(true);
    // Gauge empty vertical
    m_imageGaugeEmptyV= m_gui->addImage(ic::rect<s32>(m_gaugeVOffsetX,
                                                                     m_gaugeVOffsetY,
                                                                     m_gaugeVOffsetX + m_gaugeVHeight,
                                                                     m_gaugeVOffsetY + m_gaugeVWidth));
    m_imageGaugeEmptyV->setImage(m_textureGaugeEmptyV);
    m_imageGaugeEmptyV->setScaleImage(true);

    // Fuel
    m_textureFuel = m_driver->getTexture("data/2d/fuel.png");
    ic::vector2d<s32> gaugeUlp = getUpperLeftPoint(m_imageGaugeEmptyH);
    m_imageFuel = m_gui->addImage(ic::rect<s32>(gaugeUlp.X - m_fuelWidth - m_fuelOffsetX,
                                                                     gaugeUlp.Y,
                                                                     gaugeUlp.X - m_fuelOffsetX,
                                                                     gaugeUlp.Y + m_fuelHeight));
    m_imageFuel->setImage(m_textureFuel);
    m_imageFuel->setScaleImage(true);

    // Compasses
    // Compass
    m_compassCompass = new CGUICompass(ic::rect<s32>(m_compassOffsetX, m_compassOffsetY,
                                                            m_compassOffsetX + m_compassLength, m_compassOffsetY + m_compassLength), m_gui, nullptr);
    m_compassCompass->setCompassTexture(m_textureCompass);

    // 2D plane
    m_compassPlane = new CGUICompass(ic::rect<s32>(m_device->getVideoDriver()->getScreenSize().Width - m_planeOffsetX - m_planeWidth,
                                                               m_planeOffsetY,
                                                               m_device->getVideoDriver()->getScreenSize().Width - m_planeOffsetX,
                                                               m_planeOffsetY + m_planeHeight), m_gui, nullptr);
    m_compassPlane->setCompassTexture(m_texturePlaneRed);
    // Vertical full gauge
    int y1 = m_gaugeVOffsetY + m_gaugeVHeight/2;
    int y2 = m_gaugeVOffsetY + m_gaugeVHeight/2 - 4 + m_gaugeVOffset;
    if(y1 > y2)
    {
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
        y1 += m_gaugeVHeight/20;
    }
    m_compassVGaugeFull = new CGUICompass(ic::rect<s32>(m_gaugeVOffsetX + m_gaugeVWidth/4,
                                                                      y1,
                                                                      m_gaugeVOffsetX + m_gaugeVWidth - m_gaugeVWidth/4,
                                                                      y2), m_gui, nullptr);


    computeHorizontalGaugeOffset(m_gaugeHOffset, m_gaugeHPercentage, m_gaugeHWidth);
    m_compassHGaugeFull = new CGUICompass(ic::rect<s32>(m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHWidth - m_gaugeHOffsetX + m_gaugeHOffset + 4,
                                                                    m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHHeight - m_gaugeHOffsetY + 4,
                                                                    m_device->getVideoDriver()->getScreenSize().Width - m_gaugeHOffsetX - 4,
                                                                    m_device->getVideoDriver()->getScreenSize().Height - m_gaugeHOffsetY -4), m_gui, nullptr);


    // Adapt elements dimensions and positions to the initial window dimensions
    updateDimensions();
    updatePositions();

    return true;
}

void GUIElements::computeHorizontalGaugeOffset(int& gaugeOffset, int percentage, int gaugeWidth)
{
    if(percentage < 0 || percentage > 100)
    {
        std::cout<<"Error, the slope must be between -1 and 1."<<std::endl;
    }
    else
    {
        double div = (gaugeWidth-4)*percentage/100;
        gaugeOffset = (gaugeWidth-4) - int(div);
        if(gaugeOffset == 0)
            gaugeOffset = -1;
    }
}

void GUIElements::computeVerticalGaugeOffset(int& gaugeOffset, double slope, int gaugeHeight)
{
    if(slope < -1 || slope > 1)
    {
        std::cout<<"Error, the  must be between 0 and 100."<<std::endl;
    }
    else
    {
        gaugeOffset = -int(slope*gaugeHeight/2);
        if (gaugeOffset == 0)
        {
            gaugeOffset = -2;
        }
    }
}

std::vector<CGUICompass*> GUIElements::update2DElements()
{
    std::vector<CGUICompass*> compasses;
    if(m_device == nullptr || m_driver == nullptr || m_gui == nullptr || m_smgr == nullptr)
    {
        std::cout<<"Error: you must have set the device" <<
                   " to GUIElements before calling intialize2DElements"<<std::endl;
        return compasses;
    }

    updateDimensions();
    updatePositions();


    // Update the compass orientation
    std::cout<<"Orientation = "<< m_orientation <<std::endl;
    m_compassCompass->setCompassHeading(m_orientation);

    // Update 2D plane texture
    if(m_planeRed == true)
        m_compassPlane->setCompassTexture(m_texturePlaneRed);
    else if(m_planeOrange == true)
        m_compassPlane->setCompassTexture(m_texturePlaneOrange);
    else
        m_compassPlane->setCompassTexture(m_texturePlane);

    // Adapt the rendering if the plane is going up or down
    if(m_verticalSpeed <0)
    {
        m_compassPlane->setCompassHeading(-55);
        m_sign->setImage(m_textureMinus);
    }
    else
    {
        m_sign->setImage(m_texturePlus);
        m_compassPlane->setCompassHeading(0);
        m_planeRed = false;
    }


    // Update the fuel gauge color according to its level
    if(m_gaugeHPercentage > 63)
        m_compassHGaugeFull->setCompassTexture(m_textureGaugeFullGreenH);
    else if (m_gaugeHPercentage<63 && m_gaugeHPercentage>33)
        m_compassHGaugeFull->setCompassTexture(m_textureGaugeFullOrangeH);
    else
    m_compassHGaugeFull->setCompassTexture(m_textureGaugeFullRedH);

    if(m_gaugeVSlope > 0)
        m_compassVGaugeFull->setCompassTexture(m_textureGaugeFullGreenH);
    else
        m_compassVGaugeFull->setCompassTexture(m_textureGaugeFullRedH);

    // Speed number update
    m_s1000->setImage(m_numbers[(m_speed / 1000) % 10]);
    m_s100->setImage(m_numbers[(m_speed / 100) % 10]);
    m_s10->setImage(m_numbers[(m_speed / 10) % 10]);
    m_s1->setImage(m_numbers[(m_speed / 1) % 10]);
    // altitude number update
    m_a1000->setImage(m_numbers[(m_altitude / 1000) % 10]);
    m_a100->setImage(m_numbers[(m_altitude / 100) % 10]);
    m_a10->setImage(m_numbers[(m_altitude / 10) % 10]);
    m_a1->setImage(m_numbers[(m_altitude / 1) % 10]);
    // vertical speed number updateqqqqqqqqqqqqqqq
    m_vs1000->setImage(m_numbers[(abs(m_verticalSpeed) / 1000) % 10]);
    m_vs100->setImage(m_numbers[(abs(m_verticalSpeed) / 100) % 10]);
    m_vs10->setImage(m_numbers[(abs(m_verticalSpeed) / 10) % 10]);
    m_vs1->setImage(m_numbers[(abs(m_verticalSpeed) / 1) % 10]);

    // Update blinking elements
    if(m_stall == true && m_timer%20==0)
    {
        m_planeRed = !m_planeRed;
    }
    if(m_almostStall == true && m_timer%20==0)
    {
        m_planeOrange = !m_planeOrange;
    }

    // return compasses to render them
    //compasses.push_back(compassLevel);
    compasses.push_back(m_compassCompass);
    compasses.push_back(m_compassPlane);
    compasses.push_back(m_compassVGaugeFull);
    compasses.push_back(m_compassHGaugeFull);

    // Update window size
    m_precedentWindowSize = m_device->getVideoDriver()->getScreenSize();

    // Update timer
    m_timer++;

    return compasses;
}

