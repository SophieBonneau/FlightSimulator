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

    // Setters and getters
    void setDevice(IrrlichtDevice*);
    void setStall(const bool&);

    // Initialize 2D elements
    // ! We must have called setDevice first !
    bool initialize2DElements();
    // Update 2D elements
    // ! We must have called setDevice first !
    std::vector<CGUICompass*> update2DElements();

private:

    // To compute the horzontal and vertical gaugue offset to fill them
    void computeHorizontalGaugeOffset(int&, int, int);
    void computeVerticalGaugeOffset(int&, double, int);
    // To get the upper left point of an image
    ic::vector2d<s32> getUpperLeftPoint(ig::IGUIImage* image);
    // To get the upper right point of an image
    ic::vector2d<s32> getLowerRightPoint(ig::IGUIImage* image);
    // To update element dimensions when the window is resized
    void updateDimensions();
    // To update element positions when the window has been resized and the dimensions recomputed
    void updatePositions();


    is::ISceneManager *m_smgr;
    iv::IVideoDriver *m_driver;
    ig::IGUIEnvironment *m_gui;
    IrrlichtDevice *m_device;

    // display values
    int m_windSpeed;
    int m_altitude;
    int m_verticalSpeed;
    int m_gaugeHOffset;
    int m_gaugeVOffset;
    bool m_stall;
    int m_gaugeHPercentage;
    double m_gaugeVSlope;

    // Window size
    ic::dimension2d<u32> m_precedentWindowSize;

    // Display elements
    // Textures
    iv::ITexture *m_textureCompass;
    iv::ITexture *m_textureLevel;
    iv::ITexture *m_textureWindSpeed;
    iv::ITexture *m_textureAltitude;
    iv::ITexture *m_textureVerticalSpeed;
    iv::ITexture *m_texturePlane;
    iv::ITexture *m_texturePlaneRed;
    iv::ITexture *m_numbers[10];
    iv::ITexture *m_texturePlus;
    iv::ITexture *m_textureMinus;
    iv::ITexture *m_textureWindSpeedU;
    iv::ITexture *m_textureAltitudeU;
    iv::ITexture *m_textureVerticalSpeedU;
    iv::ITexture *m_textureFuel;
    iv::ITexture *m_textureGaugeEmptyH;
    iv::ITexture *m_textureGaugeFullGreenH;
    iv::ITexture *m_textureGaugeFullRedH;
    iv::ITexture *m_textureGaugeFullOrangeH;
    iv::ITexture *m_textureGaugeEmptyV;
    iv::ITexture *m_textureBackground;

    // Images
    ig::IGUIImage *m_imageWindSpeed;
    ig::IGUIImage *m_imageAltitude;
    ig::IGUIImage *m_imageVerticalSpeed;
    ig::IGUIImage *m_ws10000;
    ig::IGUIImage *m_ws1000;
    ig::IGUIImage *m_ws100;
    ig::IGUIImage *m_ws10;
    ig::IGUIImage *m_ws1;
    ig::IGUIImage *m_a10000;
    ig::IGUIImage *m_a1000;
    ig::IGUIImage *m_a100;
    ig::IGUIImage *m_a10;
    ig::IGUIImage *m_a1;
    ig::IGUIImage *m_sign;
    ig::IGUIImage *m_vs10000;
    ig::IGUIImage *m_vs1000;
    ig::IGUIImage *m_vs100;
    ig::IGUIImage *m_vs10;
    ig::IGUIImage *m_vs1;
    ig::IGUIImage *m_imageWindSpeedU;
    ig::IGUIImage *m_imageAltitudeU;
    ig::IGUIImage *m_imageVerticalSpeedU;
    ig::IGUIImage *m_imageBackground;
    ig::IGUIImage *m_imageFuel;
    ig::IGUIImage *m_imageGaugeEmptyH;
    ig::IGUIImage *m_imageGaugeEmptyV;

    // Compass
    CGUICompass* m_compassCompass;
    CGUICompass* m_compassVGaugeFull;
    CGUICompass* m_compassPlane;
    CGUICompass* m_compassHGaugeFull;

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
    int m_textWsLength;
    int m_textWsULength;
    int m_textWsHeight;
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

    // Timer
    int m_timer;
};
