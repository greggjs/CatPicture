//
//  Particle.h
//  CatPicture
//
//  This class I created create a particle to represent an area of the
//  screen. These particles have a certain dimension to them as defined
//  in my other class, ParticleController.cpp and ParticleController.h.
//  These allow me to get the grainy blur of my image and the sine wave
//  produced from the mouse tip.
//
//  This file is (c) 2012. It is licensed under the
//  CC by 3.0 License, which means you are free to use, share,
//  and remix it as long as you give attribution. Commercial uses
//  are allowed.
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
	Particle(); /// creates new Particle
	Particle( ci::Vec2f loc); /// creates new Particle in specified location
    /// update function call for Particle; takes a channel and a mouse location
	void update(const ci::Channel32f &channel, const ci::Vec2i &mouseLoc);
	/// draw function. it really just draws the rectangle
    void draw();
    void changeColor(); /// changes the color of the Particle
    void changeDist(float myIncrement_); /// changes the size of the rings
	
	ci::Vec2f	myLocation_; /// location of Particle
	ci::Vec2f	myDirection_; /// direction of Particle
    ci::Vec2f   myDirToCursor_; /// Direction relative to cursor
	float       rand_; /// stores a random float for color
	float		myRadius_; /// stores the radius of particle since they are square
    float       myDistChange_; /// stores the distance change
    bool        isRed_; /// stores if the current color is red, blue, or green
    bool        isGreen_;
    bool        isBlue_;
    ci::Color   myColor_; /// stores current color
};

#endif
