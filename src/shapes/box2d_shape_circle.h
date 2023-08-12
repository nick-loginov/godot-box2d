#pragma once
#include "box2d_shape.h"

using namespace godot;

class Box2DShapeCircle : public Box2DShape {
	real_t radius = 0.0;

public:
	virtual void set_data(const Variant &p_data) override;
	virtual Variant get_data() const override;
	virtual int get_b2Shape_count(bool is_static) const override { return 1; };
	virtual b2Shape *_get_transformed_b2Shape(ShapeInfo shape_info, Box2DCollisionObject *body) override;

	Box2DShapeCircle() { type = PhysicsServer2D::SHAPE_CIRCLE; }
	~Box2DShapeCircle(){};
};
