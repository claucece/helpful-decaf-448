# Notes

## Building

Take in account that *Makefile* is designed for Mac. Refer to the `Makefile` and
`README.txt`.

On Decaf branch:

For building the code, run `make`. If you want to run a stripped down version of
the library, run `make lib`. To run the tests run `make test`.

If you see this warning
`#warning "_BSD_SOURCE and _SVID_SOURCE are deprecated, use _DEFAULT_SOURCE"`,
change all places where `_BSD_SOURCE` and `_SVID_SOURCE` (if any) to
`_DEFAULT_SOURCE`. For further errors, regarding this, refer to
[here](http://stackoverflow.com/questions/29201515/what-does-d-default-source-do)

On Master branch:

For building the code, run `make build/goldilocks.so`.

## Architecture

Check your arch by running `uname -m` (this should work for Linux too). I will
give you as out put something like this `x86_64`.

On Decaf branch:

By default, the code will run in 64arch. To change it to 32, go to the Makefile
and do this:

```
#ifneq (,$(findstring x86_64,$(MACHINE)))
#ARCH ?= arch_x86_64
#else
# no i386 port yet
#ARCH ?= arch_arm_32
#endif
ARCH = arch_32
```

You will also see on `include/decaf.h`, this line

`#if (defined(__ILP64__) || defined(__amd64__) || defined(__x86_64__) || (((__UINT_FAST32_MAX__)>>30)>>30)) \
&& !defined(DECAF_FORCE_32_BIT)
`

This line, will make `DECAF_WORD_BITS` equal to 64. You need them to equal 32,
so (on the same file), after this line `#define __DECAF_448_H__ 1`, add this
`#define DECAF_FORCE_32_BIT`

## Tests

On Decaf branch:

All tests are located on test folder. The important one is `test_decaf.cxx`.
Test are written in C++, so, in order to use a function on it, you will need to
expose it to C header and C++ header.

For doing a test, it is always good to do this order:

1. Change the file: `src/decaf_fast.c`
2. Expose the function to the c header: `include/decaf.h`
3. Expose the function to the c++ header: `include/decaf.hxx`
3. Do the test on: `test/test_decaf.cxx`
