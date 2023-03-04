#ifndef JARR_H_DEF
#define JARR_H_DEF

/*
   _nocheck macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc;

   _noalloc macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.
*/

/* #define JARR_RELEASE */
#define JARR_INCLUDE
#define JARR_ALIGN_POWER_OF_TWO
#define JARR_64_BIT

#ifdef JARR_RELEASE
	#undef JARR_DEBUG
#else
	#define JARR_DEBUG
#endif

#include "/home/james/c/macros/vargc.h" // gch
#include "macros.h" // gch
#include "types.h" //gch
#include <stddef.h>

#ifdef JARR_INCLUDE
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdint.h>
#endif

#define JARR_MIN_CAP 8

#if defined(__GNUC__) || defined(__clang__)
	#define JARR_NEAR_POW2_32(x) \
		((x) ? 1 : 1UL << (sizeof((x)) * 8 - __builtin_clz((x) - 1)))
	#define JARR_NEAR_POW2_64(x) \
		((x) ? 1 : 1ULL << (sizeof((x)) * 8 - __builtin_clzll((x) - 1)))
#else
	#define JARR_NEAR_POW2_32(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		++x)
	#define JARR_NEAR_POW2_64(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		x |= x >> 32,        \
		++x)
#endif

#ifdef JARR_ALIGN_POWER_OF_TWO
	#ifdef JARR_64_BIT
		#define JARR_NEAR_POW2(x) JARR_NEAR_POW2_64(x)
	#elif JARR_32_BIT
		#define JARR_NEAR_POW2(x) JARR_NEAR_POW2_32(x)
	#else
		#define JARR_NEAR_POW2(x) (x)
	#endif
#endif

/* jarray_type type */

/*
jarray_int_t, int
jarray_uint_t, unsigned int
jarray_long_t, long
jarray_long_long_t, long long
jarray_ulong_t, unsigned long
jarray_ulong_long_t, unsigned long long
jarray_size_t_t, size_t
jarray_double_t, double
jarray_long_double_t, long double
jarray_float_t, float
jarray_short_t, short
jarray_ushort_t, unsigned short
jarray_char_t, char
jarray_uchar_t, unsigned char
*/

/* jarray_type */

/*
jarray_int_t
jarray_uint_t
jarray_long_t
jarray_long_long_t
jarray_ulong_t
jarray_ulong_long_t
jarray_size_t_t
jarray_double_t
jarray_long_double_t
jarray_float_t
jarray_short_t
jarray_ushort_t
jarray_char_t
jarray_uchar_t
*/

/* type */

/*
int
unsigned int
long
long long
unsigned long
unsigned long long
size_t
double
long double
float
short
unsigned short
char
unsigned char
*/

/* type: jarray */

/*
int: jarray_int_t,
unsigned int: jarray_uint_t,
long: jarray_long_t,
long long: jarray_long_long_t,
unsigned long: jarray_ulong_t,
unsigned long long: jarray_ulong_long_t,
size: jarray_size_t_t_t,
double: jarray_double_t,
long double: jarray_long_double_t,
*jarray_float_t: jarray_float_t,
short: jarray_short_t,
unsigned short: jarray_ushort_t,
char: jarray_char_t,
*jarray_unsigned_char_t: jarray_uchar_t,
*/

#define JARR_TEMPLATE_T(F) \
F(jarray_int_t)            \
F(jarray_uint_t)           \
F(jarray_long_t)           \
F(jarray_long_long_t)      \
F(jarray_ulong_t)          \
F(jarray_ulong_long_t)     \
F(jarray_size_t_t)         \
F(jarray_double_t)         \
F(jarray_long_double_t)    \
F(jarray_float_t)          \
F(jarray_short_t)          \
F(jarray_ushort_t)         \
F(jarray_char_t)           \
F(jarray_uchar_t)          \

#define JARR_TEMPLATE_T_t(F)               \
F(jarray_int_t, int)                       \
F(jarray_uint_t, unsigned int)             \
F(jarray_long_t, long)                     \
F(jarray_long_long_t, long long)           \
F(jarray_ulong_t, unsigned long)           \
F(jarray_ulong_long_t, unsigned long long) \
F(jarray_size_t_t, size_t)                 \
F(jarray_double_t, double)                 \
F(jarray_long_double_t, long double)       \
F(jarray_float_t, float)                   \
F(jarray_short_t, short)                   \
F(jarray_ushort_t, unsigned short)         \
F(jarray_char_t, char)                     \
F(jarray_uchar_t, unsigned char)           \

#define JARR_GENERIC(F, T, ...) _Generic((T),                                   \
	*jarray_int_t: F##_jarray_int_t(jarr_ptr, __VA_ARGS__),                 \
	*jarray_uint_t: F##_jarray_uint_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_long_t F##_jarray_long_t(jarr_ptr, __VA_ARGS__),                \
	*jarray_long_long_t: F##_jarray_long_long_t(jarr_ptr, __VA_ARGS__),     \
	*jarray_ulong_t: F##_jarray_ulong_t(jarr_ptr, __VA_ARGS__),             \
	*jarray_ulong_long_t F##_jarray_ulong_long_t(jarr_ptr, __VA_ARGS__),    \
	*jarray_size_t_t: F##_jarray_size_t_t(jarr_ptr, __VA_ARGS__),           \
	*jarray_double_t: F##_jarray_double_t(jarr_ptr, __VA_ARGS__),           \
	*jarray_long_double_t: F##_jarray_long_double_t(jarr_ptr, __VA_ARGS__), \
	*jarray_float_t: F##_jarray_float_t(jarr_ptr, __VA_ARGS__),             \
	*jarray_short: F##_jarray_short_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_ushort_t F##_jarray_ushort_t(jarr_ptr, __VA_ARGS__),            \
	*jarray_char_t: F##_jarray_char_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_unsigned_char_t: F##_jarray_uchar_t(jarr_ptr, __VA_ARGS__)      \
		)

#define JARR_STRUCT(T, t)        \
	typedef struct T {       \
		t *data;         \
		size_t size;     \
		size_t capacity; \
	} T;

JARR_TEMPLATE_T_t(JARR_STRUCT)

#define static_jarray_init(T, name, capacity)     \
	struct {                                  \
		T data[JARR_NEAR_POW2(capacity)]; \
		size_t size;                      \
	} name

#define jarr_init(jarr_ptr)                                                                      \
	(void)(((jarr_ptr)->capacity) = 0, ((jarr_ptr)->size) = 0, ((jarr_ptr)->data) = NULL, 0)

#define jarr_delete_nocheck(jarr_ptr)                          \
	(void)(free((jarr_ptr)->data), jarr_init(jarr_ptr), 0)

#define jarr_delete(jarr_ptr)                                   \
	(void)(((jarr)->data) && jarr_delete_nocheck(jarr_ptr))

#define jarr_new_alloc(jarr_ptr, cap)                                                                                              \
	(jarr->capacity = MAX(cap, JARR_MIN_CAP), (likely((jarr->data) = malloc(jarr->capacity * sizeof(*(jarr->data))))) ? 1 : 0)

static ALWAYS_INLINE int private_jarr_reserve_nocheck(void **jarr, size_t size)
{
	void *tmp;
	return ((tmp = (realloc(*jarr, size))) ? (*jarr = tmp, 1) : 0);
}

#define jarr_reserve_nocheck(jarr_ptr, cap) (private_jarr_reserve_nocheck(&((jarr_ptr)->data), cap * sizeof(*((jarr)->data))))

#define jarr_reserve(jarr_ptr, cap) (((cap) > ((jarr)->capacity)) ? (jarr_reserve_nocheck(jarr_ptr, cap)) : 1)

#define jarr_reserve_2x(jarr) jarr_reserve_nocheck(jarr, (2 * ((jarr)->capacity)))
#define jarr_reserve_4x(jarr) jarr_reserve_nocheck(jarr, (4 * ((jarr)->capacity)))
#define jarr_reserve_8x(jarr) jarr_reserve_nocheck(jarr, (8 * ((jarr)->capacity)))
#define jarr_reserve_16x(jarr) jarr_reserve_nocheck(jarr, (16 * ((jarr)->capacity)))
#define jarr_reserve_32x(jarr) jarr_reserve_nocheck(jarr, (32 * ((jarr)->capacity)))
#define jarr_reserve_64x(jarr) jarr_reserve_nocheck(jarr, (64 * ((jarr)->capacity)))

#define jarr_shrink(jarr_ptr)                                                                                   \
	((likely(((jarr)->capacity) != ((jarr)->size))) ? (jarr_reserve_nocheck(jarr_ptr, ((jarr)->size))) : 1)

#define jarr_shrink_nocheck(jarr_ptr)\
	jarr_reserve_nocheck(jarr_ptr, ((jarr)->size))

#define jarr_push_back_noalloc(jarr_ptr, value)          \
	(void)((((jarr_ptr)->data)[((jarr_ptr)->size)++] = value), 0)

#define jarr_push_back_nocheck(jarr_ptr, value)                                                                        \
	((jarr_reserve_nocheck_##T(jarr_ptr, jarr_ptr->capacity * 2)) && (jarr_push_back_noalloc(jarr_ptr, value), 1))

#define jarr_push_back(jarr_ptr, value)                                                                                                \
	((unlikely((jarr_ptr)->capacity)) ? (jarr_push_back_noheck(jarr_ptr, value)) : ((jarr_push_back_noalloc(jarr_ptr, value)), 1))

#define jarr_new_auto(jarr_ptr, ...) JARR_GENERIC(jarr_new, jarr_ptr, __VA_ARGS__)
#define jarr_new(jarr_ptr, jarr_size, ...) JARR_GENERIC(jarr_new, jarr_ptr, jarr_size)

#define jarr_cat(jarr_ptr, ...) ((PP_NARG(__VA_ARGS__) == 1) ? jarr_push_back(jarr_ptr, PP_NARG(__VA_ARGS__)) : JARR_GENERIC(jarr_cat, jarr_ptr, PP_NARG(__VA_ARGS__), ...))
#define jarr_cat_noalloc(jarr_ptr, ...) ((PP_NARG(__VA_ARGS__) == 1) ? jarr_push_back_noalloc(jarr_ptr, PP_GET_FIRST_ARG(__VA_ARGS__)) : JARR_GENERIC(jarr_cat_noalloc, jarr_ptr, PP_NARG(__VA_ARGS__), ...))

#define jarr_append(jarr_ptr, src_arr) JARR_GENERIC(jarr_append, jarr_ptr, src_arr)

#define jarr_pop_back(jarr) --((jarr)->size);

#define jarr_cmp(jarr_dest, jarr_src) ((((jarr_dest)->size) != ((jarr_src)->size)) || memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp_nocheck(jarr_dest, jarr_src) (memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))

#define jarr_foreach_index(elem, jarr) for (size_t elem = 0, size = ((jarr)->size); elem < size; ++elem)

#define jarr_foreach(elem, jarr) for (typeof(*((jarr)->data)) *RESTRICT elem = ((jarr)->data), *RESTRICT end = ((jarr)->data) + ((jarr)->size); elem < end; ++elem)

#define jarr_foreach_arr(elem, arr) for (typeof(arr[0]) *RESTRICT elem = &(arr[0]), *RESTRICT end = (&((arr)[(sizeof(arr)/sizeof(arr[0])) - 1])); elem < end; ++elem)

#define jarr_end(jarr) (*(((jarr)->data) + ((jarr)->size) - 1))

#define jarr_auto_elem(jarr) typeof(*((jarr)->data))

#define jarr_auto(jarr) typeof((*(jarr)))

#define JARR_SAME_TYPE(x, y) _Generic((x), \
	typeof(y): 1,                      \
	default: 0                         \
	)

#endif
