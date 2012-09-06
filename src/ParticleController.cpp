//
//  ParticleController.cpp
//  CatPicture
//
//  This class describes all of the functions described in the header
//
//  This file is (c) 2012. It is licensed under the
//  CC by 3.0 License, which means you are free to use, share,
//  and remix it as long as you give attribution. Commercial uses
//  are allowed.
//
//  Created by Jake Gregg on 9/4/12.
//
//

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;

/// defaul particle constructor
ParticleController::ParticleController()
{
}

/// constructs a new ParticleController with a specified
/// resolution. it adds all the particles specified by the
/// given resolution.
ParticleController::ParticleController(int myRes_) {
    
    /// store the X-Y resolution
    myXRes_ = app::getWindowWidth()/myRes_;
    myYRes_ = app::getWindowHeight()/myRes_;
    
    /// create a particle for each part of the resolution
    for (int y = 0; y<myYRes_; y++) {
        for (int x = 0; x<myXRes_; x++) {
            addParticles(x, y, myRes_);
        }
    }
}
/// points the ParticleController to the Particle version of update
void ParticleController::update( const Channel32f &channel_, const Vec2i &mouseLoc_)
{
	for( list<Particle>::iterator p_ = my_Particles_.begin(); p_ != my_Particles_.end(); ++p_ ){
		p_->update(channel_, mouseLoc_);
	}
}

/// points the ParticleController to the Particle version of draw
void ParticleController::draw()
{
	for( list<Particle>::iterator p_ = my_Particles_.begin(); p_ != my_Particles_.end(); ++p_ ){
		p_->draw();
	}
}

/// points the ParticleController to the Particle version of changeColor
void ParticleController::changeColor() {
    for( list<Particle>::iterator p_ = my_Particles_.begin(); p_ != my_Particles_.end(); ++p_ ){
		p_->changeColor();
	}
}

/// points the ParticleController to the Particle version of changeDist
void ParticleController::changeDist(float myIncrement_) {
    for( list<Particle>::iterator p_ = my_Particles_.begin(); p_ != my_Particles_.end(); ++p_ ){
		p_->changeDist(myIncrement_);
	}
}

/// this add a particle to the ParticleController with specified
/// location and resolution.
void ParticleController::addParticles( int xi_, int yi_, int myRes_ )
{
    /// give the particle coordinates
    float x = (xi_ + 0.25f)*(float)myRes_;
    float y = (yi_ + 0.25f)*(float)myRes_;
    /// push it onto the list of Particles
    my_Particles_.push_back( Particle( Vec2f( x, y ) ) );
	
}

/// this was the old way I added particles, by a specified
/// amount
void ParticleController::addParticles( int amt ) {
    
    /// for as many as specified, create a new particle
    /// randomly and push it onto the list
    for (int i=0; i < amt; i++) {
        float x = Rand::randFloat(app::getWindowWidth());
        float y = Rand::randFloat(app::getWindowHeight());
        my_Particles_.push_back(Particle(Vec2f(x,y)));
    }
}

