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
    ParticleController(int res);
	void update(const ci::Channel32f &channel, const ci::Vec2i &mouseLoc);
	void draw();
	void addParticles( int xRes, int yRes, int res );
    void addParticles( int amt );
	void removeParticles( int amt );
	
	std::list<Particle>	mParticles;
    
    int mXRes, mYRes;
};


#endif
