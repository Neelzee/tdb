#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "../lib/db/db.h"

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) { (void)state; /* unused */ }

static void test_maybe_nothing(void **state) {
  struct Maybe nothing = {.nothing = true};
  assert_true(is_nothing(&nothing));
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(null_test_success),
      cmocka_unit_test(test_maybe_nothing),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
