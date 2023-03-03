#include "jarr.h"
#include <stdarg.h>

#define PRIVATE_JARR_CONCAT(T, jarr, t, argv, size)                            \
	va_list ap;                                                            \
	va_start(ap, size);                                                    \
	for (void* argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *)) \
		jarr->data[jarr->size++] = *(t*)argv;                          \
	va_end(ap)

#define PRIVATE_JARR_NEW(T, t)                                                     \
int jarr_new_##T(T *jarr, size_t size, ...)                                        \
{                                                                                  \
	jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);              \
	if (likely(jarr->data = malloc((jarr->capacity) * sizeof(*jarr->data)))) { \
		PRIVATE_JARR_CONCAT(T, jarr, t, argv, size);                       \
		return 1;                                                          \
	}                                                                          \
	return (JARR_INIT(jarr), 0);                                               \
}

JARR_DEFINE_F_T_t(PRIVATE_JARR_NEW)

#define PRIVATE_JARR_CAT(T, t)                                                                      \
int jarr_cat_##T(T *jarr, size_t size, ...)                                                         \
{                                                                                                   \
	if (jarr->size + size > jarr->capacity) {                                                   \
		do { jarr->capacity *= 2; } while (jarr->size + size > jarr->capacity);             \
		t *tmp;                                                                             \
		jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);                       \
		if (unlikely(!(tmp = realloc(jarr->data, (jarr->capacity) * sizeof(*jarr->data))))) \
			goto ERROR;                                                                 \
		jarr->data = tmp;                                                                   \
	}                                                                                           \
	PRIVATE_JARR_CONCAT(T, jarr, t, argv, size);                                                \
ERROR:                                                                                              \
	return (JARR_INIT(jarr), 0);                                                                \
}

JARR_DEFINE_F_T_t(PRIVATE_JARR_CAT)

#define PRIVATE_JARR_APPEND(T, t)                                                                 \
int jarr_append_##T(T *jarr, t src_arr, size_t src_arr_size)                                      \
{                                                                                                 \
	if (jarr->size + src_arr_size > jarr->capacity) {                                         \
		do { jarr->capacity *= 2; } while (jarr->size + src_arr_size > jarr->capacity);   \
		t tmp;                                                                            \
		if (unlikely(!(tmp = realloc(jarr->data, jarr->capacity * sizeof(*jarr->data))))) \
			goto ERROR;                                                               \
	}                                                                                         \
	memcpy(jarr->data, src_arr, src_arr_size * sizeof(*src_arr));                             \
	return 1;                                                                                 \
ERROR:                                                                                            \
	return (JARR_INIT(jarr), 0);                                                              \
}

JARR_DEFINE_F_T_t_ptr(PRIVATE_JARR_APPEND)

#define DEBUG
#ifdef DEBUG
int main()
{
	return 0;
}
#endif
