//
//  Particle.cpp
//  CatPicture
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

Particle::Particle()
{
}

Particle::Particle( Vec2f loc )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();
    mDirToCursor = Vec2i::zero();
	mVel	= 0.0f;
    
	mRadius	= 0.0f;
    mScale = 3.0f;
}

void Particle::update( const Channel32f &channel, const Vec2i &mouseLoc)
{
	mDirToCursor = mouseLoc - mLoc;
    
    float distToCursor = mDirToCursor.length();
    float time = app::getElapsedSeconds()*4.0f;
    float dist = distToCursor * 0.05f;
    float sinOffset = sin(dist-time)*100.0f;
    
    mDirToCursor.normalize();
    Vec2f newLoc = mLoc + mDirToCursor*sinOffset;
    newLoc.x = constrain(newLoc.x, 0.0f, channel.getWidth()-1.0f);
    newLoc.y = constrain(newLoc.y, 0.0f, channel.getHeight()-1.0f);
    
    float gray = channel.getValue( newLoc );
    mColor = Color(gray, gray, gray);
    
    mRadius = channel.getValue(newLoc)*2.0f;///Rand::randFloat(0.0f, 7.0f);

}

void Particle::draw()
{
	/**
    gl::color(mColor);
    gl::drawSolidCircle( mLoc, mRadius );
     */
    gl::color(Color(1.0f, 1.0f, 1.0f));
    gl::drawVector(Vec3f(mLoc, 0.0f), Vec3f(mLoc + mDirToCursor * 15.0f, 0.0f), 6.0f, 3.0f);
    gl::drawSolidCircle(mLoc+mDirToCursor*0.2f, mRadius);
}

