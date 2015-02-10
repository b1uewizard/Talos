// ========================================================================= //
// * Engine
// Copyright (C) 2015 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Jordan Sparks <unixunited@live.com> January 2015.
// ========================================================================= //
// File: DynamicLines.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ========================================================================= //
// Defines DynamicLines class.
// ========================================================================= //

#ifndef __DYNAMICLINES_HPP__
#define __DYNAMICLINES_HPP__

// ========================================================================= //

#include "DynamicRenderable.hpp"

// ========================================================================= //
// Draws lines dynamically using hardware buffers.
class DynamicLines : public DynamicRenderable
{
public:
	// Calls init, sets material, flags as dirty.
	explicit DynamicLines(const Ogre::RenderOperation::OperationType =
						  Ogre::RenderOperation::OT_LINE_STRIP);

	// Empty destructor.
	virtual ~DynamicLines(void) override;

	// Adds a point to the list.
	void addPoint(const Ogre::Vector3&);

	// Adds a point to the list.
	void addPoint(const Ogre::Real, const Ogre::Real, const Ogre::Real);

	// Changes location of an existing point.
	void setPoint(const unsigned short index, const Ogre::Vector3&);

	// Removes all points from the point list.
	void clear(void);

	// Updates the hardware buffer after making changes.
	void update(void);

	// Getters:

	// Returns number of points in list.
	const unsigned short getNumPoints(void) const;

	// Returns current operation type for drawing.
	const Ogre::RenderOperation::OperationType getOperationType(void) const;

	// Setters:

	// Sets the type of operation to draw with.
	void setOperationType(const Ogre::RenderOperation::OperationType);

protected:
	// Implements DynamicRenderable's function, creates a simple vertex-only
	// declaration.
	virtual void createVertexDeclaration(void) override;

	// Implements DynamicRenderable's function, pushes point list out to 
	// hardware memory.
	virtual void fillHardwareBuffers(void) override;

private:
	std::vector<Ogre::Vector3> m_points;
	bool m_dirty;
};

// ========================================================================= //

// Getters:

inline const unsigned short DynamicLines::getNumPoints(void) const{
	return static_cast<unsigned short>(m_points.size());
}

inline const Ogre::RenderOperation::OperationType 
	DynamicLines::getOperationType(void) const{
	return mRenderOp.operationType;
}

// Setters:

inline void DynamicLines::setOperationType(
	const Ogre::RenderOperation::OperationType type){
	mRenderOp.operationType = type;
}

// ========================================================================= //

#endif

// ========================================================================= //