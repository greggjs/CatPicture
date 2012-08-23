/**
 * @file CatPictureApp.cpp
 * A simple app to display a cat picture using Cinder
 *
 * @author Jake Gregg
 * @date 2012-08-23
 *
 * @note This file is (c) 2012. It is licensed under the
 * CC by 3.0 License, which means you are free to use, share,
 * and remix it as long as you give attribution. Commercial uses
 * are allowed.
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	gl::Texture myImage;

	/// Brightness ranges from 0 to 1
  private:
	float brightness_;
	
};

void CatPictureApp::setup()
{
	brightness_ = 1.0f;
	
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	brightness_ = brightness_ - 0.01f;
	if (brightness_ < 0.0f) {
		brightness_ = 1.0f;
	}
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( brightness_, brightness_, brightness_ ) ); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
