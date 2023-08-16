#pragma once
#include "HandleEntity.h"
#include "../data/Vector.h"
#include "ClientUnknown.h"
#include "../interfaces/EngineTrace.h"

struct Model;

enum SolidType
{
	SOLID_NONE = 0,	// no solid model
	SOLID_BSP = 1,	// a BSP tree
	SOLID_BBOX = 2,	// an AABB
	SOLID_OBB = 3,	// an OBB (not implemented yet)
	SOLID_OBB_YAW = 4,	// an OBB, constrained so that it can only yaw
	SOLID_CUSTOM = 5,	// Always call into the entity for tests
	SOLID_VPHYSICS = 6,	// solid vphysics object, get vcollide from the model and collide with that
	SOLID_LAST,
};

class Collideable
{
public:
	// Gets at the entity handle associated with the collideable
	virtual HandleEntity* GetEntityHandle() = 0;

	// These methods return the bounds of an OBB measured in "collision" space
	// which can be retreived through the CollisionToWorldTransform or
	// GetCollisionOrigin/GetCollisionAngles methods
	virtual const Vector& OBBMins() const = 0;
	virtual const Vector& OBBMaxs() const = 0;

	// Returns the bounds of a world-space box used when the collideable is being traced
	// against as a trigger. It's only valid to call these methods if the solid flags
	// have the FSOLID_USE_TRIGGER_BOUNDS flag set.
	virtual void WorldSpaceTriggerBounds(Vector* pVecWorldMins, Vector* pVecWorldMaxs) const = 0;

	// custom collision test
	virtual bool TestCollision(const Ray& ray, unsigned int fContentsMask, Trace& tr) = 0;

	// Perform hitbox test, returns true *if hitboxes were tested at all*!!
	virtual bool TestHitboxes(const Ray& ray, unsigned int fContentsMask, Trace& tr) = 0;

	// Returns the BRUSH model index if this is a brush model. Otherwise, returns -1.
	virtual int GetCollisionModelIndex() = 0;

	// Return the model, if it's a studio model.
	virtual const Model* GetCollisionModel() = 0;

	// Get angles and origin.
	virtual const Vector& GetCollisionOrigin() const = 0;
	virtual const Vector& GetCollisionAngles() const = 0;
	virtual const Matrix3x4& CollisionToWorldTransform() const = 0;

	// Return a SOLID_ define.
	virtual SolidType GetSolid() const = 0;
	virtual int GetSolidFlags() const = 0;

	// Gets at the containing class...
	virtual ClientUnknown* GetIClientUnknown() = 0;

	// We can filter out collisions based on collision group
	virtual int GetCollisionGroup() const = 0;

	// Returns a world-aligned box guaranteed to surround *everything* in the collision representation
	// Note that this will surround hitboxes, trigger bounds, physics.
	// It may or may not be a tight-fitting box and its volume may suddenly change
	virtual void WorldSpaceSurroundingBounds(Vector* pVecMins, Vector* pVecMaxs) = 0;

	virtual unsigned int GetRequiredTriggerFlags() const = 0;

	// returns NULL unless this collideable has specified FSOLID_ROOT_PARENT_ALIGNED
	virtual const Matrix3x4* GetRootParentToWorldTransform() const = 0;
	virtual void* GetVPhysicsObject() const = 0; // TODO rework as IPhysicsObject*
};