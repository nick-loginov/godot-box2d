#include "physics_server_box2d.h"

#include <godot_cpp/core/class_db.hpp>

/* SHAPE API */

RID PhysicsServerBox2D::_shape_create(ShapeType p_shape) {
	Box2DShape *shape = nullptr;
	switch (p_shape) {
		case SHAPE_RECTANGLE: {
			shape = memnew(Box2DShapeRectangle);
		}
	}

	RID id = shape_owner.make_rid(shape);
	shape->set_self(id);

	return id;
}

RID PhysicsServerBox2D::_rectangle_shape_create() {
	return _shape_create(SHAPE_RECTANGLE);
}

void PhysicsServerBox2D::_shape_set_data(const RID &p_shape, const Variant &p_data) {
	Box2DShape *shape = shape_owner.get_or_null(p_shape);
	ERR_FAIL_COND(!shape);
	shape->set_data(p_data);
};

Variant PhysicsServerBox2D::_shape_get_data(const RID &p_shape) const {
	const Box2DShape *shape = shape_owner.get_or_null(p_shape);
	ERR_FAIL_COND_V(!shape, Variant());
	ERR_FAIL_COND_V(!shape->is_configured(), Variant());
	return shape->get_data();
};

/* SPACE API */

RID PhysicsServerBox2D::_space_create() {
	Box2DSpace *space = memnew(Box2DSpace);
	RID id = space_owner.make_rid(space);
	space->set_self(id);
	// TODO: create area
	return id;
}

void PhysicsServerBox2D::_space_set_active(const RID &p_space, bool p_active) {
	Box2DSpace *space = space_owner.get_or_null(p_space);
	ERR_FAIL_COND(!space);
	if (p_active) {
		active_spaces.insert(space);
	} else {
		active_spaces.erase(space);
	}
}

bool PhysicsServerBox2D::_space_is_active(const RID &p_space) const {
	const Box2DSpace *space = space_owner.get_or_null(p_space);
	ERR_FAIL_COND_V(!space, false);

	return active_spaces.has(space);
}

/* BODY API */

RID PhysicsServerBox2D::_body_create() {
	Box2DBody *body = memnew(Box2DBody);
	RID rid = body_owner.make_rid(body);
	body->set_self(rid);
	return rid;
}

void PhysicsServerBox2D::_body_set_space(const RID &p_body, const RID &p_space) {
	Box2DBody *body = body_owner.get_or_null(p_body);
	ERR_FAIL_COND(!body);
	Box2DSpace *space = nullptr;
	if (p_space.is_valid()) {
		space = space_owner.get_or_null(p_space);
		ERR_FAIL_COND(!space);
	}

	if (body->get_space() == space) {
		return; //pointless
	}

	//body->clear_constraint_list();
	body->set_space(space);
}

RID PhysicsServerBox2D::_body_get_space(const RID &p_body) const {
	Box2DBody *body = body_owner.get_or_null(p_body);
	ERR_FAIL_COND_V(!body, RID());

	Box2DSpace *space = body->get_space();
	if (!space) {
		return RID();
	}
	return space->get_self();
}

/* MISC */

void PhysicsServerBox2D::_free_rid(const RID &p_rid) {
	if (shape_owner.owns(p_rid)) {
		Box2DShape *shape = shape_owner.get_or_null(p_rid);

		// TODO: remove from owners?

		shape_owner.free(p_rid);
		memdelete(shape);
	}
	else if (body_owner.owns(p_rid)) {
		Box2DBody *body = body_owner.get_or_null(p_rid);

		body_set_space(p_rid, RID());

		// TODO: remove shapes

		body_owner.free(p_rid);
		memdelete(body);
	}
	else if (space_owner.owns(p_rid)) {
		Box2DSpace *space = space_owner.get_or_null(p_rid);
		// TODO: handle objects, area
		active_spaces.erase(space);
		space_owner.free(p_rid);
		memdelete(space);
	}
}

void PhysicsServerBox2D::_set_active(bool p_active) {
	active = p_active;
}

void PhysicsServerBox2D::_init() {
}

void PhysicsServerBox2D::_step(double p_step) {
	if (!active) {
		return;
	}
	for (const Box2DSpace *E : active_spaces) {
		// TODO: step
	}
}

void PhysicsServerBox2D::_sync() {
}

void PhysicsServerBox2D::_end_sync() {
}

void PhysicsServerBox2D::_finish() {
}

PhysicsServerBox2D::PhysicsServerBox2D() {
}

PhysicsServerBox2D::~PhysicsServerBox2D() {
}