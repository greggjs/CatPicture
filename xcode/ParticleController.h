//
//  ParticleController.h
//  CatPicture
//
//  Created by Jake Gregg on 9/4/12.
//
//

#ifndef CatPicture_ParticleController_h
#define CatPicture_ParticleController_h

#pragma once
#include "Particle.h"
#include <list>

class ParticleController {
public:
	ParticleController();
    ParticleController(int myRes_);
	void update(const ci::Channel32f &channel_, const ci::Vec2i &mouseLoc_);
	void draw();
	void addParticles( int xRes_, int yRes_, int myRes_ );
    void addParticles( int amt_ );
	void removeParticles( int amt_ );
	void changeColor();
    void changeDist(float myIncrement_);
    
	std::list<Particle>	my_Particles_;
    
    int myXRes_, myYRes_;
};


#endif
