#include "minirt_base.h"

minirt_transform minirt_transform_scale(minirt_scale scale) {
	return (minirt_transform){ .x = { scale.x, 0, 0, 0 },
							   .y = { 0, scale.y, 0, 0 },
							   .z = { 0, 0, scale.z, 0 },
							   .w = { 0, 0, 0, 1 } };
}

minirt_transform minirt_transform_rotate(minirt_rotation r) {
	minirt_transform yaw = minirt_transform_rotate_yaw(r.yaw);
	minirt_transform pitch = minirt_transform_rotate_pitch(r.pitch);
	minirt_transform roll = minirt_transform_rotate_roll(r.roll);
	minirt_transform yaw_and_pitch = minirt_compose(pitch, yaw);
	minirt_transform result = minirt_compose(roll, yaw_and_pitch);
	return result;
}

minirt_transform minirt_transform_rotate_yaw(minirt_f yaw) {
	minirt_f c = minirt_f_cos(yaw);
	minirt_f s = minirt_f_sin(yaw);
	return (minirt_transform){ .x = { c, -s, 0, 0 },
							   .y = { s, c, 0, 0 },
							   .z = { 0, 0, 1, 0 },
							   .w = { 0, 0, 0, 1 } };
}

minirt_transform minirt_transform_rotate_pitch(minirt_f pitch) {
	minirt_f c = minirt_f_cos(pitch);
	minirt_f s = minirt_f_sin(pitch);
	return (minirt_transform){ .x = { c, 0, s, 0 },
							   .y = { 0, 1, 0, 0 },
							   .z = { -s, 0, c, 0 },
							   .w = { 0, 0, 0, 1 } };
}

minirt_transform minirt_transform_rotate_roll(minirt_f roll) {
	minirt_f c = minirt_f_cos(roll);
	minirt_f s = minirt_f_sin(roll);
	return (minirt_transform){ .x = { 1, 0, 0, 0 },
							   .y = { 0, c, -s, 0 },
							   .z = { 0, s, c, 0 },
							   .w = { 0, 0, 0, 1 } };
}

minirt_transform minirt_transform_translate(minirt_distance distance) {
	return (minirt_transform){ .x = { 1, 0, 0, distance.x },
							   .y = { 0, 1, 0, distance.y },
							   .z = { 0, 0, 1, distance.z },
							   .w = { 0, 0, 0, 1 } };
}

minirt_transform minirt_compose(minirt_transform a, minirt_transform b) {
	minirt_transform result;

	result.x.x = a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x;
	result.x.y = a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y;
	result.x.z = a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.w.z;
	result.x.w = a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.w.w;

	result.y.x = a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x;
	result.y.y = a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y;
	result.y.z = a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.w.z;
	result.y.w = a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.w.w;

	result.z.x = a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.w.x;
	result.z.y = a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.w.y;
	result.z.z = a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.w.z;
	result.z.w = a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.w.w;

	result.w.x = a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x + a.w.w * b.w.x;
	result.w.y = a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y + a.w.w * b.w.y;
	result.w.z = a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z + a.w.w * b.w.z;
	result.w.w = a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w + a.w.w * b.w.w;

	return result;
}
