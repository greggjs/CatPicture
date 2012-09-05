//
//  ParticleController.cpp
//  CatPicture
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

ParticleController::ParticleController()
{
}

ParticleController::ParticleController(int myRes_) {
    myXRes_ = app::getWindowWidth()/myRes_;
    myYRes_ = app::getWindowHeight()/myRes_;
    
    for (int y = 0; y<myYRes_; y++) {
        for (int x = 0; x<myXRes_; x++) {
            addParticles(x, y, myRes_);
        }
    }
}

void ParticleController::update( const Channel32f &channel_, const Vec2i &mouseLoc_)
{
	for( list<Particle>::iterator p_ = my_Particles_.begin(); p_ != my_Particles_.end(); ++p_ ){
		p_->update(channel_, mouseLoc_);
	}
}

void ParticleController::draw()
{
	for( list<Particle>::iterator p_ = my_Particles_.begin(); p_ != my_Particles_.end(); ++p_ ){
		p_->draw();
	}
}

void ParticleController::addParticles( int xi_, int yi_, int myRes_ )
{
    float x = (xi_ + 0.25f)*(float)myRes_;
    float y = (yi_ + 0.25f)*(float)myRes_;
    my_Particles_.push_back( Particle( Vec2f( x, y ) ) );
	
}

void ParticleController::addParticles( int amt ) {
    for (int i=0; i < amt; i++) {
        float x = Rand::randFloat(app::getWindowWidth());
        float y = Rand::randFloat(app::getWindowHeight());
        my_Particles_.push_back(Particle(Vec2f(x,y)));
    }
}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		my_Particles_.pop_back();
	}
}

