#pragma once
#include "../../core/Common.h"
#include "../data/Matrix.h"

struct Model;

enum ModelDataCategory
{
	MODEL_DATA_LIGHTING_MODEL,	// data type returned is a RenderableLightingModel_t
	MODEL_DATA_STENCIL,			// data type returned is a ShaderStencilState_t
	MODEL_DATA_CATEGORY_COUNT,
};

enum ShadowType
{
	SHADOWS_NONE = 0,
	SHADOWS_SIMPLE,
	SHADOWS_RENDER_TO_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC,	// the shadow is always changing state
	SHADOWS_RENDER_TO_DEPTH_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC_CUSTOM,	// changing, and entity uses custom rendering code for shadow
};

struct RenderableInstance
{
	uint8_t m_nAlpha;
};

class PVSNotify
{
public:
	virtual void OnPVSStatusChanged(bool bInPVS) = 0;
};

class ClientModelRenderable
{
public:
	virtual bool GetRenderData(void* pData, ModelDataCategory nCategory) = 0;
};

class ClientRenderable
{
public:
	// Gets at the containing class...
	virtual ClientUnknown* GetIClientUnknown() = 0;

	// Data accessors
	virtual Vector const& GetRenderOrigin(void) = 0;
	virtual Vector const& GetRenderAngles(void) = 0;

	virtual bool ShouldDraw(void) = 0;
	virtual int GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void Unused(void) const {}

	virtual unsigned short GetShadowHandle() const = 0;

	// Used by the leaf system to store its render handle.
	virtual unsigned short& RenderHandle() = 0;

	// Render baby!
	virtual const Model* GetModel() const = 0;
	virtual int DrawModel(int flags, const RenderableInstance& instance) = 0;

	// Get the body parameter
	virtual int GetBody() = 0;

	// Determine the color modulation amount
	virtual void	GetColorModulation(float* color) = 0;

	// Returns false if the entity shouldn't be drawn due to LOD. 
	// (NOTE: This is no longer used/supported, but kept in the vtable for backwards compat)
	virtual bool	LODTest() = 0;

	// Call this to get the current bone transforms for the model.
	// currentTime parameter will affect interpolation
	// nMaxBones specifies how many matrices pBoneToWorldOut can hold. (Should be greater than or
	// equal to studiohdr_t::numbones. Use MAXSTUDIOBONES to be safe.)
	virtual bool	SetupBones(Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;

	virtual void	SetupWeights(const Matrix3x4* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void	DoAnimationEvents(void) = 0;

	// Return this if you want PVS notifications. See IPVSNotify for more info.	
	// Note: you must always return the same value from this function. If you don't,
	// undefined things will occur, and they won't be good.
	virtual PVSNotify* GetPVSNotifyInterface() = 0;

	// Returns the bounds relative to the origin (render bounds)
	virtual void	GetRenderBounds(Vector& mins, Vector& maxs) = 0;

	// returns the bounds as an AABB in worldspace
	virtual void	GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;

	// These normally call through to GetRenderAngles/GetRenderBounds, but some entities custom implement them.
	virtual void	GetShadowRenderBounds(Vector& mins, Vector& maxs, ShadowType shadowType) = 0;

	// Should this object be able to have shadows cast onto it?
	virtual bool	ShouldReceiveProjectedTextures(int flags) = 0;

	// These methods return true if we want a per-renderable shadow cast direction + distance
	virtual bool	GetShadowCastDistance(float* pDist, ShadowType shadowType) const = 0;
	virtual bool	GetShadowCastDirection(Vector* pDirection, ShadowType shadowType) const = 0;

	// Other methods related to shadow rendering
	virtual bool	IsShadowDirty() = 0;
	virtual void	MarkShadowDirty(bool bDirty) = 0;

	// Iteration over shadow hierarchy
	virtual ClientRenderable* GetShadowParent() = 0;
	virtual ClientRenderable* FirstShadowChild() = 0;
	virtual ClientRenderable* NextShadowPeer() = 0;

	// Returns the shadow cast type
	virtual ShadowType ShadowCastType() = 0;

	virtual void Unused2() {}

	// Create/get/destroy model instance
	virtual void CreateModelInstance() = 0;
	virtual unsigned short GetModelInstance() = 0;

	// Returns the transform from RenderOrigin/RenderAngles to world
	virtual const Matrix3x4& RenderableToWorldTransform() = 0;

	// Attachments
	virtual int LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool GetAttachment(int number, Vector& origin, Vector& angles) = 0;
	virtual bool GetAttachment(int number, Matrix3x4& matrix) = 0;
	virtual bool ComputeLightingOrigin(int nAttachmentIndex, Vector modelLightingCenter, const Matrix3x4& matrix, Vector& transformedLightingCenter) = 0;

	// Rendering clip plane, should be 4 floats, return value of NULL indicates a disabled render clip plane
	virtual float* GetRenderClipPlane(void) = 0;

	// Get the skin parameter
	virtual int GetSkin() = 0;

	virtual void	OnThreadedDrawSetup() = 0;

	virtual bool	UsesFlexDelayedWeights() = 0;

	virtual void	RecordToolMessage() = 0;
	virtual bool	ShouldDrawForSplitScreenUser(int nSlot) = 0;

	// NOTE: This is used by renderables to override the default alpha modulation,
	// not including fades, for a renderable. The alpha passed to the function
	// is the alpha computed based on the current renderfx.
	virtual uint8_t OverrideAlphaModulation(uint8_t nAlpha) = 0;

	// NOTE: This is used by renderables to override the default alpha modulation,
	// not including fades, for a renderable's shadow. The alpha passed to the function
	// is the alpha computed based on the current renderfx + any override
	// computed in OverrideAlphaModulation
	virtual uint8_t OverrideShadowAlphaModulation(uint8_t nAlpha) = 0;

	virtual ClientModelRenderable* GetClientModelRenderable() = 0;
};