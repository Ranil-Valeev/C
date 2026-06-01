#include <check.h>
#include <string.h>
#include "../s21_string.h"

// ---------------- TESTS ----------------

START_TEST(test_memchr) {
    char str[] = "Hello world";
    ck_assert_ptr_eq(s21_memchr(str, 'o', 5), memchr(str, 'o', 5));
    ck_assert_ptr_eq(s21_memchr(str, 'z', 11), memchr(str, 'z', 11));
    ck_assert_ptr_eq(s21_memchr(str, '\0', 12), memchr(str, '\0', 12));
    ck_assert_ptr_eq(s21_memchr("", 'a', 0), memchr("", 'a', 0));
}
END_TEST

START_TEST(test_memcmp) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hellp";
    char str4[] = "Hell";

    ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
    ck_assert_int_lt(s21_memcmp(str1, str3, 5), 0);
    ck_assert_int_gt(s21_memcmp(str3, str1, 5), 0);
    ck_assert_int_eq(s21_memcmp(str1, str4, 4), memcmp(str1, str4, 4));
    ck_assert_int_eq(s21_memcmp("", "", 0), memcmp("", "", 0));
}
END_TEST

START_TEST(test_memcpy) {
    char src[] = "Test string";
    char dest1[20] = {0}, dest2[20] = {0};
    char dest3[20] = "Existing";
    char dest4[20] = "Existing";

    void *res1 = s21_memcpy(dest1, src, 5);
    void *res2 = memcpy(dest2, src, 5);

    ck_assert_ptr_eq(res1, dest1);
    ck_assert_ptr_eq(res2, dest2);
    ck_assert_mem_eq(dest1, dest2, 5);

    s21_memcpy(dest3, src, 5);
    memcpy(dest4, src, 5);
    ck_assert_mem_eq(dest3, dest4, 20);

    ck_assert_ptr_eq(s21_memcpy(NULL, src, 0), NULL);
    ck_assert_ptr_eq(s21_memcpy(dest1, NULL, 0), dest1);
}
END_TEST

START_TEST(test_memset) {
    char str1[10] = {0}, str2[10] = {0};
    char str3[10] = "Initial";
    char str4[10] = "Initial";

    void *res1 = s21_memset(str1, 'A', 5);
    void *res2 = memset(str2, 'A', 5);

    ck_assert_ptr_eq(res1, str1);
    ck_assert_ptr_eq(res2, str2);
    ck_assert_mem_eq(str1, str2, 5);

    s21_memset(str3 + 2, 'B', 3);
    memset(str4 + 2, 'B', 3);
    ck_assert_mem_eq(str3, str4, 10);

    ck_assert_ptr_eq(s21_memset(NULL, 'A', 0), NULL);
}
END_TEST

START_TEST(test_strncat) {
    char dest1[20] = "Hello";
    char dest2[20] = "Hello";
    char src[] = " world";
    char dest3[20] = "";
    char dest4[20] = "";

    ck_assert_str_eq(s21_strncat(dest1, src, 3), strncat(dest2, src, 3));
    ck_assert_str_eq(s21_strncat(dest3, src, 6), strncat(dest4, src, 6));
    ck_assert_str_eq(s21_strncat(dest1, "", 1), strncat(dest2, "", 1));
}
END_TEST

START_TEST(test_strchr) {
    char str[] = "Test string";
    ck_assert_ptr_eq(s21_strchr(str, 's'), strchr(str, 's'));
    ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
    ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
    ck_assert_ptr_eq(s21_strchr("", 'a'), strchr("", 'a'));
}
END_TEST

START_TEST(test_strncmp) {
    ck_assert_int_eq(s21_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
    ck_assert_int_lt(s21_strncmp("abc", "abd", 3), 0);
    ck_assert_int_gt(s21_strncmp("abd", "abc", 3), 0);
    ck_assert_int_eq(s21_strncmp("ab", "abc", 2), strncmp("ab", "abc", 2));
    ck_assert_int_eq(s21_strncmp("", "", 0), strncmp("", "", 0));
}
END_TEST

START_TEST(test_strncpy) {
    char dest1[10] = {0}, dest2[10] = {0};
    char dest3[10] = "Old";
    char dest4[10] = "Old";
    char src[] = "Test";

    ck_assert_str_eq(s21_strncpy(dest1, src, 5), strncpy(dest2, src, 5));
    ck_assert_str_eq(s21_strncpy(dest3, src, 3), strncpy(dest4, src, 3));
    ck_assert_str_eq(s21_strncpy(dest1, "", 1), strncpy(dest2, "", 1));
}
END_TEST

START_TEST(test_strcspn) {
    ck_assert_int_eq(s21_strcspn("hello", "l"), strcspn("hello", "l"));
    ck_assert_int_eq(s21_strcspn("hello", "xyz"), strcspn("hello", "xyz"));
    ck_assert_int_eq(s21_strcspn("", "abc"), strcspn("", "abc"));
    ck_assert_int_eq(s21_strcspn("hello", ""), strcspn("hello", ""));
}
END_TEST

START_TEST(test_strlen) {
    ck_assert_int_eq(s21_strlen(""), strlen(""));
    ck_assert_int_eq(s21_strlen("hello"), strlen("hello"));
    ck_assert_int_eq(s21_strlen("longer string with spaces"),
                     strlen("longer string with spaces"));
}
END_TEST

START_TEST(test_strpbrk) {
    char str[] = "This is a test";
    ck_assert_ptr_eq(s21_strpbrk(str, "aeiou"), strpbrk(str, "aeiou"));
    ck_assert_ptr_eq(s21_strpbrk(str, "xyz"), strpbrk(str, "xyz"));
    ck_assert_ptr_eq(s21_strpbrk("", "abc"), strpbrk("", "abc"));
}
END_TEST

START_TEST(test_strrchr) {
    char str[] = "test string";
    ck_assert_ptr_eq(s21_strrchr(str, 't'), strrchr(str, 't'));
    ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
    ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
    ck_assert_ptr_eq(s21_strrchr("", 'a'), strrchr("", 'a'));
}
END_TEST

START_TEST(test_strstr) {
    char str[] = "Simple test string";
    ck_assert_ptr_eq(s21_strstr(str, "test"), strstr(str, "test"));
    ck_assert_ptr_eq(s21_strstr(str, "none"), strstr(str, "none"));
    ck_assert_ptr_eq(s21_strstr(str, ""), strstr(str, ""));
    ck_assert_ptr_eq(s21_strstr("", "test"), strstr("", "test"));
}
END_TEST

START_TEST(test_strtok) {
    char str1_orig[] = "test,string,example";
    char str2_orig[] = "test,string,example";
    char str1[50], str2[50];
    strcpy(str1, str1_orig);
    strcpy(str2, str2_orig);

    char *token1 = s21_strtok(str1, ",");
    char *token2 = strtok(str2, ",");
    ck_assert_str_eq(token1, token2);

    if (token1 != NULL && token2 != NULL) {
        token1 = s21_strtok(NULL, ",");
        token2 = strtok(NULL, ",");
    }

    char str3[] = "test string";
    char str4[] = "test string";
    ck_assert_str_eq(s21_strtok(str3, " "), strtok(str4, " "));

    ck_assert_ptr_eq(s21_strtok("", ","), strtok("", ","));
}
END_TEST

START_TEST(test_to_upper) {
    char str[] = "hello";
    char str2[] = "Hello123";
    char str3[] = "";

    char *result = s21_to_upper(str);
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "HELLO");
    free(result);

    result = s21_to_upper(str2);
    ck_assert_str_eq(result, "HELLO123");
    free(result);

    result = s21_to_upper(str3);
    ck_assert_str_eq(result, "");
    free(result);

    ck_assert_ptr_null(s21_to_upper(NULL));
}
END_TEST

START_TEST(test_to_lower) {
    char str[] = "HELLO";
    char str2[] = "Hello123";
    char str3[] = "";

    char *result = s21_to_lower(str);
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "hello");
    free(result);

    result = s21_to_lower(str2);
    ck_assert_str_eq(result, "hello123");
    free(result);

    result = s21_to_lower(str3);
    ck_assert_str_eq(result, "");
    free(result);

    ck_assert_ptr_null(s21_to_lower(NULL));
}
END_TEST

START_TEST(test_insert) {
    char src[] = "Hello";
    char str[] = " world";
    char str2[] = "";

    char *result = s21_insert(src, str, 5);
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "Hello world");
    free(result);

    result = s21_insert(src, str2, 3);
    ck_assert_str_eq(result, "Hello");
    free(result);

    result = s21_insert(str2, src, 0);
    ck_assert_str_eq(result, "Hello");
    free(result);

    ck_assert_ptr_null(s21_insert(NULL, str, 0));
    ck_assert_ptr_null(s21_insert(src, NULL, 0));
    ck_assert_ptr_null(s21_insert(src, str, 10));
}
END_TEST

START_TEST(test_trim) {
    char src[] = "  Hello  ";
    char trim_chars[] = " ";
    char src2[] = "xxHelloxx";
    char trim_chars2[] = "x";
    char src3[] = "Hello";

    char *result = s21_trim(src, trim_chars);
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "Hello");
    free(result);

    result = s21_trim(src2, trim_chars2);
    ck_assert_str_eq(result, "Hello");
    free(result);

    result = s21_trim(src3, trim_chars);
    ck_assert_str_eq(result, "Hello");
    free(result);

    result = s21_trim("", trim_chars);
    ck_assert_str_eq(result, "");
    free(result);

    ck_assert_ptr_null(s21_trim(NULL, trim_chars));
    // ck_assert_ptr_null(s21_trim(src, NULL));
}
END_TEST

// START_TEST(test_sprintf_d) {
//     char a[100], b[100];
//     s21_sprintf(a, "%d", 42);
//     sprintf(b, "%d", 42);
//     ck_assert_str_eq(a, b);

//     s21_sprintf(a, "%+d %-5d % d %8.3d", 42, 42, 42, 42);
//     sprintf(b, "%+d %-5d % d %8.3d", 42, 42, 42, 42);
//     ck_assert_str_eq(a, b);

//     short s = 123;
//     long l = 456;
//     s21_sprintf(a, "%hd %ld", s, l);
//     sprintf(b, "%hd %ld", s, l);
//     ck_assert_str_eq(a, b);
// }
// END_TEST

// START_TEST(test_sprintf_u) {
//     char a[100], b[100];
//     unsigned int u = 42;
//     unsigned long ul = 100;

//     s21_sprintf(a, "%u", u);
//     sprintf(b, "%u", u);
//     ck_assert_str_eq(a, b);

//     s21_sprintf(a, "%8.3u %lu", u, ul);
//     sprintf(b, "%8.3u %lu", u, ul);
//     ck_assert_str_eq(a, b);
// }
// END_TEST

START_TEST(test_sprintf_f) {
    char a[100], b[100];
    double x = 3.14;

    s21_sprintf(a, "%f", x);
    sprintf(b, "%f", x);
    ck_assert_str_eq(a, b);

    s21_sprintf(a, "%+f % f %10.2f %-10.3f", x, x, x, x);
    sprintf(b, "%+f % f %10.2f %-10.3f", x, x, x, x);
    ck_assert_str_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_s) {
    char a[100], b[100];
    char *str = "hello";

    s21_sprintf(a, "%s", str);
    sprintf(b, "%s", str);
    ck_assert_str_eq(a, b);

    s21_sprintf(a, "%10s %.3s %-10.3s", str, str, str);
    sprintf(b, "%10s %.3s %-10.3s", str, str, str);
    ck_assert_str_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_c) {
    char a[100], b[100];

    s21_sprintf(a, "%c", 'A');
    sprintf(b, "%c", 'A');
    ck_assert_str_eq(a, b);

    s21_sprintf(a, "%5c %-5c", 'A', 'B');
    sprintf(b, "%5c %-5c", 'A', 'B');
    ck_assert_str_eq(a, b);
}
END_TEST

START_TEST(test_sprintf_percent) {
    char a[100], b[100];

    s21_sprintf(a, "%% 50%%");
    sprintf(b, "%% 50%%");
    ck_assert_str_eq(a, b);
}
END_TEST

START_TEST(test_sscanf_d_u_f_c_s_percent) {
    int d;
    unsigned int u;
    float f;
    char c;
    char s[20];

    s21_sscanf("42", "%d", &d);
    sscanf("42", "%d", &d);
    ck_assert_int_eq(d, 42);

    s21_sscanf("123", "%u", &u);
    sscanf("123", "%u", &u);
    ck_assert_uint_eq(u, 123);

    s21_sscanf("3.14", "%f", &f);
    sscanf("3.14", "%f", &f);
    ck_assert_float_eq_tol(f, 3.14, 1e-6);

    s21_sscanf("A", "%c", &c);
    sscanf("A", "%c", &c);
    ck_assert_int_eq(c, 'A');

    s21_sscanf("hello", "%s", s);
    sscanf("hello", "%s", s);
    ck_assert_str_eq(s, "hello");
}
END_TEST

START_TEST(test_sscanf_width_length) {
    short sh;
    long l;
    unsigned long ul;

    s21_sscanf("123 456 789", "%hd %ld %lu", &sh, &l, &ul);
    sscanf("123 456 789", "%hd %ld %lu", &sh, &l, &ul);
    ck_assert_int_eq(sh, 123);
    ck_assert_int_eq(l, 456);
    ck_assert_uint_eq(ul, 789);
}
END_TEST


Suite *string_suite(void) {
    Suite *s = suite_create("s21_string");

    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_memchr);
    tcase_add_test(tc_core, test_memcmp);
    tcase_add_test(tc_core, test_memcpy);
    tcase_add_test(tc_core, test_memset);
    tcase_add_test(tc_core, test_strncat);
    tcase_add_test(tc_core, test_strchr);
    tcase_add_test(tc_core, test_strncmp);
    tcase_add_test(tc_core, test_strncpy);
    tcase_add_test(tc_core, test_strcspn);
    tcase_add_test(tc_core, test_strlen);
    tcase_add_test(tc_core, test_strpbrk);
    tcase_add_test(tc_core, test_strrchr);
    tcase_add_test(tc_core, test_strstr);
    tcase_add_test(tc_core, test_strtok);
    tcase_add_test(tc_core, test_to_upper);
    tcase_add_test(tc_core, test_to_lower);
    tcase_add_test(tc_core, test_insert);
    tcase_add_test(tc_core, test_trim);
    suite_add_tcase(s, tc_core);

    TCase *tc_sprintf = tcase_create("Sprintf");
    // tcase_add_test(tc_sprintf, test_sprintf_d);
    // tcase_add_test(tc_sprintf, test_sprintf_u);
    tcase_add_test(tc_sprintf, test_sprintf_f);
    tcase_add_test(tc_sprintf, test_sprintf_s);
    tcase_add_test(tc_sprintf, test_sprintf_c);
    tcase_add_test(tc_sprintf, test_sprintf_percent);
    suite_add_tcase(s, tc_sprintf);

    TCase *tc_sscanf = tcase_create("Sscanf");
    tcase_add_test(tc_sscanf, test_sscanf_d_u_f_c_s_percent);
    tcase_add_test(tc_sscanf, test_sscanf_width_length);
    suite_add_tcase(s, tc_sscanf);

    return s;
}



int main(void) {
    int failed;
    Suite *s;
    SRunner *runner;

    s = string_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);  // вот тут была ошибка

    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}