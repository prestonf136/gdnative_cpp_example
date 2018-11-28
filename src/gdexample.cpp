#include "gdexample.h"

using namespace godot;

void gdexample::_register_methods() {
	register_method("_process", &gdexample::_process);
	register_property<gdexample, float>("amplitude", &gdexample::amplitude, 10.0);
	register_property<gdexample, float>("speed", &gdexample::set_speed, &gdexample::get_speed, 1.0);

	Dictionary args;
	args["node"] = Variant::OBJECT;
	args["new_pos"] = Variant::VECTOR2;
	register_signal<gdexample>((char *)"position_changed", args);
}

gdexample::gdexample() {
}

gdexample::~gdexample() {
	// add your cleanup here
}

void gdexample::_init() {
	// initialize any variables here
	time_passed = 0.0;
	amplitude = 10.0;
	speed = 1.0;
}

void gdexample::_process(float delta) {
	time_passed += speed * delta;

	Vector2 new_position = Vector2(
		amplitude + (amplitude * sin(time_passed * 2.0)),
		amplitude + (amplitude * cos(time_passed * 1.5))
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0) {
		Array args;
		args.push_back(this);
		args.push_back(new_position);
		emit_signal("position_changed", args);

		time_emit = 0.0;
	}
}

void gdexample::set_speed(float p_speed) {
	speed = p_speed;
}

float gdexample::get_speed() {
	return speed;
}
