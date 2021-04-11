#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

// PERIODIC CYCLES:
//      for input            i: 0,1,2,3,4,5,6,7,8,...
//      get periodic output  o: 0,1,2,0,1,2,0,1,2,...
// m:-1, p:1, z:0
#define cycle2_zp(i) (i % 2)
#define cycle2_pz(i) ((i + 1) % 2)
#define cycle2_mz(i) ((i % 2) - 1)
#define cycle2_zm(i) (((i + 1) % 2) - 1)
#define cycle2_mp(i) (cycle2_mz(i) + cycle2_zp(i))
#define cycle2_pm(i) (cycle2_pz(i) + cycle2_zm(i))

#define cycle3_mzp(i) ((i % 3) - 1)
#define cycle3_zpm(i) (((i + 1) % 3) - 1)
#define cycle3_pmz(i) (((i + 2) % 3) - 1)
#define cycle3_pzm(i) (1 - (i % 3))
#define cycle3_zmp(i) (1 - ((i + 1) % 3))
#define cycle3_mpz(i) (1 - ((i + 2) % 3))

#define cycle4_mzp2(i) ((i % 4) - 1)
#define cycle4_zp2m(i) (((i + 1) % 4) - 1)
#define cycle4_p2mz(i) (((i + 2) % 4) - 1)
#define cycle4_2mzp(i) (((i + 3) % 4) - 1)
#define cycle4_mzpz(i) (cycle2_pz(i) * cycle4_mzp2(i))
#define cycle4_pzmz(i) (cycle2_mz(i) * cycle4_mzp2(i))
#define cycle4_zmzp(i) (cycle2_zp(i) * cycle4_2mzp(i))
#define cycle4_zpzm(i) (cycle2_zp(i) * cycle4_zp2m(i))

#define cycle4_mmpp(i) (cycle4_mzpz(i) + cycle4_zmzp(i))
#define cycle4_pmmp(i) (cycle4_pzmz(i) + cycle4_zmzp(i))
#define cycle4_mppm(i) (cycle4_mzpz(i) + cycle4_zpzm(i))
#define cycle4_ppmm(i) (cycle4_pzmz(i) + cycle4_zpzm(i))

#define cycle6_mzpzzz(i) (cycle3_mzp(i) * cycle2_pz(i))
#define cycle6_zzzmzp(i) (cycle3_mzp(i) * cycle2_zp(i))
#define cycle6_zzmzpz(i) (cycle3_zpm(i) * cycle2_pz(i))
#define cycle6_zpzzzm(i) (cycle3_zpm(i) * cycle2_zp(i))
#define cycle6_pzzzmz(i) (cycle3_pmz(i) * cycle2_pz(i))
#define cycle6_zmzpzz(i) (cycle3_pmz(i) * cycle2_zp(i))

#define cycle6_mzzzpz(i) (cycle3_mpz(i) * cycle2_pz(i))
#define cycle6_zpzmzz(i) (cycle3_mpz(i) * cycle2_zp(i))
#define cycle6_pzmzzz(i) (cycle3_pzm(i) * cycle2_pz(i))
#define cycle6_zzzpzm(i) (cycle3_pzm(i) * cycle2_zp(i))
#define cycle6_zzpzmz(i) (cycle3_zmp(i) * cycle2_pz(i))
#define cycle6_zmzzzp(i) (cycle3_zmp(i) * cycle2_zp(i))

#define cycle6_mppmzz(i) (cycle6_mzpzzz(i) + cycle6_zpzmzz(i))
#define cycle6_zzmppm(i) (cycle6_zzzpzm(i) + cycle6_zzmzpz(i))
#define cycle6_pmzzmp(i) (cycle6_zmzzzp(i) + cycle6_pzzzmz(i))


// ################### VARIADIC MACROS:##########################
//  FOR_EACH:      
//     Apply arbitrary macro to each arg in __VA_ARGS__
//     Can work up to 63 args, :
//              1- Copy FOR_EACH_N
//              2- Add integers up to N to FOR_EACH_RSEQ_N and FOR_EACH_ARG_N
// 
//  FOR_EACH_NARG-> Count number of args in __VA_ARGS__

#define CONCATENATE(arg1, arg2) CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(macro, x)\
    macro(x)

#define FOR_EACH_2(macro, x, ...)\
    macro(x),\
    FOR_EACH_1(macro, __VA_ARGS__)

#define FOR_EACH_3(macro, x, ...)\
    macro(x),\
    FOR_EACH_2(macro, __VA_ARGS__)

#define FOR_EACH_4(macro, x, ...)\
    macro(x),\
    FOR_EACH_3(macro,  __VA_ARGS__)

#define FOR_EACH_5(macro, x, ...)\
    macro(x),\
    FOR_EACH_4(macro,  __VA_ARGS__)

#define FOR_EACH_6(macro, x, ...)\
    macro(x),\
    FOR_EACH_5(macro,  __VA_ARGS__)

#define FOR_EACH_7(macro, x, ...)\
    macro(x),\
    FOR_EACH_6(macro,  __VA_ARGS__)

#define FOR_EACH_8(macro, x, ...)\
    macro(x),\
    FOR_EACH_7(macro,  __VA_ARGS__)

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define FOR_EACH_(N, macro, ...) CONCATENATE(FOR_EACH_, N)(macro, __VA_ARGS__)
#define FOR_EACH(macro, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), macro, __VA_ARGS__)

// OVERLOADED: choose macro on number of input args
#define GET_MACRO(_1,_2,_3,NAME,...) NAME
#define OVERLOADED(...) GET_MACRO(__VA_ARGS__, OL3, OL2)(__VA_ARGS__)
#define OL2(x,y)
#define OL3(x,y,z)
// EXAMPLE:

// FOO(World, !)         # expands to FOO2(World, !)
// FOO(foo,bar,baz)      # expands to FOO3(foo,bar,baz)
#endif // MACROS