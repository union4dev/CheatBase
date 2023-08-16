#pragma once
#include <cstddef>

#include "../../core/Common.h"
#include "../classvars/GlobalVars.h"
#include "../classvars/ClientClass.h"
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

struct ScreenFade_t
{
	unsigned short 	duration;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration
	unsigned short 	holdTime;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration until reset (fade & hold)
	short fadeFlags;		// flags
	std::byte r, g, b, a;		// fade to color ( max alpha )
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

	// Request a pointer to the list of client datatable classes
	virtual ClientClass* GetAllClasses(void) = 0;

	// Called once per level to re-initialize any hud element drawing stuff
	virtual int HudVidInit(void) = 0;
	// Called by the engine when gathering user input
	virtual void HudProcessInput(bool bActive) = 0;
	// Called oncer per frame to allow the hud elements to think
	virtual void HudUpdate(bool bActive) = 0;
	// Reset the hud elements to their initial states
	virtual void HudReset(void) = 0;
	// Display a hud text message
	virtual void HudText(const char* message) = 0;

	// Draw the console overlay?
	virtual bool ShouldDrawDropdownConsole() = 0;

	// Mouse Input Interfaces
	// Activate the mouse (hides the cursor and locks it to the center of the screen)
	virtual void IN_ActivateMouse(void) = 0;
	// Deactivates the mouse (shows the cursor and unlocks it)
	virtual void IN_DeactivateMouse(void) = 0;
	// This is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
	//  This call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if 
	//  rendering or other processing is taking too long
	virtual void IN_Accumulate(void) = 0;
	// Reset all key and mouse states to their initial, unpressed state
	virtual void IN_ClearStates(void) = 0;
	// If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
	virtual bool IN_IsKeyDown(const char* name, bool& isdown) = 0;
	// Raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
	//  if the client .dll returns 0, the key is swallowed.
	virtual int IN_KeyEvent(int eventcode, ButtonCode keynum, const char* pszCurrentBinding) = 0;

	// This function is called once per tick to create the player CUserCmd (used for prediction/physics simulation of the player)
	// Because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
	//  specifies how much additional mouse / keyboard simulation to perform.
	virtual void CreateMove(
		int sequence_number,			// sequence_number of this cmd
		float input_sample_frametime,	// Frametime for mouse input sampling
		bool active) = 0;				// True if the player is active (not paused)

	// If the game is running faster than the tick_interval framerate, then we do extra mouse sampling to avoid jittery input
	//  This code path is much like the normal move creation code, except no move is created
	virtual void ExtraMouseSample(float frametime, bool active) = 0;

	// Encode the delta (changes) between the CUserCmd in slot from vs the one in slot to.  The game code will have
	//  matching logic to read the delta.
	virtual bool WriteUsercmdDeltaToBuffer(int nSlot, bf_write* buf, int from, int to, bool isnewcommand) = 0;

	// Demos need to be able to encode/decode CUserCmds to memory buffers, so these functions wrap that
	virtual void EncodeUserCmdToBuffer(int nSlot, bf_write& buf, int slot) = 0;
	virtual void DecodeUserCmdFromBuffer(int nSlot, bf_read& buf, int slot) = 0;

	// Set up and render one or more views (e.g., rear view window, etc.).  This called into RenderView below
	virtual void View_Render(Rect* rect) = 0;

	// Allow engine to expressly render a view (e.g., during timerefresh)
	// See IVRenderView.h, PushViewFlags_t for nFlags values
	virtual void RenderView(const ViewSetup& view, int nClearFlags, int whatToDraw) = 0;

	// Apply screen fade directly from engine
	virtual void View_Fade(ScreenFade_t* pSF) = 0;

	// The engine has parsed a crosshair angle message, this function is called to dispatch the new crosshair angle
	virtual void SetCrosshairAngle(const Vector& angle) = 0;

	// Sprite (.spr) model handling code
	// Load a .spr file by name
	virtual void InitSprite(EngineSprite* pSprite, const char* loadname) = 0;
	// Shutdown a .spr file
	virtual void ShutdownSprite(EngineSprite* pSprite) = 0;
	// Returns sizeof( CEngineSprite ) so the engine can allocate appropriate memory
	virtual int GetSpriteSize(void) const = 0;

	// Called when a player starts or stops talking.
	// entindex is -1 to represent the local client talking (before the data comes back from the server). 
	// entindex is -2 to represent the local client's voice being acked by the server.
	// entindex is GetPlayer() when the server acknowledges that the local client is talking.
	virtual void VoiceStatus(int entindex, int iSsSlot, bool bTalking) = 0;

	// returns false if the player can't hear the other client due to game rules (eg. the other team)
	virtual bool PlayerAudible(int iPlayerIndex) = 0;

	// Networked string table definitions have arrived, allow client .dll to 
	//  hook string changes with a callback function ( see INetworkStringTableClient.h )
	virtual void InstallStringTableCallback(char const* tableName) = 0;

	// Notification that we're moving into another stage during the frame.
	virtual void FrameStageNotify(ClientFrameStage curStage) = 0;

	// The engine has received the specified user message, this code is used to dispatch the message handler
	virtual bool DispatchUserMessage(int msg_type, uint32_t nFlags, int size, const void* msg) = 0;	// New protobuf version
};