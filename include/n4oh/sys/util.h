/*
 * Copyright (c) 2011-2014, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SYS_UTIL_H_
#define _SYS_UTIL_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX
/**
 * @brief Obtain the maximum of two values.
 *
 * @note Arguments are evaluated twice. Use Z_MAX for a GCC-only, single
 * evaluation version
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Maximum value of @p a and @p b.
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
/**
 * @brief Obtain the minimum of two values.
 *
 * @note Arguments are evaluated twice. Use Z_MIN for a GCC-only, single
 * evaluation version
 *
 * @param a First value.
 * @param b Second value.
 *
 * @returns Minimum value of @p a and @p b.
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/**
 * @brief Value of @p x rounded up to the next multiple of @p align.
 */
#define ROUND_UP(x, align)                                   \
	((((unsigned long)(x) + ((unsigned long)(align) - 1)) / \
	  (unsigned long)(align)) * (unsigned long)(align))

/**
 * @brief Value of @p x rounded down to the previous multiple of @p align.
 */
#define ROUND_DOWN(x, align)                                 \
	(((unsigned long)(x) / (unsigned long)(align)) * (unsigned long)(align))

/**
 * @brief Checks if a value is within range.
 *
 * @note @p val is evaluated twice.
 *
 * @param val Value to be checked.
 * @param min Lower bound (inclusive).
 * @param max Upper bound (inclusive).
 *
 * @retval true If value is within range
 * @retval false If the value is not within range
 */
#define IN_RANGE(val, min, max) ((min) <= (val) && (val) <= (max))

/**
 * @brief Divide and round up.
 *
 * Example:
 * @code{.c}
 * DIV_ROUND_UP(1, 2); // 1
 * DIV_ROUND_UP(3, 2); // 2
 * @endcode
 *
 * @param n Numerator.
 * @param d Denominator.
 *
 * @return The result of @p n / @p d, rounded up.
 */
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

/** @brief 0 if @p cond is true-ish; causes a compile error otherwise. */
#define ZERO_OR_COMPILE_ERROR(cond) ((int) sizeof(char[1 - 2 * !(cond)]) - 1)

#if defined(__cplusplus)

/* The built-in function used below for type checking in C is not
 * supported by GNU C++.
 */
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#else /* __cplusplus */

/**
 * @brief Zero if @p array has an array type, a compile error otherwise
 *
 * This macro is available only from C, not C++.
 */
#define IS_ARRAY(array) \
	ZERO_OR_COMPILE_ERROR( \
		!__builtin_types_compatible_p(__typeof__(array), \
					      __typeof__(&(array)[0])))

/**
 * @brief Number of elements in the given @p array
 *
 * In C++, due to language limitations, this will accept as @p array
 * any type that implements <tt>operator[]</tt>. The results may not be
 * particularly meaningful in this case.
 *
 * In C, passing a pointer as @p array causes a compile error.
 */
#define ARRAY_SIZE(array) \
	((size_t) (IS_ARRAY(array) + (sizeof(array) / sizeof((array)[0]))))

#endif /* __cplusplus */

/**
 * @brief Get a pointer to a structure containing the element
 *
 * Example:
 *
 *	struct foo {
 *		int bar;
 *	};
 *
 *	struct foo my_foo;
 *	int *ptr = &my_foo.bar;
 *
 *	struct foo *container = CONTAINER_OF(ptr, struct foo, bar);
 *
 * Above, @p container points at @p my_foo.
 *
 * @param ptr pointer to a structure element
 * @param type name of the type that @p ptr is an element of
 * @param member the name of the field within the struct @p ptr points to
 * @return a pointer to the structure that contains @p ptr
 */
#define CONTAINER_OF(ptr, type, member)                         \
    ({                                                          \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type, member) );    \
    })

#ifdef __cplusplus
}
#endif

#endif /* _SYS_UTIL_H_ */

