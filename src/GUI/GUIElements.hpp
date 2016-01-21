#include <irrlicht.h>

#include <vector>

#include "CGUICompass.hpp"
#include "../Event/EventReceiver.hpp"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;


class GUIElements
{
public:
    // Constructor
    GUIElements();
    // Destructor
    ~GUIElements();

    // Initialize 2D elements
    // ! We must have called setDevice first !
    bool initialize2DElements();
    // Update 2D elements
    // ! We must have called setDevice first !
    std::vector<CGUICompass*> update2DElements();

    // Setters and getters
    void setDevice(IrrlichtDevice*);
    void setSpeed(const float speed){     m_speed = speed;    }
    void setAltitude(const float altitude){     m_altitude = altitude;    }
    void setVerticalSpeed(const float verticalSpeed){     m_verticalSpeed = verticalSpeed;    }
    void setStall(const bool stall)
    {
        m_stall = stall;
        if(m_stall == true && m_almostStall == true )
        {
            m_almostStall = false;
        }
        else if (m_stall == false)
        {
            m_planeRed = false;
        }
    }
    void setAlmostStall(const bool almostStall){
        m_almostStall = almostStall;
        if(m_almostStall == true && m_stall == true)
        {
            m_stall = false;
        }
        else if (m_almostStall == false)
        {
            m_planeOrange = false;
        }
    }
    void setGaugeHPercentage(const float gaugeHPercentage){     m_gaugeHPercentage = gaugeHPercentage;    }
    void setGaugeVSlope(const float gaugeVSlope){     m_gaugeVSlope = gaugeVSlope;    }
    void setOrientation(const int orientation){     m_orientation = orientation;    }

private:

    // To compute the horzontal and vertical gaugue offset to fill them
    void computeHorizontalGaugeOffset(int&, int, int);
    void computeVerticalGaugeOffset(int&, double, int);
    // To get the upper left point of an image
    ic::vector2d<s32> getUpperLeftPoint(ig::IGUIImage* image);
    // To get the upper right point of an image
    ic::vector2d<s32> getLowerRightPoint(ig::IGUIImage* image);
    // To update element dimensions when the ow is resized
    void updateDimensions();
    // To update element positions when the window has been resized and the dimensions recomputed
    void updatePositions();


    is::ISceneManager *m_smgr = nullptr;
    iv::IVideoDriver *m_driver = nullptr;
    ig::IGUIEnvironment *m_gui = nullptr;
    IrrlichtDevice *m_device = nullptr;

    // display values
    int m_speed;
    int m_altitude;
    int m_verticalSpeed;
    int m_gaugeHOffset;
    int m_gaugeVOffset;
    bool m_stall;
    bool m_almostStall;
    int m_gaugeHPercentage;
    double m_gaugeVSlope;
    int m_orientation;

    // Window size
    ic::dimension2d<u32> m_precedentWindowSize = ic::dimension2d<u32>(0.0, 0.0);

    // Display elements
    // Textures
    iv::ITexture *m_textureCompass = nullptr;
    iv::ITexture *m_textureLevel = nullptr;
    iv::ITexture *m_textureSpeed = nullptr;
    iv::ITexture *m_textureAltitude = nullptr;
    iv::ITexture *m_textureVerticalSpeed = nullptr;
    iv::ITexture *m_texturePlane = nullptr;
    iv::ITexture *m_texturePlaneOrange = nullptr;
    iv::ITexture *m_texturePlaneRed = nullptr;
    iv::ITexture *m_numbers[10];
    iv::ITexture *m_texturePlus = nullptr;
    iv::ITexture *m_textureMinus = nullptr;
    iv::ITexture *m_textureSpeedU = nullptr;
    iv::ITexture *m_textureAltitudeU = nullptr;
    iv::ITexture *m_textureVerticalSpeedU = nullptr;
    iv::ITexture *m_textureFuel = nullptr;
    iv::ITexture *m_textureGaugeEmptyH = nullptr;
    iv::ITexture *m_textureGaugeFullGreenH = nullptr;
    iv::ITexture *m_textureGaugeFullRedH = nullptr;
    iv::ITexture *m_textureGaugeFullOrangeH = nullptr;
    iv::ITexture *m_textureGaugeEmptyV = nullptr;
    iv::ITexture *m_textureBackground = nullptr;

    // Images
    ig::IGUIImage *m_imageSpeed = nullptr;
    ig::IGUIImage *m_imageAltitude = nullptr;
    ig::IGUIImage *m_imageVerticalSpeed = nullptr;
    ig::IGUIImage *m_s1000 = nullptr;
    ig::IGUIImage *m_s100 = nullptr;
    ig::IGUIImage *m_s10 = nullptr;
    ig::IGUIImage *m_s1 = nullptr;
    ig::IGUIImage *m_a1000 = nullptr;
    ig::IGUIImage *m_a100 = nullptr;
    ig::IGUIImage *m_a10 = nullptr;
    ig::IGUIImage *m_a1 = nullptr;
    ig::IGUIImage *m_sign = nullptr;
    ig::IGUIImage *m_vs1000 = nullptr;
    ig::IGUIImage *m_vs100 = nullptr;
    ig::IGUIImage *m_vs10 = nullptr;
    ig::IGUIImage *m_vs1 = nullptr;
    ig::IGUIImage *m_imageSpeedU = nullptr;
    ig::IGUIImage *m_imageAltitudeU = nullptr;
    ig::IGUIImage *m_imageVerticalSpeedU = nullptr;
    ig::IGUIImage *m_imageBackground = nullptr;
    ig::IGUIImage *m_imageFuel = nullptr;
    ig::IGUIImage *m_imageGaugeEmptyH = nullptr;
    ig::IGUIImage *m_imageGaugeEmptyV = nullptr;

    // Compass
    CGUICompass* m_compassCompass = nullptr;
    CGUICompass* m_compassVGaugeFull = nullptr;
    CGUICompass* m_compassPlane = nullptr;
    CGUICompass* m_compassHGaugeFull = nullptr;

    // Positions
    int m_compassLength;
    int m_compassOffsetX;
    int m_compassOffsetY;
    int m_backgroundHeight;
    int m_backgroundWidth;
    int m_backgroundOffsetX;
    int m_backgroundOffsetY;
    int m_textOffsetX;
    int m_textOffsetY;
    int m_textSpeedLength;
    int m_textSpeedULength;
    int m_textSpeedHeight;
    int m_textAltitudeLength;
    int m_textAltitudeULength;
    int m_textAltitudeHeight;
    int m_textVsLength;
    int m_textVsULength;
    int m_textVsHeight;
    int m_textNumberHeight;
    int m_textNumberLength;
    int m_textNumberOffsetX;
    int m_textSpaceLength;
    int m_planeOffsetX;
    int m_planeOffsetY;
    int m_planeHeight;
    int m_planeWidth;
    int m_gaugeVHeight;
    int m_gaugeVWidth;
    int m_gaugeHHeight;
    int m_gaugeHWidth;
    int m_gaugeHOffsetX;
    int m_gaugeHOffsetY;
    int m_gaugeVOffsetX;
    int m_gaugeVOffsetY;
    int m_fuelOffsetX;
    int m_fuelHeight;
    int m_fuelWidth;

    // Elements blinking
    bool m_planeRed;
    bool m_planeOrange;

    // Timer
    int m_timer;
};
