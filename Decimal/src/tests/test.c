#include "test.h"

int main() {
  Suite *suites[] = {arithmetic_suite(), comparison_suite(), converters_suite(),
                     decimal_suite(),    other_suite(),      NULL};

  int total_failed = 0;

  for (int i = 0; suites[i] != NULL; i++) {
    SRunner *runner = srunner_create(suites[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    int failed = srunner_ntests_failed(runner);
    total_failed += failed;
    srunner_free(runner);
  }

  return (total_failed == 0) ? 0 : 1;
}