#ifndef MINIRT_BASE_H
#define MINIRT_BASE_H

#include <stdbool.h>
#include <stddef.h>


typedef bool minirt_err;


#ifndef MINIRT_PRECISION
# define MINIRT_PRECISION 1
#endif

#if MINIRT_PRECISION == 1
typedef float minirt_f;
#elif MINIRT_PRECISION == 2
typedef double minirt_f;
#elif MINIRT_PRECISION == 3
typedef long double minirt_f;
#else
# error Unrecognized MINIRT_PRECISION value
#endif

minirt_f minirt_f_sqrt(minirt_f f);
minirt_f minirt_f_pow(minirt_f f, minirt_f exp);
minirt_f minirt_f_ln(minirt_f f);
minirt_f minirt_f_log(minirt_f f, minirt_f base);
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
MINIRT_STRUCT3(minirt_pixel, r, g, b);

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
minirt_transform minirt_transform_rotate_yaw(minirt_f yaw);
minirt_transform minirt_transform_rotate_pitch(minirt_f pitch);
minirt_transform minirt_transform_rotate_roll(minirt_f roll);
minirt_transform minirt_transform_translate(minirt_distance distance);
minirt_transform minirt_compose(minirt_transform a, minirt_transform b);


typedef struct _minirt_point minirt_point;

typedef struct {
	minirt_color_ldr albedo;
	minirt_f roughness;
	minirt_f specular;
	minirt_f metallic;
} minirt_material;

typedef struct _minirt_brdf minirt_brdf;

typedef void (*minirt_brdf_dispose_v)(minirt_brdf *self);

typedef minirt_err (*minirt_brdf_function_v)(
	minirt_brdf *self,
	minirt_direction incident,
	minirt_direction light_direction,
	minirt_direction surface_normal,
	minirt_color_hdr light_color,
	minirt_material material,
	minirt_f *out);

typedef struct {
	minirt_brdf_dispose_v dispose;
	minirt_brdf_function_v function;
} minirt_brdf_v;

struct _minirt_brdf {
	const minirt_brdf_v *v;
};

typedef void (*minirt_point_dispose_v)(minirt_point *self);
typedef minirt_err (
	*minirt_point_get_material_v)(minirt_point *self, minirt_material *out);
typedef minirt_err (
	*minirt_point_get_normal_v)(minirt_point *self, minirt_direction *out);

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


typedef struct _minirt_object minirt_object;

typedef struct {
	minirt_position origin;
	minirt_direction direction;
} minirt_ray;

typedef struct {
	size_t length;
	size_t capacity;
	minirt_point *array[];
} minirt_hit_records;

typedef void (*minirt_object_dispose_v)(minirt_object *self);
typedef minirt_err (*minirt_object_hit_records_v)(
	minirt_object *self,
	minirt_ray ray,
	minirt_hit_records *mut);

typedef struct {
	minirt_object_dispose_v dispose;
	minirt_object_hit_records_v hit_records;
} minirt_object_v;

struct _minirt_object {
	const minirt_object_v *v;
};


typedef struct _minirt_prng minirt_prng;

typedef void (*minirt_prng_dispose_v)(minirt_prng *self);
typedef minirt_f (*minirt_prng_random_v)(minirt_prng *self);

typedef struct {
	minirt_prng_dispose_v dispose;
	minirt_prng_random_v random;
} minirt_prng_v;

struct _minirt_prng {
	const minirt_prng_v *v;
};


typedef struct _minirt_camera minirt_camera;

typedef void (*minirt_camera_dispose_v)(minirt_camera *self);
typedef minirt_err (*minirt_camera_ray_v)(
	minirt_camera *self,
	size_t d,
	size_t h,
	size_t w,
	size_t z,
	size_t y,
	size_t x,
	minirt_prng *prng,
	minirt_ray *out);

typedef struct {
	minirt_camera_dispose_v dispose;
	minirt_camera_ray_v ray;
} minirt_camera_v;

struct _minirt_camera {
	const minirt_camera_v *v;
};


typedef struct _minirt minirt;

typedef struct {
	size_t height;
	size_t width;
	minirt_color_hdr pixels[];
} minirt_image_hdr;

typedef struct {
	size_t height;
	size_t width;
	minirt_color_ldr pixels[];
} minirt_image_ldr;

typedef struct {
	minirt_brdf *default_brdf;
} minirt_render_options;

typedef struct {
	size_t complete_depth;
	size_t complete_height;
	size_t complete_width;
	size_t total_depth;
	size_t total_height;
	size_t total_width;
	minirt_pixel pixels[];
} minirt_progress;

typedef void (*minirt_dispose_v)(minirt *self);
typedef void (*minirt_step_v)(minirt *self);

typedef struct {
	minirt_dispose_v dispose;
	minirt_step_v step;
} minirt_v;

struct _minirt {
	const minirt_v *v;
	minirt_render_options options;
	minirt_progress progress;
};


#endif
