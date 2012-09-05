//
//  Particle.cpp
//  CatPicture
//
//  This class dictates the actions taken place by the particle
//  shapes created in my program.
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
/// the Direction relative to the cursor is initiallize at 0.
Particle::Particle( Vec2f loc )
{
	myLocation_	= loc;
	myDirection_	= Rand::randVec2f();
    myDirToCursor_ = Vec2i::zero();
	myRadius_	= 0.0f;
    isRed_ = false;
    isGreen_ = true;
    isBlue_ = true;;
    rand_ = randFloat(0.0f, 1.0f);
}

void Particle::update( const Channel32f &channel, const Vec2i &mouseLoc)
{
	myDirToCursor_ = mouseLoc - myLocation_;
    
    float dist_To_Cursor_ = myDirToCursor_.length();
    float time_ = app::getElapsedSeconds()*4.0f;
    float dist_ = dist_To_Cursor_ * 0.05f;
    float sinOffset_ = sin(dist_-time_)*2.0f;
    myDirToCursor_ *= sinOffset_*15.0f;
    
    
    if (isRed_) {
        rand_ = randFloat(0.0f, 1.0f);
        myColor_ = Color(rand_, 0.0f, 0.0f);
    }
    else if (isGreen_) {
        rand_ = randFloat(0.0f, 1.0f);
        myColor_ = Color(0.0f, rand_, 0.0f);
    }
    else if (isBlue_) {
        rand_ = randFloat(0.0f, 1.0f);
        myColor_ = Color(0.0f, 0.0f, rand_);
    }
        
   
    myRadius_ = channel.getValue(myLocation_)*sinOffset_;

}

void Particle::draw()
{
	
    gl::color(myColor_);
    Rectf rect_( myLocation_.x, myLocation_.y, myLocation_.x
               + myRadius_, myLocation_.y + myRadius_);
    gl::drawSolidRect(rect_);
    ///gl::drawSolidCircle(mLoc+mDirToCursor, mRadius);
}

void Particle::changeColor() {
    if (!isRed_) {
        isRed_ = !isRed_;
        isGreen_ = !isGreen_;
    }
    else if (!isGreen_) {
        isGreen_ = !isGreen_;
        isBlue_ = !isBlue_;
    }
    else if (!isBlue_) {
        isBlue_ = !isBlue_;
        isRed_ = !isRed_;
    }
}
