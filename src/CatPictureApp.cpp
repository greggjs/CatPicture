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
 * 
 * @note This project satisfies the goals A.1 (rectangle), A.2 (circle), 8.1 (blur),
 * E.2 (transparency), E.5 (animation), and E.6 (interaction)
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

/// this constant defines the resolution
/// I am drawing at. That means that each
/// Particle I draw is 5 pixels by 5 pixels.
/// Anything smaller really slows down the
/// frames per second.
#define RESOLUTION 5

using namespace ci;
using namespace ci::app;
using namespace std;

/// Define public methods and private variables
class CatPictureApp : public AppBasic {
  public:
    void prepareSettings(Settings *settings); /// prepare the initial settings
	void setup(); /// setup the app
	void mouseMove( MouseEvent event );	/// handle when the mouse moves
	void mouseDrag( MouseEvent event ); /// handle whne the mouse is dragged
    void mouseDown( MouseEvent event ); /// handle when the mouse is clicked
    void mouseWheel( MouseEvent event ); /// handle when the wheel is moved
	void update(); /// update the settings
	void draw(); // draw the updated settings
    
    Channel32f myChannel_; /// where I maninpulate my imported image
    gl::Texture myTexture_; /// where I store my image
    
    ParticleController myParticleController_; /// where the particles are stored

    /// stores the mouse location
	Vec2i myMouseLoc_;
};

void CatPictureApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(520, 520);
    settings->setFrameRate(60.0f);
}

/// This sets ups the program before everything is drawn
void CatPictureApp::setup()
{
    /// create a new channel to store the image, and create the texture with the
    /// same image
    myChannel_ = Channel32f(loadImage(loadResource(RES_AC)));
    myTexture_ = myChannel_;
    
    /// Create a new ParticleController with the resolution
    /// desired
    myParticleController_ = ParticleController(RESOLUTION);
    
    /// initiallize the mouse location at the origin
    myMouseLoc_ = Vec2i(0, 0);

}

/// When the user moves the mouse, it gets the new mouse position
/// and stores it
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

/// when the mouse is dragged, it calls the same method
/// as when the mouse is clicked. This was done to
/// smooth out the movements of the Particles.
void CatPictureApp::mouseDrag( MouseEvent event) {
	
    mouseMove(event);
    
}

/// This handles when the mouseWheel is scrolled.
/// it sends it first to the ParticleController, then
/// the ParticleController sends it to each Particle
/// to handle on their own.
void CatPictureApp::mouseWheel ( MouseEvent event ) {
    myParticleController_.changeDist(event.getWheelIncrement());
}

/// This function is continuously called and changes the properties
/// of the Particles based on the mouse's location
void CatPictureApp::update()
{
	/// if somehow it's not our channel being called,
    /// don't proceed with the update
    if (! myChannel_) return;
    
	myParticleController_.update(myChannel_, myMouseLoc_);
    
	
}

/// This method draws our ParticleController's Particles
/// after proper updates have been performed.
void CatPictureApp::draw()
{
    gl::clear(Color(0.0f, 0.0f, 0.0f));
    myParticleController_.draw();

	
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
