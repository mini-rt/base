#ifndef MINIRT_BASE_H
#define MINIRT_BASE_H

#include <stddef.h>


#ifndef MINIRT_PRECISION
# define MINIRT_PRECISION 1
#endif

#if MINIRT_PRECISION == 0
typedef _Float16 minirt_f;
#elif MINIRT_PRECISION == 1
typedef float minirt_f;
#elif MINIRT_PRECISION == 2
typedef double minirt_f;
#elif MINIRT_PRECISION == 3
typedef long double minirt_f;
#else
# error Unrecognized MINIRT_PRECISION value
#endif

minirt_f minirt_f_add(minirt_f f1, minirt_f f2);
minirt_f minirt_f_subtract(minirt_f f1, minirt_f f2);
minirt_f minirt_f_multiply(minirt_f f1, minirt_f f2);
minirt_f minirt_f_divide(minirt_f f1, minirt_f f2);
minirt_f minirt_f_pow(minirt_f f, minirt_f exp);
minirt_f minirt_f_log(minirt_f f, minirt_f base);
minirt_f minirt_f_reverse(minirt_f f);
minirt_f minirt_f_sin(minirt_f f);
minirt_f minirt_f_cos(minirt_f f);
minirt_f minirt_f_tan(minirt_f f);
minirt_f minirt_f_cot(minirt_f f);
minirt_f minirt_f_sec(minirt_f f);
minirt_f minirt_f_csc(minirt_f f);
minirt_f minirt_f_sinh(minirt_f f);
minirt_f minirt_f_cosh(minirt_f f);
minirt_f minirt_f_tanh(minirt_f f);
minirt_f minirt_f_coth(minirt_f f);
minirt_f minirt_f_sech(minirt_f f);
minirt_f minirt_f_csch(minirt_f f);
minirt_f minirt_f_asin(minirt_f f);
minirt_f minirt_f_acos(minirt_f f);
minirt_f minirt_f_atan(minirt_f f);
minirt_f minirt_f_acot(minirt_f f);
minirt_f minirt_f_asec(minirt_f f);
minirt_f minirt_f_acsc(minirt_f f);
minirt_f minirt_f_asinh(minirt_f f);
minirt_f minirt_f_acosh(minirt_f f);
minirt_f minirt_f_atanh(minirt_f f);
minirt_f minirt_f_acoth(minirt_f f);
minirt_f minirt_f_asech(minirt_f f);
minirt_f minirt_f_acsch(minirt_f f);


#define MINIRT_STRUCT3(name, x, y, z)                                          \
	typedef struct {                                                           \
		minirt_f x;                                                            \
		minirt_f y;                                                            \
		minirt_f z;                                                            \
	} name;

MINIRT_STRUCT3(minirt_color_ldr, red, green, blue);
MINIRT_STRUCT3(minirt_color_hdr, red, green, blue);
MINIRT_STRUCT3(minirt_rotation, roll, pitch, yaw);
MINIRT_STRUCT3(minirt_scale, x, y, z);
MINIRT_STRUCT3(minirt_position, x, y, z);
MINIRT_STRUCT3(minirt_distance, x, y, z);
MINIRT_STRUCT3(minirt_direction, x, y, z);

#undef MINIRT_STRUCT3

minirt_color_hdr minirt_color_multiply(minirt_color_hdr h, minirt_color_ldr l);
minirt_rotation minirt_rotation_multiply(minirt_rotation r, minirt_f f);
minirt_scale minirt_scale_multiply(minirt_scale s1, minirt_scale s2);
minirt_position minirt_move(minirt_position p, minirt_distance d);
minirt_position minirt_rotate_position(minirt_position p, minirt_rotation r);
minirt_position minirt_rotate_from(
	minirt_position p,
	minirt_position center,
	minirt_rotation r);
minirt_distance minirt_rotate_distance(minirt_distance d, minirt_rotation r);
minirt_distance minirt_distance_scale(minirt_distance d, minirt_scale s);
minirt_distance minirt_distance_from(minirt_position from, minirt_position to);
minirt_distance minirt_direction_multiply(minirt_direction d, minirt_scale s);
minirt_distance minirt_difference(minirt_distance a, minirt_distance b);
minirt_distance minirt_reverse_distance(minirt_distance d);
minirt_direction minirt_normalize(minirt_position p);
minirt_direction minirt_rotate_direction(minirt_direction d, minirt_rotation r);
minirt_direction minirt_reverse_direction(minirt_direction d);
minirt_f minirt_cos_between(minirt_direction a, minirt_direction b);

typedef struct {
	struct {
		minirt_f x, y, z, w;
	} x, y, z, w;
} minirt_transform;

minirt_transform minirt_transform_scale(minirt_scale scale);
minirt_transform minirt_transform_rotate(minirt_rotation rotation);
minirt_transform minirt_transform_rotate_roll(minirt_f roll);
minirt_transform minirt_transform_rotate_pitch(minirt_f pitch);
minirt_transform minirt_transform_rotate_yaw(minirt_f yaw);
minirt_transform minirt_transform_translate(minirt_distance distance);


typedef struct _minirt_point minirt_point;

typedef struct {
	minirt_color_ldr albedo;
	minirt_f roughness;
	minirt_f specular;
	minirt_f metallic;
} minirt_material;

typedef struct _minirt_brdf minirt_brdf;

typedef void (*minirt_brdf_dispose_v)(minirt_brdf *self);

typedef minirt_f (*minirt_brdf_function_v)(
	minirt_brdf *self,
	minirt_direction incident,
	minirt_direction outgoing,
	minirt_direction surface_normal,
	minirt_color_hdr light_color,
	minirt_material material);

typedef struct {
	minirt_brdf_dispose_v dispose;
	minirt_brdf_function_v function;
} minirt_brdf_v;

struct _minirt_brdf {
	const minirt_brdf_v *v;
};

void minirt_brdf_dispose(minirt_brdf *self);

minirt_f minirt_brdf_function(
	minirt_brdf *self,
	minirt_direction incident,
	minirt_direction outgoing,
	minirt_direction surface_normal,
	minirt_color_hdr light_color,
	minirt_material material);

typedef void (*minirt_point_dispose_v)(minirt_point *self);
typedef minirt_material (*minirt_point_get_material_v)(minirt_point *self);
typedef minirt_direction (*minirt_point_get_normal_v)(minirt_point *self);

typedef struct {
	minirt_point_dispose_v dispose;
	minirt_point_get_material_v get_material;
	minirt_point_get_normal_v get_real_normal;
	minirt_point_get_normal_v get_mapped_normal;
} minirt_point_v;

struct _minirt_point {
	const minirt_point_v *v;
	minirt_brdf *optional_specialized_brdf;
};

void minirt_point_dispose(minirt_point *self);
minirt_material minirt_point_get_material(minirt_point *self);
minirt_direction minirt_point_get_real_normal(minirt_point *self);
minirt_direction minirt_point_get_mapped_normal(minirt_point *self);


typedef struct _minirt_object minirt_object;

typedef struct {
	minirt_position origin;
	minirt_direction direction;
} minirt_ray;

typedef struct {
	size_t length;
	minirt_point **array;
} minirt_hit_records;

typedef minirt_hit_records (
	*minirt_object_hit_records_v)(minirt_object *self, minirt_ray ray);

typedef struct {
	minirt_object_hit_records_v hit_records;
} minirt_object_v;

struct _minirt_object {
	const minirt_object_v *v;
};

minirt_hit_records
	minirt_object_hit_records(minirt_object *self, minirt_ray ray);


typedef struct _minirt_render_options minirt_render_options;

typedef minirt_color_ldr *(*minirt_render_options_tone_mapper_v)(
	minirt_render_options *self,
	minirt_color_hdr *buffer,
	size_t height,
	size_t width);
typedef void (*minirt_render_options_on_progress_v)(
	minirt_render_options *self,
	size_t total,
	size_t current);

typedef struct {
	minirt_render_options_tone_mapper_v tone_mapper;
	minirt_render_options_on_progress_v on_progress;
} minirt_render_options_v;

struct _minirt_render_options {
	const minirt_render_options_v *v;
	size_t sample_per_pixel;
	minirt_brdf *default_brdf;
};

minirt_color_ldr *minirt_render_options_tone_mapper(
	minirt_render_options *self,
	minirt_color_hdr *buffer,
	size_t height,
	size_t width);
void minirt_render_options_on_progress(
	minirt_render_options *self,
	size_t total,
	size_t current);

#endif
