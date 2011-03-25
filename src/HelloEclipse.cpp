/**
 * EclipseLovesCinder example application
 * When debugging, if you change your project name go into debug configurations (arrow next to bug icon), and modify where the debug application will run from
 *
 * This project is released under public domain, do whatever with it.
 *
 *
 * Mario Gonzalez
 * http://onedayitwillmake
 */
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/TriMesh.h"
#include "cinder/Rand.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Camera.h"
#include "cinder/app/Event.h"

class HelloWorldApp : public ci::app::AppBasic {
public:
	void setup();
	void prepareSettings( ci::app::AppBasic::Settings *settings );
	void mouseDown( ci::app::MouseEvent event );
	void mouseDrag( ci::app::MouseEvent event );
	void update();
	void draw();

	ci::MayaCamUI mayaCam;
};

void HelloWorldApp::prepareSettings( ci::app::AppBasic::Settings *settings )
{
	settings->setWindowSize( 800, 600 );
}

void HelloWorldApp::setup()
{
	std::cout << "Setting application path: " << getAppPath() << std::endl;
	chdir( getAppPath().c_str( ) );

	// Camera perspective properties
	float cameraFOV			= 100;
	float cameraNear		= 1;
	float cameraFar			= 50000;


	ci::Vec3f eyePoint = ci::Vec3f::zero();

//	ci::CameraPersp camPersp = ci::CameraPersp( getWindowWidth(), getWindowHeight(), cameraFOV );
//	camPersp.setEyePoint( eyePoint );
//	camPersp.setCenterOfInterestPoint( ci::Vec3f::zero() );
//	camPersp.setPerspective( cameraFOV, getWindowAspectRatio(), 0.1f, cameraFar );

	ci::CameraPersp initialCam;
	initialCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1, 10000 );
	mayaCam.setCurrentCam( initialCam );
}

void HelloWorldApp::mouseDown( ci::app::MouseEvent event )
{
	mayaCam.mouseDown( event.getPos() );
}

void HelloWorldApp::mouseDrag( ci::app::MouseEvent event )
{
	mayaCam.mouseDrag( event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown() );
}

void HelloWorldApp::update()
{
}

void HelloWorldApp::draw()
{
	using namespace ci;

	// clear out the window with black
	ci::Color aColor = ci::Color( 0, 0, 0 );
	ci::gl::clear( aColor );

	// Set the color
	aColor.r = fabs( cosf(getElapsedFrames() * 0.008) );
	aColor.g = fabs( sinf(getElapsedFrames() * 0.01) );
	aColor.b = (float) getMousePos().x / getWindowWidth();
	ci::gl::color( ci::Color(aColor * 0.5) );

	ci::TriMesh mesh;

	// Create the points of our cube
	Vec3f v0(-1,-1,-1);
	Vec3f v1( 1,-1,-1);
	Vec3f v2( 1, 1,-1);
	Vec3f v3(-1, 1,-1);
	Vec3f v4(-1,-1, 1);
	Vec3f v5( 1,-1, 1);
	Vec3f v6( 1, 1, 1);
	Vec3f v7(-1, 1, 1);

	// Create the colors for each vertex
	Color c0( 0, 0, 0 );
	Color c1( 1, 0, 0 );
	Color c2( 1, 1, 0 );
	Color c3( 0, 1, 0 );
	Color c4( 0, 0, 1 );
	Color c5( 1, 0, 1 );
	Color c6( 1, 1, 1 );
	Color c7( 0, 1, 1 );

	Vec3f faces[6][4] = {  /* Vertices for the 6 faces of a cube. */
	    {v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
	    {v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3} };

	Color colors[6][4] = {  /* colors for each vertex of the cube. */
	    {c0, c1, c2, c3}, {c3, c2, c6, c7}, {c7, c6, c5, c4},
	    {c4, c5, c1, c0}, {c5, c6, c2, c1}, {c7, c4, c0, c3} };

	for (int i = 0; i < 6; i++)
	{

	    mesh.appendVertex(faces[i][0]);
	    mesh.appendColorRGB(colors[i][0]);
	    mesh.appendVertex(faces[i][1]);
	    mesh.appendColorRGB(colors[i][1]);
	    mesh.appendVertex(faces[i][2]);
	    mesh.appendColorRGB(colors[i][2]);
	    mesh.appendVertex(faces[i][3]);
	    mesh.appendColorRGB(colors[i][3]);

	    int numberVertices = mesh.getNumVertices();

	    mesh.appendTriangle( numberVertices - 4, numberVertices - 3, numberVertices - 2 );
	    mesh.appendTriangle( numberVertices - 4, numberVertices - 2, numberVertices - 1 );

	};

	ci::gl::enableDepthRead();
	ci::gl::enableDepthWrite();
	ci::gl::setMatrices( mayaCam.getCamera() );

	ci:;gl::pushMatrices();
		ci::gl::draw( mesh );
	ci::gl::popMatrices();
//	ci::gl::drawLine( ci::Vec2f(getMousePos()), ci::Vec2f( getWindowCenter() ) );
}

CINDER_APP_BASIC( HelloWorldApp, ci::app::RendererGl )
