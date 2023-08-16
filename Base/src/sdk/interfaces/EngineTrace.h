#pragma once
#include "../data/Vector.h"
#include "../data/Matrix.h"
#include "../entity/Entity.h"

#define CONTENTS_EMPTY					0
#define CONTENTS_SOLID					0x1
#define CONTENTS_WINDOW					0x2
#define CONTENTS_AUX					0x4
#define CONTENTS_GRATE					0x8
#define CONTENTS_SLIME					0x10
#define CONTENTS_WATER					0x20
#define CONTENTS_BLOCKLOS				0x40
#define CONTENTS_OPAQUE					0x80
#define CONTENTS_TESTFOGVOLUM			0x100
#define CONTENTS_UNUSED					0x200
#define CONTENTS_BLOCKLIGHT				0x400
#define CONTENTS_TEAM1					0x800
#define CONTENTS_TEAM2					0x1000
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000
#define CONTENTS_MOVEABLE				0x4000
#define CONTENTS_AREAPORTAL				0x8000
#define CONTENTS_PLAYERCLIP				0x10000
#define CONTENTS_MONSTERCLIP			0x20000
#define CONTENTS_CURRENT_0				0x40000
#define CONTENTS_CURRENT_90				0x80000
#define CONTENTS_CURRENT_180			0x100000
#define CONTENTS_CURRENT_270			0x200000
#define CONTENTS_CURRENT_UP				0x400000
#define CONTENTS_CURRENT_DOWN			0x800000
#define CONTENTS_ORIGIN					0x1000000
#define CONTENTS_MONSTER				0x2000000
#define CONTENTS_DEBRIS					0x4000000
#define CONTENTS_DETAIL					0x8000000
#define CONTENTS_TRANSLUCENT			0x10000000
#define CONTENTS_LADDER					0x20000000
#define CONTENTS_HITBOX					0x40000000
#define LAST_VISIBLE_CONTENTS			CONTENTS_OPAQUE
#define ALL_VISIBLE_CONTENTS			(LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define SURF_LIGHT						0x0001
#define SURF_SKY2D						0x0002
#define SURF_SKY						0x0004
#define SURF_WARP						0x0008
#define SURF_TRANS						0x0010
#define SURF_NOPORTAL					0x0020
#define SURF_TRIGGER					0x0040
#define SURF_NODRAW						0x0080
#define SURF_HINT						0x0100
#define SURF_SKIP						0x0200
#define SURF_NOLIGHT					0x0400
#define SURF_BUMPLIGHT					0x0800
#define SURF_NOSHADOWS					0x1000
#define SURF_NODECALS					0x2000
#define SURF_NOCHOP						0x4000
#define SURF_HITBOX						0x8000

#define MASK_ALL						(0xFFFFFFFF)
#define MASK_SOLID						(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_PLAYERSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCSOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCFLUID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_WATER						(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define MASK_OPAQUE						(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS			(MASK_OPAQUE|CONTENTS_MONSTER)
#define MASK_BLOCKLOS					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS			(MASK_BLOCKLOS|CONTENTS_MONSTER)
#define MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS			(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_SHOT						(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_BRUSHONLY				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define MASK_SHOT_HULL					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC				(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC_FLUID		(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define MASK_SPLITAREAPORTAL			(CONTENTS_WATER|CONTENTS_SLIME)
#define MASK_CURRENT					(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define MASK_DEADSOLID					(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)


#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)
#define DISPSURF_FLAG_SURFPROP3		(1<<5)
#define DISPSURF_FLAG_SURFPROP4		(1<<6)

struct Ray
{
	VectorAligned  m_Start;	// starting point, centered within the extents
	VectorAligned  m_Delta;	// direction + length of the ray
	VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
	const Matrix3x4* m_pWorldAxisTransform;
	bool	m_IsRay;	// are the extents zero?
	bool	m_IsSwept;	// is delta != 0?

	Ray() : m_pWorldAxisTransform(NULL) {}

	Ray(Vector const& start, Vector const& end) :
		m_Start(start), m_Delta(end - start)
	{
		this->m_IsSwept = (m_Delta.LengthSqr() != 0);
		this->m_pWorldAxisTransform = NULL;
		this->m_IsRay = true;
	}

	Ray(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs) :
		m_Start(start), m_Delta(end - start)
	{
		this->m_IsSwept = (m_Delta.LengthSqr() != 0);
		this->m_pWorldAxisTransform = NULL;

		this->m_Extents = maxs - mins;
		this->m_Extents *= 0.5f;

		this->m_IsRay = (this->m_Extents.LengthSqr() < 1e-6);

		if (this->m_Extents.x >= 0 && this->m_Extents.y >= 0 && this->m_Extents.z >= 0)
		{
			this->m_StartOffset = mins + maxs;
			this->m_StartOffset += 0.5f;
			this->m_Start = this->m_StartOffset + start;
			this->m_StartOffset *= -1.f;
		}
	}

	// compute inverse delta
	Vector InvDelta() const
	{
		Vector invDelta;
		for (int axis = 0; axis < 3; ++axis)
		{
			if (m_Delta[axis] != 0.0f)
			{
				invDelta[axis] = 1.0f / m_Delta[axis];
			}
			else
			{
				invDelta[axis] = FLT_MAX;
			}
		}
		return invDelta;
	}
};

struct CPlane
{
	Vector normal;
	float distance;
	std::byte type;
	std::byte signBits;
	std::byte pad[0x2];
};

struct CSurface
{
	const char* name;
	short surfaceProps;
	std::uint16_t flags;
};

class BaseTrace
{
public:

	// Displacement flags tests.
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }
	bool IsDispSurfaceProp3(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP3) != 0); }
	bool IsDispSurfaceProp4(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP4) != 0); }

public:

	// these members are aligned!!
	Vector startpos;				// start position
	Vector endpos;					// final position
	CPlane plane;					// surface normal at impact

	float fraction;				// time completed, 1.0 = didn't hit anything

	int contents;				// contents on other side of surface hit
	unsigned short dispFlags;				// displacement flags for marking surfaces with data

	bool allsolid;				// if true, plane is not valid
	bool startsolid;				// if true, the initial point was in a solid area

	BaseTrace() {}

private:
	// No copy constructors allowed
	BaseTrace(const BaseTrace& vOther);
};

class Trace : public BaseTrace
{
public:
	// Gets the entity's network index if the trace has hit an entity.
	// If not, returns -1.
	inline int GetEntityIndex() const
	{
		if (entity)
			return entity->entindex();
		else
			return -1;
	}

	// Returns true if there was any kind of impact at all
	inline bool DidHit() const
	{
		return fraction < 1.f || allsolid || startsolid;
	}

	inline bool IsVisible() const
	{
		return (fraction > 0.97f);
	}


public:

	float fractionleftsolid;	// time we left a solid, only valid if we started in solid
	CSurface surface;			// surface hit (impact surface)

	int hitgroup;			// 0 == generic, non-zero is specific body part

	short physicsbone;		// physics bone hit by trace in studio
	unsigned short worldSurfaceIndex;	// Index of the msurface2_t, if applicable

	BaseEntity* entity;

	// NOTE: this member is overloaded.
	// If entity points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int hitbox;					// box hit by trace in studio

	Trace() : entity(NULL) {}

private:
	// No copy constructors allowed
	Trace(const Trace& other);
};