#pragma once
#include <cstddef>

#include "../../core/Common.h"
#include "../classvars/GlobalVars.h"
#include "../data/Vector.h"

enum ClientFrameStage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,

	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,

	FRAME_RENDER_START,
	FRAME_RENDER_END,

	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE
};

enum ButtonCode
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};

class ViewSetup
{
public:
	int x;
	int unscaledX;
	int y;
	int unscaledY;
	int width;
	int unscaledWidth;
	int height;
	int unscaledHeight;
	bool	 ortho;
	float	 orthoLeft;
	float	 orthoTop;
	float	 orthoRight;
	float	 orthoBottom;
	std::byte pad0[0x7C];
	float fov;
	float viewModelFOV;
	Vector origin;
	Vector view;
	float	 nearZ;
	float	 farZ;
	float	 nearViewmodelZ;
	float	 farViewmodelZ;
	float	 aspectRatio;
	float	 nearBlurDepth;
	float	 nearFocusDepth;
	float	 farFocusDepth;
	float	 farBlurDepth;
	float	 nearBlurRadius;
	float	 farBlurRadius;
	float	 doFQuality;
	int motionBlurMode;
	float	 shutterTime;
	Vector shutterOpenPosition;
	Vector shutterOpenAngles;
	Vector shutterClosePosition;
	Vector shutterCloseAngles;
	float offCenterTop;
	float offCenterBottom;
	float offCenterLeft;
	float offCenterRight;
	bool offCenter : 1;
	bool renderToSubrectOfLargerScreen : 1;
	bool bloomAndToneMapping : 1;
	bool depthOfField : 1;
	bool HDRTarget : 1;
	bool drawWorldNormal : 1;
	bool cullFontFaces : 1;
	bool cacheFullSceneState : 1;
	bool CSMView : 1;
};

// unfinished
class EngineSprite;

// csgo -> public -> cdll_int.h
class IBaseClientDLL
{
public:
	// Connect appsystem components, get global interfaces, don't run any other init code
	virtual int Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;

	virtual void Disconnect() = 0;

	// run other init code here
	virtual int Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;

	virtual void PostInit() = 0;

	// Called once when the client DLL is being unloaded
	virtual void Shutdown(void) = 0;

	// Called at the start of each level change
	virtual void LevelInitPreEntity(char const* pMapName) = 0;

	// Called at the start of a new level, after the entities have been received and created
	virtual void LevelInitPostEntity() = 0;

	// Called at the end of a level
	virtual void LevelShutdown(void) = 0;
};