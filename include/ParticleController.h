//
//  ParticleController.h
//  CatPicture
//
//  This is the way that I organized all the particles on the
//  screen. This controller adds, removes, and can change the
//  color and ring size of the channel picture coming in.
//
//  This file is (c) 2012. It is licensed under the
//  CC by 3.0 License, which means you are free to use, share,
//  and remix it as long as you give attribution. Commercial uses
//  are allowed.
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
	ParticleController(); /// default constructor
    ParticleController(int myRes_); /// constructs a new ParticleController
                                    /// with a specific resolution
    
    /// update, draw, changeColor, and changeDist are all forwarded to
    /// the same function call in the Particle class.
	void update(const ci::Channel32f &channel_, const ci::Vec2i &mouseLoc_);
	void draw();
    void changeColor();
    void changeDist(float myIncrement_);
    
    /// adds Particles to the ParticleController
	void addParticles( int xRes_, int yRes_, int myRes_ );
    void addParticles( int amt_ );
    /// removes Particles from the ParticleController
	void removeParticles( int amt_ );
    
    /// This is what holds all my particles
	std::list<Particle>	my_Particles_;
    
    /// stores the X-Y resolution of what I'm drawing
    int myXRes_, myYRes_;
};


#endif
