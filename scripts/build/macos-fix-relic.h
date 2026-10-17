/* Force-included on macOS builds (-include). The macOS SDK <mach/error.h>
 * defines a function-like macro err_get_code(err), which collides with
 * relic's `int err_get_code(void);` declaration in chiabls/contrib/relic.
 * Include the SDK header once up front, then drop the macro; its include
 * guard keeps it from being redefined later. Nothing in AMMOcoin uses the
 * mach macro. */
#ifdef __APPLE__
#include <mach/error.h>
#undef err_get_code
#endif
