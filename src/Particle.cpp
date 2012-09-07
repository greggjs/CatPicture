//
//  Particle.cpp
//  CatPicture
//
//  This class dictates the actions taken place by the particle
//  shapes created in my program. It sets up the particle initially,
//  updates it properties, and is the end system for MouseEvent
//  actions.
//
//  This file is (c) 2012. It is licensed under the
//  CC by 3.0 License, which means you are free to use, share,
//  and remix it as long as you give attribution. Commercial uses
//  are allowed.
//
//  Created by Jake Gregg on 9/4/12.
//
//

#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Color.h"

using namespace ci;

/// Default constructor
Particle::Particle()
{
}

/// Constructs a new Particle with a location, direction, and radius.
/// the Direction relative to the cursor is initiallize at 0. The color
/// will always start out as a shade of red. A random is generated and
/// the initial distance change is set.
Particle::Particle( Vec2f location_ )
{
	myLocation_	= location_;
	myDirection_	= Rand::randVec2f();
    myDirToCursor_ = Vec2i::zero();
	myRadius_	= 0.0f;
    rand_ = randFloat(0.0f, 1.0f);
    myDistChange_ = .05f;
	redLevel_ = 1.0f;
	greenLevel_ = 1.0f;
	blueLevel_ = 1.0f;
	change_ = 0;
	myColor_ = Color(redLevel_, greenLevel_, blueLevel_);
    
}

/// This update method takes a float channel, which is our image, and
/// the current mouse location. It then takes this data, based on the
/// amount of time that has elapsed, and will store the new properties
/// of the the Particle for drawing
void Particle::update( const Channel32f &channel, const Vec2i &mouseLoc)
{
	/// calculates the direction to the cursor, and finds
    /// the distance to it,
    myDirToCursor_ = mouseLoc - myLocation_;
    float dist_To_Cursor_ = myDirToCursor_.length();
    
    /// with the time and distance change factored in,
    /// we can generate our sine function offset and
    /// apply it to the particle.
    float time_ = app::getElapsedSeconds()*4.0f;
    float dist_ = dist_To_Cursor_ * myDistChange_;
    float sinOffset_ = sin(dist_-time_)*2.0f;
    myDirToCursor_ *= sinOffset_*15.0;
    

    /// the radius of the particle is then changed based on the
    /// current sinOffset_ value.
    myRadius_ = channel.getValue(myLocation_)*sinOffset_;

}

/// This method draws the particle after the properties
/// have been updated.
void Particle::draw()
{
	
    /// sets the new color
    gl::color(myColor_);
    /// makes a new rectangle for the particle and draws it.
    Rectf rect_( myLocation_.x, myLocation_.y, myLocation_.x
               + myRadius_, myLocation_.y + myRadius_);
    gl::drawSolidRect(rect_);
    /** This would work if there were a proper graphic library to
        plot the pixels. I don't think there is one in cinder without
        the use of OpenGL...
    ///for (int i = 0; i < myLocation_.y + myRadius_; i++ ) {
       /// for (int j = 0; j < myLocation_.x + myRadius_; j++) {
          ///  putpixel(myLocation_.x+j, myLocation_.y+i);
        ///}
    ///}
    */
}

/// This method handles the changing the color of the
/// Particle when the mouse is scrolled
void Particle::changeColor(int wheelClicks) {

	change_ += (wheelClicks%256)/256.0;

	double redLevel_ = 1;
    double greenLevel_ = 1;
    double blueLevel_ = 1;
    if (change_ < 1/6.0){
        greenLevel_ = change_ / (1/6.0);
        blueLevel_ = 0;
    }
    else if (change_ < (1/3.0)){
        redLevel_ = 1 - ((change_ - (1/6.0)) / (1/6.0));
        blueLevel_ = 0;
    }
    else if (change_ < 0.5){
        redLevel_ = 0;
        blueLevel_ = (change_ - (1/3.0)) / (1/6.0);
    }
    else if (change_ < (2/3.0))
    {
        redLevel_ = 0;
        greenLevel_ = 1 - ((change_ - 0.5) / (1/6.0));
    }
    else if (change_ < (5/6.0))
    {
        redLevel_ = (change_ - (2/3.0)) / (1/6.0);
        greenLevel_ = 0;
    }
    else
    {
        blueLevel_ = 1 - ((change_ - (5/6.0)) / (1/6.0));
        greenLevel_ = 0;
    }

	//bounds checks
	if(redLevel_ > 1.0f)
		redLevel_ = 1.0f;
	else if(redLevel_ < 0.0f)
		redLevel_ = 0.0f;

	if(greenLevel_ > 1.0f)
		greenLevel_ = 1.0f;
	else if(greenLevel_ < 0.0f)
		greenLevel_ = 0.0f;

	if(blueLevel_ > 1.0f)
		blueLevel_ = 1.0f;
	else if(blueLevel_ < 0.0f)
		blueLevel_ = 0.0f;

	myColor_ = Color(redLevel_, blueLevel_, greenLevel_);

}

/// This method handles the changing increment for the
/// sine waves generated. It handles it from the
/// CatPictureApp::mouseWheel
void Particle::changeDist(float myIncrement_) {
    if (myIncrement_ > 0 && myDistChange_ < 0.5f) /// makes rings bigger
        myDistChange_ += 0.005f;
    else if (myIncrement_ < 0 && myDistChange_ > .0001f)/// makes rings smaller
        myDistChange_ -= 0.005f;
}
