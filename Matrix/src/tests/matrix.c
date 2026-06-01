#include "matrix.h"

int main() {
  Suite *suites[] = {create_matrix_suite(),
                     remove_matrix_suite(),
                     equal_matrix_suite(),
                     sum_matrix_suite(),
                     sub_matrix_suite(),
                     mult_number_suite(),
                     mult_matrix_suite(),
                     transpose_suite(),
                     calc_complements_suite(),
                     determinant_suite(),
                     inverse_matrix_suite(),
                     my_functions_suite(),
                     NULL};

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