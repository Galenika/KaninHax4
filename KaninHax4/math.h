#pragma once
#include "pch.h"
#include "vector3.h"

#define pi (3.14159265359)
#define radpi (57.2957795131)
#define degrees_to_radians(x) (x / radpi)
#define radians_to_degrees(x) (x * radpi)

float normalize_angle(float angle) {
	while (angle > 180.f)
		angle -= 360.f;
	while (angle < -180.f)
		angle += 360.f;
	return angle;
}

vector3_t clamp_angles(vector3_t angle) {
	angle.y = normalize_angle(angle.y);

	if (angle.y > 179.9f)
		angle.y = 179.9f;
	if (angle.y < -179.9f)
		angle.y = -179.9f;

	if (angle.x > 89.f)
		angle.x = 89.f;
	if (angle.x < -89.f)
		angle.x = -89.f;
	return angle;
}

float clamp_angle_x(float angle) {
	if (angle > 89.f)
		angle = 89.f;
	if (angle < -89.f)
		angle = -89.f;
	return angle;
}

float clamp_angle_y(float angle) {
	angle = normalize_angle(angle);

	if (angle > 179.9f)
		angle = 179.9f;
	if (angle < -179.9f)
		angle = -179.9f;

	return angle;
}

double get_3d_distance(vector3_t vec1, vector3_t vec2) {
	return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2) + pow(vec1.z - vec2.z, 2));
}

double get_2d_distance(vector2_t vec1, vector2_t vec2) {
	return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}

vector3_t calc_angle_3d(vector3_t source_pos, vector3_t destination_pos) {
	vector3_t delta = source_pos - destination_pos;
	double xy_hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	vector3_t angles = vector3_t(float(atanf(delta.z / xy_hyp) * radpi), float(atanf(delta.y / delta.x) * radpi), 0.f);

	if (delta.x > 0.f)
		angles.y += 180.f;

	return clamp_angles(angles);
}

float calc_angle_2d(vector2_t source_pos, vector2_t destination_pos) {
	vector2_t delta = source_pos - destination_pos;
	float angle = atanf(delta.y / delta.x) * radpi;

	if (delta.x > 0.f)
		angle += 180.f;

	return clamp_angle_y(angle);
}

vector3_t vector3_lerp(vector3_t source, vector3_t destination, double t_percent) {
	if (t_percent < 1)
		t_percent = 100;
	return clamp_angles((((destination - source) / 100) * t_percent) + source);
}

void rotate_point(vector2_t& _point, float _angle) {}

inline void angle_vectors(const vector3_t angles, vector3_t& forward) {
	float sp, sy, cp, cy;
	sy = sin(degrees_to_radians(angles.y));
	cy = cos(degrees_to_radians(angles.y));

	sp = sin(degrees_to_radians(angles.x));
	cp = cos(degrees_to_radians(angles.x));

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

inline void angle_vectors(const vector3_t angles, vector3_t& forward, vector3_t& right, vector3_t& up) {
	float sp, sy, sr, cp, cy, cr;

	sy = sin(degrees_to_radians(angles.y));
	cy = cos(degrees_to_radians(angles.y));
	sp = sin(degrees_to_radians(angles.x));
	cp = cos(degrees_to_radians(angles.x));
	sr = sin(degrees_to_radians(angles.z));
	cr = cos(degrees_to_radians(angles.z));

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;

	right.x = -1 * sr * sp * cy + -1 * cr * -sy;
	right.y = -1 * sr * sp * sy + -1 * cr * cy;
	right.z = -1 * sr * cp;

	up.x = cr * sp * cy + -sr * -sy;
	up.y = cr * sp * sy + -sr * cy;
	up.z = cr * cp;
}

float get_distance_to_angles(vector3_t source, vector3_t destination) {
	destination.y += 180.f;
	source.y += 180.f;
	float diff = max(destination.y, source.y) - min(destination.y, source.y);
	if (diff > 180.f)
		diff = 360.f - diff;

	return sqrt(pow(diff, 2) + pow(destination.x - source.x, 2));
}

float get_distance_to_angle(float source, float angle) {
	source += 180.f;
	angle += 180.f;

	float diff = max(angle, source) - min(angle, source);
	if (diff > 180.f)
		diff = 360.f - diff;

	return diff;
}

inline float dot_product(const vector3_t& a, const vector3_t& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
