#ifndef _IP_TOOL_INCLUDE_TEST_H
#define _IP_TOOL_INCLUDE_TEST_H

#include <stdio.h>

#define PASSED 1
#define FAILED 0

#define START_SUB_TEST(DESCRIPTION)   \
notify("\tit %s...\n", DESCRIPTION)

#define STOP_SUB_TEST() \
if (results) notify("\tTEST PASSED\n");  \
else notify("\tTEST FAILED\n")

#define is(EXPRESSION, DESCRIPTION, DEFINITION) do {  \
  if (EXPRESSION) {                                     \
    START_SUB_TEST(DESCRIPTION);                        \
    DEFINITION                                    \
    STOP_SUB_TEST();                              \
  }                                               \
} while(0)

#define it(DESCRIPTION, DEFINITION) \
is(results==PASSED, DESCRIPTION, DEFINITION)

#define recover(DESCRIPTION, DEFINITION) \
is(results!=PASSED, DESCRIPTION, DEFINITION)

#define notify(FORMAT, ...) printf(FORMAT, __VA_ARGS__)

#define DEFINE_TESTS(DESCRIPTION, DEF)        \
void LoadTestDefinitions() {                  \
  setModuleDescription(DESCRIPTION);          \
  DEF                                         \
}

#define TEST_START(NAME)                      \
int results = 1;                              \
int sub_test_count = 0;                       \
int sub_tests_complete = 0;                   \
notify("Starting test %s\n", #NAME)

#define TEST_COMPLETE(NAME)                             \
if (results) {                                          \
  notify("Test " #NAME " completed successfully\n\n");  \
} else {                                                \
  notify("TEST FAILED!!!");                             \
}                                                       \
return results;

#define TEST_DECL(NAME, ...) int NAME(__VA_ARGS__)

#define test(NAME, DEFINITION, ...) \
TEST_DECL(NAME, __VA_ARGS__) {      \
  TEST_START(NAME);                 \
  if(1) DEFINITION                  \
  TEST_COMPLETE(NAME);              \
}                                   \
TEST_DECL(NAME, __VA_ARGS__)

#define run(NAME, ...) NAME(__VA_ARGS__)

#define fail() results = FAILED
#define pass() results = PASSED

// #define assertEquals(v1, v2, msg)   \
// if (v1 != v2) {                     \
//   notify("\t\t" msg ". (expected %i, found %i)\n", v1, v2);  \
//   fail();                           \
//   break;                            \
// }

#define assert(expr, msg)  \
if (!(expr)) { \
  notify("\t\t" msg ". expected(" #expr ")\n"); \
  fail(); \
  break; \
}

#define wrap(DEFINITION) do DEFINITION; while(0);

#endif  // _IP_TOOL_INCLUDE_TEST_H
