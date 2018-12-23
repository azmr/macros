// TODO:
// - literal arrays
// 		for each(char, C in ['A', 'B', C'])
//		#define in , arrayliteral
//
// make sure that you don't have any trailing semicolons

#ifndef EACH_H
#define EACH_CAT(A, ...)  CAT2(A, __VA_ARGS__)
#define EACH_CAT2(A, ...) CAT1(A, __VA_ARGS__)
#define EACH_CAT1(A, ...) A##__VA_ARGS__
#define EACH_LINE(A) CAT(A, __LINE__)

// Suitable for C89 - variables have already been defined (declared?)
#define eachdef(var, atype, arr) \
	(each_indextype(arr) each_indexify(var) = 0, \
	each_## atype ##_init(arr); \
	each_## atype ##_cond(i##var, arr); \
	each_## atype ##_next(i## var, arr))

#define each(type, var, atype, arr) \
	(each_indextype(arr) each_indexify(var) = 0, EACH_LINE(each_once) = 1; (each_indexify(var), EACH_LINE(each_once)--);) \
	for(each_## atype ##_init(type, var, arr, each_indexify(var)); \
		each_## atype ##_cond(type, var, arr, each_indexify(var)); \
		each_## atype ##_next(type, var, arr, each_indexify(var)))

// e.g. could define to empty for C89
#ifndef each_indextype_default
#define each_indextype_default int
#endif

#ifdef  EACH_CUSTOM_INDEX_TYPE
/* will this expand correctly? */
#define each_indextype(arr) each_## arr ##_indextype
#else /*EACH_CUSTOM_INDEX_TYPE*/
#define each_indextype(arr) each_indextype_default
#endif/*EACH_CUSTOM_INDEX_TYPE*/

#ifndef each_indexify
#define each_indexify(var) i## var
#endif/* each_indexify*/

/* TODO: cache arr? */
#ifndef each_array_init
#define each_array_init(type, var, arr, i) type var = arr[0]
#define each_array_cond(type, var, arr, i) i < sizeof(arr)/sizeof(*(arr))
#define each_array_next(type, var, arr, i) ++i, var = arr[i]
#endif/*each_array_init*/

#ifndef each_arrayptr_init
#define each_arrayptr_init(type, var, arr, i) type var = &arr[0]
#define each_arrayptr_cond(type, var, arr, i) i < sizeof(arr)/sizeof(*(arr))
#define each_arrayptr_next(type, var, arr, i) ++i, var = &arr[i]
#endif/*each_arrayptr_init*/

#ifndef each_arrayliteral_init
#define each_arrayliteral_expand(...) {__VA_ARGS__}
#define each_arrayliteral_init(type, var, arr, i) type var##s[] = each_arrayliteral_expand## arr, var = var##s[0]
#define each_arrayliteral_cond(type, var, arr, i) i < sizeof(var##s)/sizeof(*(var##s))
#define each_arrayliteral_next(type, var, arr, i) ++i
#endif/*each_array_init*/

#ifndef each_of
#define each_of(array_lit) arrayliteral, (array_lit)
/* Used as: for each(float, f, each_of(2.1f, -.7f, 58.f)) {do something...}*/
#endif/*each_of*/

/* Usage:
 * #define in ,
 * #define of ,
 * for each(char *, String in array of Strings)
 * { printf("%d: %s\n", iString, String) }
 * 
 * char * String;
 * for eachdef(String, Strings, array)
 * { printf("%d: %s\n", iString, String) }
 */

#ifndef each_arr_init
#define each_arr_base(base, count) base
#define each_arr_count(base, count) count
#define each_arr_init(type, var, arr) type var = each_arr_base## arr[0]
#define each_arr_cond(type, var, arr, i) i < each_arr_count## arr )
#define each_arr_next(type, var, arr, i) ++i, var = each_arr_base## arr[i]
#endif/*each_arr_init*/

#ifndef each_arrptr_init
#define each_arrptr_init(type, var, arr) type var = &each_arr_base## arr[0]
#define each_arrptr_cond(type, var, arr, i) i < each_arr_count## arr )
#define each_arrptr_next(type, var, arr, i) ++i, var = &each_arr_base## arr[i]
#endif/*each_arrptr_init*/

#define EACH_H
#endif
