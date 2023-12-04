#include "minirt_base.h"

minirt_color_hdr minirt_color_multiply(minirt_color_hdr h, minirt_color_ldr l) {
	return (minirt_color_hdr){ .red = h.red * l.red,
							   .green = h.green * l.green,
							   .blue = h.blue * l.blue };
}

minirt_rotation minirt_rotation_multiply(minirt_rotation r, minirt_f f) {
	return (minirt_rotation){ .roll = r.roll * f,
							  .pitch = r.pitch * f,
							  .yaw = r.yaw * f };
}

minirt_scale minirt_scale_multiply(minirt_scale s1, minirt_scale s2) {
	return (
		minirt_scale){ .x = s1.x * s2.x, .y = s1.y * s2.y, .z = s1.z * s2.z };
}

minirt_position minirt_move(minirt_position p, minirt_distance d) {
	return (minirt_position){ .x = p.x + d.x, .y = p.y + d.y, .z = p.z + d.z };
}

minirt_position minirt_rotate_position(minirt_position p, minirt_rotation r) {
	minirt_f c_yaw = minirt_f_cos(r.yaw);
	minirt_f s_yaw = minirt_f_sin(r.yaw);
	minirt_f c_pitch = minirt_f_cos(r.pitch);
	minirt_f s_pitch = minirt_f_sin(r.pitch);
	minirt_f c_roll = minirt_f_cos(r.roll);
	minirt_f s_roll = minirt_f_sin(r.roll);

	minirt_position temp1 = { .x = p.x * c_yaw - p.y * s_yaw,
							  .y = p.x * s_yaw + p.y * c_yaw,
							  .z = p.z };

	minirt_position temp2 = { .x = temp1.x * c_pitch + temp1.z * s_pitch,
							  .y = temp1.y,
							  .z = -temp1.x * s_pitch + temp1.z * c_pitch };

	minirt_position rotated = { .x = temp2.x,
								.y = temp2.y * c_roll - temp2.z * s_roll,
								.z = temp2.y * s_roll + temp2.z * c_roll };

	return rotated;
}

minirt_position minirt_rotate_from(
	minirt_position p,
	minirt_position center,
	minirt_rotation r) {
	minirt_position moved = minirt_move(
		p, (minirt_distance){ .x = -center.x, .y = -center.y, .z = -center.z });
	minirt_position rotated = minirt_rotate_position(moved, r);
	minirt_position result = minirt_move(
		rotated,
		(minirt_distance){ .x = -center.x, .y = -center.y, .z = -center.z });
	return result;
}

minirt_distance minirt_rotate_distance(minirt_distance d, minirt_rotation r) {
	minirt_f c_yaw = minirt_f_cos(r.yaw);
	minirt_f s_yaw = minirt_f_sin(r.yaw);
	minirt_f c_pitch = minirt_f_cos(r.pitch);
	minirt_f s_pitch = minirt_f_sin(r.pitch);
	minirt_f c_roll = minirt_f_cos(r.roll);
	minirt_f s_roll = minirt_f_sin(r.roll);

	minirt_distance temp1 = { .x = d.x * c_yaw - d.y * s_yaw,
							  .y = d.x * s_yaw + d.y * c_yaw,
							  .z = d.z };

	minirt_distance temp2 = { .x = temp1.x * c_pitch + temp1.z * s_pitch,
							  .y = temp1.y,
							  .z = -temp1.x * s_pitch + temp1.z * c_pitch };

	minirt_distance rotated = { .x = temp2.x,
								.y = temp2.y * c_roll - temp2.z * s_roll,
								.z = temp2.y * s_roll + temp2.z * c_roll };

	return rotated;
}

minirt_distance minirt_distance_scale(minirt_distance d, minirt_scale s) {
	return (minirt_distance){ .x = d.x * s.x, .y = d.y * s.y, .z = d.z * s.z };
}

minirt_distance minirt_distance_from(minirt_position from, minirt_position to) {
	return (minirt_distance){ .x = to.x - from.x,
							  .y = to.y - from.y,
							  .z = to.z - from.z };
}

minirt_distance minirt_direction_multiply(minirt_direction d, minirt_scale s) {
	return (minirt_distance){ .x = d.x * s.x, .y = d.y * s.y, .z = d.z * s.z };
}

minirt_distance minirt_difference(minirt_distance a, minirt_distance b) {
	return (minirt_distance){ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
}

minirt_distance minirt_reverse_distance(minirt_distance d) {
	return (minirt_distance){ .x = -d.x, .y = -d.y, .z = -d.z };
}

minirt_direction minirt_normalize(minirt_position p) {
	minirt_f length = minirt_f_sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	return (minirt_direction){ .x = p.x / length,
							   .y = p.y / length,
							   .z = p.z / length };
}

// TODO:
minirt_direction
	minirt_rotate_direction(minirt_direction d, minirt_rotation r) {
	minirt_f c_yaw = minirt_f_cos(r.yaw);
	minirt_f s_yaw = minirt_f_sin(r.yaw);
	minirt_f c_pitch = minirt_f_cos(r.pitch);
	minirt_f s_pitch = minirt_f_sin(r.pitch);
	minirt_f c_roll = minirt_f_cos(r.roll);
	minirt_f s_roll = minirt_f_sin(r.roll);

	minirt_direction temp1 = { .x = d.x * c_yaw - d.y * s_yaw,
							   .y = d.x * s_yaw + d.y * c_yaw,
							   .z = d.z };

	minirt_direction temp2 = { .x = temp1.x * c_pitch + temp1.z * s_pitch,
							   .y = temp1.y,
							   .z = -temp1.x * s_pitch + temp1.z * c_pitch };

	minirt_direction rotated = { .x = temp2.x,
								 .y = temp2.y * c_roll - temp2.z * s_roll,
								 .z = temp2.y * s_roll + temp2.z * c_roll };

	return rotated;
}

minirt_direction minirt_reverse_direction(minirt_direction d) {
	return (minirt_direction){ .x = -d.x, .y = -d.y, .z = -d.z };
}

minirt_f minirt_cos_between(minirt_direction a, minirt_direction b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Matrix
