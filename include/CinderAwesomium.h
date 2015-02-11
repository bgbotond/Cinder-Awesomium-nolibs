#pragma once

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include "cinder/Exception.h"
#include "cinder/Surface.h"
#include "cinder/app/AppBasic.h"
#include "cinder/app/Window.h"
#include "cinder/gl/Texture.h"

namespace ph { namespace awesomium {

// exceptions
class EmptyPointerException : public ci::Exception {
	virtual const char * what() const throw() { return "The specified pointer is empty."; }
};

class InvalidBufferException : public ci::Exception {
	virtual const char * what() const throw() { return "The specified buffer is empty or not initialized."; }
};

// A helper macro, used in 'getWebKeyFromKeyEvent'
#define mapKey(a, b) case ci::app::KeyEvent::KEY_##a: return Awesomium::KeyCodes::AK_##b;

// Translates a Cinder virtual key code to an Awesomium key code
int getWebKeyFromKeyEvent( ci::app::KeyEvent event );

// Conversion functions
ci::Surface toSurface( Awesomium::BitmapSurface* surface );

inline ci::Surface toSurface( Awesomium::WebView* webview )
{
	return toSurface( (Awesomium::BitmapSurface*) webview->surface() );
}

ci::gl::TextureRef toTexture( Awesomium::BitmapSurface* surface, ci::gl::Texture::Format format=ci::gl::Texture::Format() );

inline ci::gl::TextureRef toTexture( Awesomium::WebView* webview, ci::gl::Texture::Format format=ci::gl::Texture::Format() )
{
	return toTexture( (Awesomium::BitmapSurface*) webview->surface(), format );
}

inline bool isDirty( Awesomium::WebView* webview ) 
{
	if( ! webview ) throw EmptyPointerException();

	Awesomium::BitmapSurface* surface = (Awesomium::BitmapSurface*) webview->surface();
	if( ! surface ) return false; //throw EmptyPointerException();

	return surface->is_dirty();
}

Awesomium::WebKeyboardEvent toKeyEvent( ci::app::KeyEvent event, Awesomium::WebKeyboardEvent::Type type );

Awesomium::WebKeyboardEvent toKeyChar( ci::app::KeyEvent event );

// helper class to handle web view events

typedef std::shared_ptr< class WebViewEventHandler > WebViewEventHandlerRef;
typedef std::shared_ptr< class TouchDataManager > TouchDataManagerRef;

class TouchDataManager
{
private:
	static const int MAX_TOUCHDATA_NUM = 7; // fixme: in case of 8 touch points awesomium crashes

public:
	struct TouchData
	{
		enum class Status
		{
			ADDED,
			UPDATED,
			RELEASED,
			HANDLED,
		};

		int mId;
		int mAwesomiumId;
		ci::ivec2 mPos;
		ci::ivec2 mPosScreen;
		Status mStatus;

		TouchData()
			: mId( -1 )
			, mAwesomiumId( -1 )
			, mPos( ci::ivec2( 0, 0 ) )
			, mPosScreen( ci::ivec2( 0, 0 ) )
			, mStatus( Status::HANDLED )
		{
		}

		TouchData( int id, int awesomiumId, ci::ivec2 pos, ci::ivec2 posScreen, Status status )
			: mId( id )
			, mAwesomiumId( awesomiumId )
			, mPos( pos )
			, mPosScreen( posScreen )
			, mStatus( status )
		{
		}
	};

public:
	static TouchDataManagerRef create() { return TouchDataManagerRef( new TouchDataManager() ); }
	virtual ~TouchDataManager();

	void addTouch( int id, const ci::ivec2 &pos, const ci::ivec2 &posScreen );
	void moveTouch( int id, const ci::ivec2 &pos, const ci::ivec2 &posScreen );
	void removeTouch( int id, const ci::ivec2 &pos, const ci::ivec2 &posScreen );
	void removeTouchAll();

	bool fillWebTouchEventAll( Awesomium::WebTouchEvent &webTouchEvent );
	bool fillWebTouchEventAdd( Awesomium::WebTouchEvent &webTouchEvent );
	bool fillWebTouchEventMove( Awesomium::WebTouchEvent &webTouchEvent );
	bool fillWebTouchEventRemove( Awesomium::WebTouchEvent &webTouchEvent );

private:
	TouchDataManager();

	int lockAwesomiumId();
	void unlockAwesomiumId( int id );

	void fillWebTouchPoint( Awesomium::WebTouchPoint *webTouchPoint, int pos, TouchData &touchData );

private:
	std::map< int, TouchData > mTouchDataMap;
	std::set< int > mAvailableAwesomiumIds;
};

class WebViewEventHandler
{
public:
	static WebViewEventHandlerRef create( Awesomium::WebView *webView, ci::app::WindowRef window ) { return WebViewEventHandlerRef( new WebViewEventHandler( webView, window ) ); }

	~WebViewEventHandler();

	void handleKeyDown( ci::app::KeyEvent event );
	void handleKeyUp( ci::app::KeyEvent event );
	void handleMouseMove( ci::app::MouseEvent event );
	void handleMouseUp( ci::app::MouseEvent event );
	void handleMouseDrag( ci::app::MouseEvent event );
	void handleMouseDown( ci::app::MouseEvent event );
	void handleMouseWheel( ci::app::MouseEvent event, int increment = 150 );

	void addTouch( int id, const ci::ivec2 &pos );
	void moveTouch( int id, const ci::ivec2 &pos );
	void removeTouch( int id, const ci::ivec2 &pos );
	void removeTouchAll();
	void updateTouches();

private:
	WebViewEventHandler( Awesomium::WebView *webView, ci::app::WindowRef window );

private:
	Awesomium::WebView *mWebView;
	ci::app::WindowRef mWindow;
	TouchDataManagerRef mTouchDataManager;
	Awesomium::WebTouchEvent mWebTouchEvent;
};

} } // namespace ph::awesomium
