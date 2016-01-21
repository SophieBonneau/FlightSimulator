#include <irrlicht.h>

#include <vector>

#include "CGUICompass.hpp"
#include "../Event/EventReceiver.hpp"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

/* Class GUIElements: Class which manages the GUI elements displaying
*/
class GUIElements
{
public:

    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor GUIELements: Initialize all global attributes of the class
     * param:   IrrlichtDevice* device: the scene device
    */
    GUIElements(IrrlichtDevice* device);
    ~GUIElements();


    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setSpeed: set the plane speed
     * param:  const float: the plane speed
    */
    void setSpeed(const float speed){     m_speed = speed;    }
    /* void setAltitude: set the plane altitude
     * param:  const float: the plane altitude
    */
    void setAltitude(const float altitude){     m_altitude = altitude;    }
    /* void setVerticalSpeed: set the plane vertical speed
     * param:  const float: the plane vertical speed
    */
    void setVerticalSpeed(const float verticalSpeed){     m_verticalSpeed = verticalSpeed;    }
    /* void setGaugeHPercentage: set the percentage of the fuel gauge (between 0 and 100
     * param:  const float: percentage of fuel gauge
    */
    void setGaugeHPercentage(const float gaugeHPercentage){
        if(gaugeHPercentage >100 || gaugeHPercentage < 0) { std::cout<<"Error, gaugeHPercentage must be between 0 and 100"<<std::endl;}
        m_gaugeHPercentage = gaugeHPercentage;    }
    /* void setGaugeVSlope: set the value between -1 and 1 giving information about the plane vertical slope
     * param:  const float: vertical slope
    */
    void setGaugeVSlope(const float gaugeVSlope){
        if(gaugeVSlope >1 || gaugeVSlope < -1) { std::cout<<"Error, gaugeVSlope must be between -1 and 1"<<std::endl;}
        m_gaugeVSlope = gaugeVSlope;    }
    /* void setOrientation: set plane orientation angle value
     * param:  const float: orientation angle
    */
    void setOrientation(const int orientation){     m_orientation = orientation;    }
    /* void setStall: set the stall state value
     * param:  const float: stall state
    */
    void setStall(const bool stall);
    /* void setStall: set the stall limit state value
     * param:  const float: stall limit state
    */
    void setAlmostStall(const bool almostStall);

    /************************************************************************************/
    /******************************** Public functions *********************************/
    /************************************************************************************/
    /* void initialize2DElements:  Initialization of GUI elements
    */
    void initialize2DElements();

    /* std::vector<CGUICompass*> update2DElements(): update the GUI elements in terms of positioning and scaling
     * and according to the current simulation parameters
    */
    std::vector<CGUICompass*> update2DElements();

private:

    /************************************************************************************/
    /******************************** Private functions *********************************/
    /************************************************************************************/
    /* void computeHorizontalGaugeOffset: Compute the horizontal gaugue offset to fill it
     * */
    void computeHorizontalGaugeOffset(int&, int, int);

    /* void computeVerticalGaugeOffset: Compute the vertical gaugue offset to fill it
     * */
    void computeVerticalGaugeOffset(int&, double, int);

    /* void getUpperLeftPoint: To fetch the upper left point of an image
     * */
    ic::vector2d<s32> getUpperLeftPoint(ig::IGUIImage* image);

    /* void getLowerRightPoint: To fetch the lower right point of an image
     * */
    ic::vector2d<s32> getLowerRightPoint(ig::IGUIImage* image);

    /* void updateDimensions: To update element dimensions according to the window size
     * */
    void updateDimensions();

    /* void updatePositions: To update element positions when the window has been resized and the dimensions recomputed
     * */
    void updatePositions();

    /* void updateNumbersDisplayed: To update the numbers displayed according to the simulation parameters values
     * */
    void updateNumbersDisplayed();


    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/

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

    // To register the precedent windiw size in order to know if the 2D elements need to be rescaled
    ic::dimension2d<u32> m_precedentWindowSize = ic::dimension2d<u32>(0.0, 0.0);

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

    // Blinking elements
    bool m_planeRed;
    bool m_planeOrange;

    // Timer
    int m_timer;
};
