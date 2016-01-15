#include <irrlicht.h>

#include <vector>

//#include "CGUICompass.hpp"


using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

class CGUICompass;
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


    is::ISceneManager *smgr;
    iv::IVideoDriver *driver;
    ig::IGUIEnvironment *gui;
    IrrlichtDevice *device;

    // display values
    int wind_speed;
    int altitude;
    int vertical_speed;
    int gauge_h_offset;
    int gauge_v_offset;
    bool stall;
    int gauge_h_percentage;
    double gauge_v_slope;

    // Window size
    ic::dimension2d<u32> precedent_window_size;

    // Display elements
    // Textures
    iv::ITexture *texture_compass;
    iv::ITexture *texture_level;
    iv::ITexture *texture_wind_speed;
    iv::ITexture *texture_altitude;
    iv::ITexture *texture_vertical_speed;
    iv::ITexture *texture_plane;
    iv::ITexture *texture_plane_red;
    iv::ITexture *numbers[10];
    iv::ITexture *texture_plus;
    iv::ITexture *texture_minus;
    iv::ITexture *texture_wind_speed_u;
    iv::ITexture *texture_altitude_u;
    iv::ITexture *texture_vertical_speed_u;
    iv::ITexture *texture_fuel;
    iv::ITexture *texture_gauge_empty_h;
    iv::ITexture *texture_gauge_full_green_h;
    iv::ITexture *texture_gauge_full_red_h;
    iv::ITexture *texture_gauge_full_orange_h;
    iv::ITexture *texture_gauge_empty_v;
    iv::ITexture *texture_background;

    // Images
    ig::IGUIImage *image_wind_speed;
    ig::IGUIImage *image_altitude;
    ig::IGUIImage *image_vertical_speed;
    ig::IGUIImage *ws_10000;
    ig::IGUIImage *ws_1000;
    ig::IGUIImage *ws_100;
    ig::IGUIImage *ws_10;
    ig::IGUIImage *ws_1;
    ig::IGUIImage *a_10000;
    ig::IGUIImage *a_1000;
    ig::IGUIImage *a_100;
    ig::IGUIImage *a_10;
    ig::IGUIImage *a_1;
    ig::IGUIImage *sign;
    ig::IGUIImage *vs_10000;
    ig::IGUIImage *vs_1000;
    ig::IGUIImage *vs_100;
    ig::IGUIImage *vs_10;
    ig::IGUIImage *vs_1;
    ig::IGUIImage *image_wind_speed_u;
    ig::IGUIImage *image_altitude_u;
    ig::IGUIImage *image_vertical_speed_u;
    ig::IGUIImage *image_background;
    ig::IGUIImage *image_fuel;
    ig::IGUIImage *image_gauge_empty_h;
    ig::IGUIImage *image_gauge_empty_v;

    // Positions
    int compass_length;
    int compass_offset_x;
    int compass_offset_y;
    int background_height;
    int background_width;
    int background_offset_x;
    int background_offset_y;
    int text_offset_x;
    int text_offset_y;
    int text_ws_length;
    int text_ws_u_length;
    int text_ws_height;
    int text_altitude_length;
    int text_altitude_u_length;
    int text_altitude_height;
    int text_vs_length;
    int text_vs_u_length;
    int text_vs_height;
    int text_number_height;
    int text_number_length;
    int text_number_offset_x;
    int text_space_length;
    int plane_offset_x;
    int plane_offset_y;
    int plane_height;
    int plane_width;
    int gauge_v_height;
    int gauge_v_width;
    int gauge_h_height;
    int gauge_h_width;
    int gauge_h_offset_x;
    int gauge_h_offset_y;
    int gauge_v_offset_x;
    int gauge_v_offset_y;
    int fuel_offset_x;
    int fuel_height;
    int fuel_width;

    // Elements blinking
    bool plane_red;

    // Timer
    int timer;


};
