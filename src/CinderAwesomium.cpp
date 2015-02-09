#include "CinderAwesomium.h"

#include "cinder/Log.h"

namespace ph { namespace awesomium {

// Translates a Cinder virtual key code to an Awesomium key code
int getWebKeyFromKeyEvent( ci::app::KeyEvent event )
{
    switch( event.getCode() )
    {
    mapKey(BACKSPACE, BACK)
    mapKey(TAB, TAB)
    mapKey(CLEAR, CLEAR)
    mapKey(RETURN, RETURN)
    mapKey(PAUSE, PAUSE)
    mapKey(ESCAPE, ESCAPE)
    mapKey(SPACE, SPACE)
    mapKey(EXCLAIM, 1)
    mapKey(QUOTEDBL, 2)
    mapKey(HASH, 3)
    mapKey(DOLLAR, 4)
    mapKey(AMPERSAND, 7)
    mapKey(QUOTE, OEM_7)
    mapKey(LEFTPAREN, 9)
    mapKey(RIGHTPAREN, 0)
    mapKey(ASTERISK, 8)
    mapKey(PLUS, OEM_PLUS)
    mapKey(COMMA, OEM_COMMA)
    mapKey(MINUS, OEM_MINUS)
    mapKey(PERIOD, OEM_PERIOD)
    mapKey(SLASH, OEM_2)
    mapKey(0, 0)
    mapKey(1, 1)
    mapKey(2, 2)
    mapKey(3, 3)
    mapKey(4, 4)
    mapKey(5, 5)
    mapKey(6, 6)
    mapKey(7, 7)
    mapKey(8, 8)
    mapKey(9, 9)
    mapKey(COLON, OEM_1)
    mapKey(SEMICOLON, OEM_1)
    mapKey(LESS, OEM_COMMA)
    mapKey(EQUALS, OEM_PLUS)
    mapKey(GREATER, OEM_PERIOD)
    mapKey(QUESTION, OEM_2)
    mapKey(AT, 2)
    mapKey(LEFTBRACKET, OEM_4)
    mapKey(BACKSLASH, OEM_5)
    mapKey(RIGHTBRACKET, OEM_6)
    mapKey(CARET, 6)
    mapKey(UNDERSCORE, OEM_MINUS)
    mapKey(BACKQUOTE, OEM_3)
    mapKey(a, A)
    mapKey(b, B)
    mapKey(c, C)
    mapKey(d, D)
    mapKey(e, E)
    mapKey(f, F)
    mapKey(g, G)
    mapKey(h, H)
    mapKey(i, I)
    mapKey(j, J)
    mapKey(k, K)
    mapKey(l, L)
    mapKey(m, M)
    mapKey(n, N)
    mapKey(o, O)
    mapKey(p, P)
    mapKey(q, Q)
    mapKey(r, R)
    mapKey(s, S)
    mapKey(t, T)
    mapKey(u, U)
    mapKey(v, V)
    mapKey(w, W)
    mapKey(x, X)
    mapKey(y, Y)
    mapKey(z, Z)
    mapKey(DELETE, DELETE)
    mapKey(KP0, NUMPAD0)
    mapKey(KP1, NUMPAD1)
    mapKey(KP2, NUMPAD2)
    mapKey(KP3, NUMPAD3)
    mapKey(KP4, NUMPAD4)
    mapKey(KP5, NUMPAD5)
    mapKey(KP6, NUMPAD6)
    mapKey(KP7, NUMPAD7)
    mapKey(KP8, NUMPAD8)
    mapKey(KP9, NUMPAD9)
    mapKey(KP_PERIOD, DECIMAL)
    mapKey(KP_DIVIDE, DIVIDE)
    mapKey(KP_MULTIPLY, MULTIPLY)
    mapKey(KP_MINUS, SUBTRACT)
    mapKey(KP_PLUS, ADD)
    mapKey(KP_ENTER, SEPARATOR)
    mapKey(KP_EQUALS, UNKNOWN)
    mapKey(UP, UP)
    mapKey(DOWN, DOWN)
    mapKey(RIGHT, RIGHT)
    mapKey(LEFT, LEFT)
    mapKey(INSERT, INSERT)
    mapKey(HOME, HOME)
    mapKey(END, END)
    mapKey(PAGEUP, PRIOR)
    mapKey(PAGEDOWN, NEXT)
    mapKey(F1, F1)
    mapKey(F2, F2)
    mapKey(F3, F3)
    mapKey(F4, F4)
    mapKey(F5, F5)
    mapKey(F6, F6)
    mapKey(F7, F7)
    mapKey(F8, F8)
    mapKey(F9, F9)
    mapKey(F10, F10)
    mapKey(F11, F11)
    mapKey(F12, F12)
    mapKey(F13, F13)
    mapKey(F14, F14)
    mapKey(F15, F15)
    mapKey(NUMLOCK, NUMLOCK)
    mapKey(CAPSLOCK, CAPITAL)
    mapKey(SCROLLOCK, SCROLL)
    mapKey(RSHIFT, RSHIFT)
    mapKey(LSHIFT, LSHIFT)
    mapKey(RCTRL, RCONTROL)
    mapKey(LCTRL, LCONTROL)
    mapKey(RALT, RMENU)
    mapKey(LALT, LMENU)
    mapKey(RMETA, LWIN)
    mapKey(LMETA, RWIN)
    mapKey(LSUPER, LWIN)
    mapKey(RSUPER, RWIN)
    mapKey(MODE, MODECHANGE)
    mapKey(COMPOSE, ACCEPT)
    mapKey(HELP, HELP)
    mapKey(PRINT, SNAPSHOT)
    mapKey(SYSREQ, EXECUTE)
    default: return Awesomium::KeyCodes::AK_UNKNOWN;
    }
}

// Conversion functions

ci::Surface toSurface( Awesomium::BitmapSurface* surface )
{
	if( ! surface ) throw EmptyPointerException();
	if( ! surface->buffer() ) throw InvalidBufferException();

	// set isDirty to false, because we are manually copying the data
	surface->set_is_dirty( false );

	// create the Surface by copying the data directly 
	return ci::Surface( (uint8_t*) surface->buffer(), surface->width(), surface->height(), surface->row_span(), ci::SurfaceChannelOrder::BGRA );

	// TODO: a more efficient way to render the Surface would be to create a ph::awesomium::Surface class that extends Awesomium::Surface,
	// and use the Paint and Scroll methods to efficiently copy the changed portion. Then use Awesomium::WebCore::set_surface_factory() 
	// to only create Cinder-compatible surfaces.
	//
}

ci::gl::TextureRef toTexture( Awesomium::BitmapSurface* surface, ci::gl::Texture::Format format )
{
	if( ! surface ) throw EmptyPointerException();
	if( ! surface->buffer() ) throw InvalidBufferException();

	// set isDirty to false, because we are manually copying the data
	surface->set_is_dirty( false );
	format.loadTopDown();

	// create the gl::Texture by copying the data directly
	return ci::gl::Texture::create( surface->buffer(), GL_BGRA, surface->width(), surface->height(), format );

	// TODO: a more efficient way to render the Surface would be to create a ph::awesomium::Texture class that extends Awesomium::Surface,
	// and use the Paint and Scroll methods to efficiently copy the changed portion. Then use Awesomium::WebCore::set_surface_factory() 
	// to only create Cinder-compatible surfaces.
}

Awesomium::WebKeyboardEvent toKeyEvent( ci::app::KeyEvent event, Awesomium::WebKeyboardEvent::Type type )
{
	Awesomium::WebKeyboardEvent evt;
	evt.type = type;
	evt.virtual_key_code = getWebKeyFromKeyEvent( event );
	evt.native_key_code = event.getNativeKeyCode();
	evt.text[0] = event.getChar();
    evt.unmodified_text[0] = event.getChar();

	char* buf = new char[20];
	Awesomium::GetKeyIdentifierFromVirtualKeyCode(evt.virtual_key_code, &buf);
#if defined( CINDER_MSW )
	strcpy_s<20>(evt.key_identifier, buf);
#else
	strncpy(evt.key_identifier, buf, 20);
#endif
    delete[] buf;

	evt.modifiers = 0;

	if( event.isAltDown() )
		evt.modifiers |= Awesomium::WebKeyboardEvent::kModAltKey;
	if( event.isControlDown() )
		evt.modifiers |= Awesomium::WebKeyboardEvent::kModControlKey;
	if( event.isMetaDown() )
		evt.modifiers |= Awesomium::WebKeyboardEvent::kModMetaKey;
	if( event.isShiftDown() )
		evt.modifiers |= Awesomium::WebKeyboardEvent::kModShiftKey;
	//if( event.isKeypadDown() )	// there is no Cinder isKeypadDown() method at this time
	//	evt.modifiers |= Awesomium::WebKeyboardEvent::kModIsKeypad;

	return evt;
}

Awesomium::WebKeyboardEvent toKeyChar( ci::app::KeyEvent event )
{
	Awesomium::WebKeyboardEvent evt;
	evt.type = Awesomium::WebKeyboardEvent::kTypeChar;

	evt.virtual_key_code = event.getChar();
	evt.native_key_code = event.getChar();
	evt.text[0] = event.getChar();
    evt.unmodified_text[0] = event.getChar();

	return evt;
} 

TouchDataManager::TouchDataManager()
{
	for ( int id = 0; id < MAX_TOUCHDATA_NUM; ++id )
		mAvailableAwesomiumIds.insert( id );
}

TouchDataManager::~TouchDataManager()
{
}

void TouchDataManager::addTouch( int id, const ci::ivec2 &pos, const ci::ivec2 &posScreen )
{
	if ( mTouchDataMap.size() >= MAX_TOUCHDATA_NUM )
	{
		CI_LOG_I( "!!! reached max num (" << id << ") " << pos );
		return;
	}

	if ( mTouchDataMap.find( id ) != mTouchDataMap.end() )
	{
		CI_LOG_I( "!!! data already in (" << id << ") " << pos );
	}
	else
	{
		CI_LOG_I( "addTouch (" << id << ") " << pos );
		TouchData touchData( id, lockAwesomiumId(), pos, posScreen, TouchData::Status::ADDED );
		mTouchDataMap[ id ] = touchData;
	}
}

void TouchDataManager::moveTouch( int id, const ci::ivec2 &pos, const ci::ivec2 &posScreen )
{
	if ( mTouchDataMap.find( id ) == mTouchDataMap.end() )
	{
		CI_LOG_I( "!!! not found (" << id << ") " << pos );
		if ( mTouchDataMap.size() < MAX_TOUCHDATA_NUM )
		{
			CI_LOG_I( "!!! add (" << id << ") " << pos );
			TouchData touchData( id, lockAwesomiumId(), pos, posScreen, TouchData::Status::ADDED );
			mTouchDataMap[ id ] = touchData;
		}
	}
	else
	{
		CI_LOG_I( "move (" << id << ") " << pos );
		mTouchDataMap[ id ].mPos = pos;
		mTouchDataMap[ id ].mPosScreen = posScreen;
		if ( mTouchDataMap[ id ].mStatus == TouchData::Status::HANDLED )
			mTouchDataMap[ id ].mStatus = TouchData::Status::UPDATED;
	}
}

void TouchDataManager::removeTouch( int id, const ci::ivec2 &pos, const ci::ivec2 &posScreen )
{
	if ( mTouchDataMap.find( id ) == mTouchDataMap.end() )
	{
		CI_LOG_I( "!!! not found (" << id << ") " << pos );
	}
	else
	{
		if ( mTouchDataMap[ id ].mStatus == TouchData::Status::ADDED )
		{
			unlockAwesomiumId( mTouchDataMap[ id ].mAwesomiumId );
			mTouchDataMap.erase( id );
			CI_LOG_I( "delete (" << id << ") " << pos << " - hasn't been added" );
			return;
		}

		CI_LOG_I( "set remove (" << id << ") " << pos );
		mTouchDataMap[ id ].mPos = pos;
		mTouchDataMap[ id ].mPosScreen = posScreen;
		mTouchDataMap[ id ].mStatus = TouchData::Status::RELEASED;
	}
}

void TouchDataManager::fillWebTouchPoint( Awesomium::WebTouchPoint *webTouchPoint, int pos, TouchData &touchData )
{
	webTouchPoint[ pos ].state = Awesomium::kWebTouchPointState_Stationary;
	webTouchPoint[ pos ].id = touchData.mAwesomiumId;
	webTouchPoint[ pos ].screen_position_x = touchData.mPosScreen.x;
	webTouchPoint[ pos ].screen_position_y = touchData.mPosScreen.y;
	webTouchPoint[ pos ].position_x = touchData.mPos.x;
	webTouchPoint[ pos ].position_y = touchData.mPos.y;
	webTouchPoint[ pos ].radius_x = 1;
	webTouchPoint[ pos ].radius_y = 1;
	webTouchPoint[ pos ].rotation_angle = 0;
	webTouchPoint[ pos ].force = 0;
}

bool TouchDataManager::fillWebTouchEventAll( Awesomium::WebTouchEvent &webTouchEvent )
{
	webTouchEvent.touches_length = 0;
	webTouchEvent.target_touches_length = 0;
	webTouchEvent.changed_touches_length = 0;

	bool hasAdded = false;
	bool hasUpdated = false;
	bool hasReleased = false;
	for ( auto& it : mTouchDataMap )
	{
		TouchData& touchData = it.second;

		fillWebTouchPoint( webTouchEvent.touches, webTouchEvent.touches_length, touchData );

		switch ( touchData.mStatus )
		{
		case TouchData::Status::ADDED    : { webTouchEvent.touches[ webTouchEvent.touches_length ].state = Awesomium::kWebTouchPointState_Pressed; touchData.mStatus = TouchData::Status::HANDLED; hasAdded    = true; } break;
		case TouchData::Status::UPDATED  : { webTouchEvent.touches[ webTouchEvent.touches_length ].state = Awesomium::kWebTouchPointState_Moved;   touchData.mStatus = TouchData::Status::HANDLED; hasUpdated  = true; } break;
		case TouchData::Status::RELEASED : { webTouchEvent.touches[ webTouchEvent.touches_length ].state = Awesomium::kWebTouchPointState_Released;                                                hasReleased = true; } break;
		case TouchData::Status::HANDLED  : /* do nothing */ break;
		default: assert( false );
		}
		webTouchEvent.touches_length++;
	}

	if ( hasReleased )
	{
		auto it = mTouchDataMap.begin();
		while ( it != mTouchDataMap.end() )
		{
			if ( it->second.mStatus == TouchData::Status::RELEASED )
			{
				CI_LOG_I( "delete (" << it->second.mId << ") " << it->second.mPos );
				unlockAwesomiumId( it->second.mAwesomiumId );
				mTouchDataMap.erase( it++ );
				continue;
			}
			++it;
		}
	}

	return hasAdded || hasUpdated || hasReleased;
}
/*
bool TouchDataManager::fillWebTouchEventAdd( Awesomium::WebTouchEvent &webTouchEvent )
{
	webTouchEvent.touches_length = 0;
	webTouchEvent.target_touches_length = 0;
	webTouchEvent.changed_touches_length = 0;

	bool ret = false;
	for ( auto& it : mTouchDataMap )
	{
		TouchData& touchData = it.second;

		fillWebTouchPoint( webTouchEvent.touches, webTouchEvent.touches_length, touchData );

		if ( touchData.mStatus == TouchData::Status::ADDED )
		{
			webTouchEvent.touches[ webTouchEvent.touches_length ].state = Awesomium::kWebTouchPointState_Pressed;
			touchData.mStatus = TouchData::Status::HANDLED;
			ret = true;
		}

		webTouchEvent.touches_length++;
	}

	return ret;
}

bool TouchDataManager::fillWebTouchEventMove( Awesomium::WebTouchEvent &webTouchEvent )
{
	webTouchEvent.touches_length = 0;
	webTouchEvent.target_touches_length = 0;
	webTouchEvent.changed_touches_length = 0;

	bool ret = false;
	for ( auto& it : mTouchDataMap )
	{
		TouchData& touchData = it.second;

		fillWebTouchPoint( webTouchEvent.touches, webTouchEvent.touches_length, touchData );

		if ( touchData.mStatus == TouchData::Status::UPDATED )
		{
			webTouchEvent.touches[ webTouchEvent.touches_length ].state = Awesomium::kWebTouchPointState_Moved;
			touchData.mStatus = TouchData::Status::HANDLED;
			ret = true;
		}

		webTouchEvent.touches_length++;
	}

	return ret;
}

bool TouchDataManager::fillWebTouchEventRemove( Awesomium::WebTouchEvent &webTouchEvent )
{
	webTouchEvent.touches_length = 0;
	webTouchEvent.target_touches_length = 0;
	webTouchEvent.changed_touches_length = 0;

	bool ret = false;
	for ( auto& it : mTouchDataMap )
	{
		TouchData& touchData = it.second;

		fillWebTouchPoint( webTouchEvent.touches, webTouchEvent.touches_length, touchData );

		if ( touchData.mStatus == TouchData::Status::RELEASED )
		{
			webTouchEvent.touches[ webTouchEvent.touches_length ].state = Awesomium::kWebTouchPointState_Released;
			ret = true;
		}

		webTouchEvent.touches_length++;
	}

	if ( ret )
	{
		auto it = mTouchDataMap.begin();
		while ( it != mTouchDataMap.end() )
		{
			if ( it->second.mStatus == TouchData::Status::RELEASED )
			{
				unlockAwesomiumId( it->second.mAwesomiumId ),
					mTouchDataMap.erase( it++ );
			}
			else
			{
				++it;
			}
		}
	}

	return ret;
}
*/
int TouchDataManager::lockAwesomiumId()
{
	for ( int id = 0; id < MAX_TOUCHDATA_NUM; ++id )
	{
		if ( mAvailableAwesomiumIds.find( id ) != mAvailableAwesomiumIds.end() )
		{
			mAvailableAwesomiumIds.erase( id );
			ci::app::console() << "Lock awesomium id: " << id << std::endl;
			return id;
		}
	}

	assert( false );
	return -1;
}

void TouchDataManager::unlockAwesomiumId( int id )
{
	ci::app::console() << "Unlock awesomium id: " << id << std::endl;
	assert( id >= 0 && id < MAX_TOUCHDATA_NUM );
	assert( mAvailableAwesomiumIds.find( id ) == mAvailableAwesomiumIds.end() );

	mAvailableAwesomiumIds.insert( id );
}

WebViewEventHandler::WebViewEventHandler( Awesomium::WebView *webView, ci::app::WindowRef window )
	: mWebView( webView )
	, mWindow( window )
{
	mTouchDataManager = TouchDataManager::create();
}

WebViewEventHandler::~WebViewEventHandler()
{
}

void WebViewEventHandler::handleKeyDown( ci::app::KeyEvent event )
{
	// handle cut, copy, paste (as suggested by Simon Geilfus - thanks mate)
	if ( event.isAccelDown() )
	{
		switch ( event.getCode() )
		{
		case ci::app::KeyEvent::KEY_x: mWebView->Cut(); return;
		case ci::app::KeyEvent::KEY_c: mWebView->Copy(); return;
		case ci::app::KeyEvent::KEY_v: mWebView->Paste(); return;
		}
	}

	// other keys
	mWebView->Focus();
	mWebView->InjectKeyboardEvent( toKeyEvent( event, Awesomium::WebKeyboardEvent::kTypeKeyDown ) );
	mWebView->InjectKeyboardEvent( toKeyChar( event ) );
}

void WebViewEventHandler::handleKeyUp( ci::app::KeyEvent event )
{
	mWebView->Focus();
	mWebView->InjectKeyboardEvent( toKeyEvent( event, Awesomium::WebKeyboardEvent::kTypeKeyUp ) );
}

void WebViewEventHandler::handleMouseMove( ci::app::MouseEvent event )
{
	mWebView->InjectMouseMove( event.getX(), event.getY() );
}

void WebViewEventHandler::handleMouseDown( ci::app::MouseEvent event )
{
	if ( event.isLeft() )
		mWebView->InjectMouseDown( Awesomium::kMouseButton_Left );
	else if ( event.isMiddle() )
		mWebView->InjectMouseDown( Awesomium::kMouseButton_Middle );
	else if ( event.isRight() )
		mWebView->InjectMouseDown( Awesomium::kMouseButton_Right );
}

void WebViewEventHandler::handleMouseDrag( ci::app::MouseEvent event )
{
	mWebView->InjectMouseMove( event.getX(), event.getY() );
}

void WebViewEventHandler::handleMouseUp( ci::app::MouseEvent event )
{
	if ( event.isLeft() )
		mWebView->InjectMouseUp( Awesomium::kMouseButton_Left );
	else if ( event.isMiddle() )
		mWebView->InjectMouseUp( Awesomium::kMouseButton_Middle );
	else if ( event.isRight() )
		mWebView->InjectMouseUp( Awesomium::kMouseButton_Right );
}

void WebViewEventHandler::handleMouseWheel( ci::app::MouseEvent event, int increment )
{
	mWebView->InjectMouseWheel( increment * int( event.getWheelIncrement() ), 0 );
}

void WebViewEventHandler::addTouch( int id, const ci::ivec2 &pos )
{
	mTouchDataManager->addTouch( id, pos, mWindow->getPos() + pos );
}

void WebViewEventHandler::moveTouch( int id, const ci::ivec2 &pos )
{
	mTouchDataManager->moveTouch( id, pos, mWindow->getPos() + pos );
}

void WebViewEventHandler::removeTouch( int id, const ci::ivec2 &pos )
{
	mTouchDataManager->removeTouch( id, pos, mWindow->getPos() + pos );
}

void WebViewEventHandler::updateTouches()
{
	mWebView->Focus();

	if ( mTouchDataManager->fillWebTouchEventAll( mWebTouchEvent ) )
		mWebView->InjectTouchEvent( mWebTouchEvent );

/*
	if( mTouchDataManager->fillWebTouchEventAdd( mWebTouchEvent ) )
		mWebView->InjectTouchEvent( mWebTouchEvent );

	if ( mTouchDataManager->fillWebTouchEventMove( mWebTouchEvent ) )
		mWebView->InjectTouchEvent( mWebTouchEvent );

	if ( mTouchDataManager->fillWebTouchEventRemove( mWebTouchEvent ) )
		mWebView->InjectTouchEvent( mWebTouchEvent );
*/
}


} } // namespace ph::awesomium
