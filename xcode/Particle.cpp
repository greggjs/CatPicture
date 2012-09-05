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
	mVel	= 0.0f;
	mRadius	= 0.5f;
}

void Particle::update( const Channel32f &channel)
{
	mRadius = channel.getValue(mLoc) * Rand::randFloat(0.0f, 7.0f);
    
    float gray = channel.getValue( mLoc );
    mColor = Color(gray, gray, gray);
    
    mLoc += mDir * mVel;
}

void Particle::draw()
{
	gl::color(mColor);
    gl::drawSolidCircle( mLoc, mRadius );
}

