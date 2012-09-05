//
//  Particle.h
//  CatPicture
//
//  Created by Jake Gregg on 9/4/12.
//
//

#ifndef CatPicture_Particle_h
#define CatPicture_Particle_h

#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Color.h"
#include <vector>

class Particle {
public:
	Particle();
	Particle( ci::Vec2f loc);
	void update(const ci::Channel32f &channel, const ci::Vec2i &mouseLoc);
	void draw();
    void changeColor();
    void changeDist(float myIncrement_);
	
	ci::Vec2f	myLocation_;
	ci::Vec2f	myDirection_;
    ci::Vec2f   myDirToCursor_;
	float		myVelocity_;
	float       rand_;
	float		myRadius_;
    float       myDistChange_;
    bool        isRed_;
    bool        isGreen_;
    bool        isBlue_;
    ci::Color   myColor_;
};

#endif
