#pragma once
#include "box2d_shape_segment.h"
#include <godot_cpp/variant/vector2.hpp>

class Box2DShapeWorldBoundary : public Box2DShapeSegment {
	Vector2 normal;
	real_t distance;

public:
	virtual void set_data(const Variant &p_data) override;
	virtual Variant get_data() const override;
	virtual int get_b2Shape_count(bool is_static) const override { return 1; };
	virtual b2Shape *_get_transformed_b2Shape(ShapeInfo shape_info, Box2DCollisionObject *body) override;

	Box2DShapeWorldBoundary() { type = PhysicsServer2D::SHAPE_WORLD_BOUNDARY; }
	~Box2DShapeWorldBoundary() {}
};
