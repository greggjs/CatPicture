/**
 * @file CatPictureApp.cpp
 * This app randomizes the color of the background when it is
 * clicked upon. It will draw a circle that increases in size
 * wherever the mouse currently is, and it will save the circles
 * on a particular background.
 *
 * @author Jake Gregg
 * @date 2012-08-23
 *
 * @note This file is (c) 2012. It is licensed under the
 * CC by 3.0 License, which means you are free to use, share,
 * and remix it as long as you give attribution. Commercial uses
 * are allowed.
 */

/// Include statements

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Particle.h"
#include "ParticleController.h"
#include "cinder/Rand.h"

#define RESOLUTION 5

using namespace ci;
using namespace ci::app;
using namespace std;

/// Define public methods and private variables
class CatPictureApp : public AppBasic {
  public:
    void prepareSettings(Settings *settings);
	void setup();
	void mouseMove( MouseEvent event );	
	void mouseDrag( MouseEvent event );
    void mouseDown( MouseEvent event );
    void mouseWheel( MouseEvent event );
	void update();
	void draw();
    
    Channel32f myChannel_;
    gl::Texture myTexture_;
    
    ParticleController myParticleController_;
    
    bool mDrawParticles_;
    bool mDrawImage_;
    
private:
	Surface mySurface_;
    float rand_;
	Vec2i myMouseLoc_;
};

void CatPictureApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(520, 520);
    settings->setFrameRate(60.0f);
}

/// Sets the initial loop number to 1, initiallizes the random
/// number generator, and initiallizes my random numbers for use
/// in generating the background color.
void CatPictureApp::setup()
{
    myChannel_ = Channel32f(loadImage(loadResource("assassins_creed_3_logo.jpeg")));
    myTexture_ = myChannel_;
    
    myParticleController_ = ParticleController(RESOLUTION);
    
    myMouseLoc_ = Vec2i(0, 0);
    
    mDrawParticles_ = true;
    mDrawImage_ = false;

}

/// When the user moves the mouse, it gets the new mouse position
/// and it draws a new circle there. It will start the loop over.
void CatPictureApp::mouseMove( MouseEvent event )
{

	myMouseLoc_ = event.getPos();
	
}

/// When the user clicks the left click, it will randomize
/// the background color by calling the mouseDown event in
/// the Particle class
void CatPictureApp::mouseDown( MouseEvent event) {
    myParticleController_.changeColor();
}

void CatPictureApp::mouseDrag( MouseEvent event) {
	
    mouseMove(event);
    
}

void CatPictureApp::mouseWheel ( MouseEvent event ) {
    myParticleController_.changeDist(event.getWheelIncrement());
}

/// A continuous loop is running in the background the entire
/// program, and this determines the radius of the drawn circle.
/// if the circle reaches a certain limit, it will stop drawing
/// that particular circle.
void CatPictureApp::update()
{
	
    if (! myChannel_) return;
    
	myParticleController_.update(myChannel_, myMouseLoc_);
    
	
}

/// When the draw method is called, it draws a cirlce with the 
/// current parameters.
void CatPictureApp::draw()
{
    gl::clear (Color(0, 0, 0), true);
    
    if (mDrawImage_ ){
        myTexture_.enableAndBind();
        gl::draw(myTexture_, getWindowBounds());
    }
    if (mDrawParticles_) {
        glDisable(GL_TEXTURE_2D);
        myParticleController_.draw();
    }
	
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
