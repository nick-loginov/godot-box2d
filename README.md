![Box2D Logo](box2d_icon.svg)

# Godot Box2D
[![🔗 Build Status](https://github.com/godot-box2d/godot-box2d/actions/workflows/runner.yml/badge.svg)](https://github.com/godot-box2d/godot-box2d/actions/workflows/runner.yml)

A [Box2D](https://github.com/erincatto/box2d) physics server for [Godot Engine](https://github.com/godotengine/godot) 4.1, implemented as a GDExtension.

[Box2D](https://github.com/erincatto/box2d) is a 2D physics engine for games made by [Erin Catto](https://box2d.org).

## Determinism

Box2D is binary deterministic, but doesn't make any guaratee as for cross platform determinism.
Godot Box2D should also be binary deterministic, however no such tests were run yet.

When Box2C gets released, that will be one of this repo's goals to make it cross platform deterministic (from what I understand, it should be just the cos and sin functions that are not cross determinstic in Box2D).

## Limitations

- Having non symetrical physics mask/layers results in no collision. Eg. if we had the following:

|object|mask|category|
|---|---|---|
|object A|1|2|
|object B|2|2|

       In godot would result a collision, but would be very weird, as only one of the objects would receive collision restution.

- Shape scaling and skewing:
  - Circles and capsules only support uniform scaling and don't support skewing

## Install

### From Godot Asset Store

[Godot Asset Library](https://godotengine.org/asset-library/asset/2007)

### From Github Releases

1. Download from [Github Releases](https://github.com/godot-box2d/godot-box2d/releases/latest) the file called `godot-box2d.zip`.
2. Extract the ZIP archive and move the `addons/` folder it contains into your project folder.
3. Open your project settings.
4. Make sure `Advanced Settings` is enabled.
5. Go to `Physics` and then `2D`.
6. Change `Physics Engine` to `Box2D`.
7. Restart Godot.

## Implementation Progress

Currently pass rate of [Godot-Physics-Tests](https://github.com/fabriceci/Godot-Physics-Tests):

Test Count|Pass Status|Category|Notes|Test Names|
--|--|--|--|--|
132|PASS|All|
4|VERY CLOSE|RigidBody2D CCD|There is one line that causes it to fail for another reason. https://github.com/godot-box2d/godot-box2d/issues/29.|testing Continuous Collision Detection (CCD)
1|VERY CLOSE|RigidBody2D Collision Stability|If I increase the collision boundary to 3 pixels, test passes. Could be chance that godot physics test passes.| testing if 450 rectangles can be handled before instablity
2|VERY CLOSE|RigidBody2D Sleep|* All bodies are asleep after 3.5 seconds, while in Godot after 2s. Sleep time is not configurable in box2d|*testing [contact_monitor] > The body sleep and *testing the stability with a pyramid [tolerance (2.50, 0.00)] > All body are sleep
3|VERY CLOSE|RigidBody2D Torque|Final values are very close to  Godot Physics. https://github.com/godot-box2d/godot-box2d/issues/28|* Constant torque is applied, *The impulse torque is applied to the angular velocity and *The impulse torque makes the body rotate correctly
1|FAIL|CharacterBody2D|Fail for snapping to floor. https://github.com/godot-box2d/godot-box2d/issues/11
5|FAIL|Sync to Physics|https://github.com/godot-box2d/godot-box2d/issues/7|*Sync to Physics
2|FAIL|CollisionShape One Way| https://github.com/godot-box2d/godot-box2d/issues/27|*Only collide if the platform rotation > 180°
142|PASS + VERY CLOSE|All|
8|FAIL|All|

Performance Tests, before simulation goes below 30fps:

Shape Type|Max Bodies Box2D|Max Bodies GodotPhysics2D|
--|--|--|
Capsule|1120|2300|
Concave|640|820|
Circles|4600|2980|
Concave|1940|1920|
Rectangle|2560|2080|

NOTE: the simulation for box2d goes slower (eg. 30 fps), while for godot physics it goes completely unstable (eg. when it drops to 30 fps, even much before that).

## Building from source

1. Clone the git repository, including its submodules.

2. Open a terminal application and change its working directory to the `godot-box2d` git repository.

3. Compile `godot-cpp` for the desired `target` (`template_debug` or `template_release`):

       cd godot-cpp
       scons target=template_debug generate_bindings=yes

4. Compile the GDExtension for the same `target` as above:

       cd ..
       scons target=template_debug generate_bindings=no

*Note*: The `template_debug` target can also be loaded in the Godot editor.

## Lint

Run `scripts/clang-tidy.sh` in order to lint.

## Credits

Based of [rburing/physics_server_box2d](https://github.com/rburing/physics_server_box2d). Many thanks to you for starting implementation on this!
