#ifndef _IP_TOOL_INCLUDE_TEST_H
#define _IP_TOOL_INCLUDE_TEST_H

#include <stdio.h>

#define PASSED 1
#define FAILED 0

#define START_SUB_TEST(DESCRIPTION)   \
char *subTestDescription = DESCRIPTION

#define STOP_SUB_TEST() \
log("      %s... %s\n\n", subTestDescription, results?"success": "fail")

#define is(EXPRESSION, DESCRIPTION, DEFINITION) do {  \
  if (EXPRESSION) {                                     \
    START_SUB_TEST(DESCRIPTION);                        \
    do { DEFINITION; } while(0);                                    \
    STOP_SUB_TEST();                              \
  }                                               \
} while(0)

#define it(DESCRIPTION, DEFINITION) \
is(results==PASSED, DESCRIPTION, DEFINITION)

#define recover(DESCRIPTION, DEFINITION) \
is(results!=PASSED, DESCRIPTION, DEFINITION)

#define log(FORMAT, ...) printf(FORMAT, __VA_ARGS__)

#define DEFINE_TESTS(DESCRIPTION, DEF)        \
void LoadTestDefinitions() {                  \
  setModuleDescription(DESCRIPTION);          \
  DEF                                         \
}

#define TEST_START(NAME)                      \
int results = 1;                              \
int sub_test_count = 0;                       \
int sub_tests_complete = 0;                   \
log("  Starting test %s\n", #NAME)

#define TEST_COMPLETE(NAME)                             \
if (results) {                                          \
  log("Test " #NAME " completed successfully\n\n");  \
} else {                                                \
  log("TEST FAILED!!!");                             \
}                                                       \
return results;

#define TEST(NAME, ...) int NAME(__VA_ARGS__)

#define test(NAME, DEFINITION, ...) \
TEST(NAME, __VA_ARGS__) {      \
  TEST_START(NAME);                 \
  if(1) DEFINITION                  \
  TEST_COMPLETE(NAME);              \
}                                   \
TEST(NAME, __VA_ARGS__)

#define run(NAME, ...) NAME(__VA_ARGS__)

#define fail() results = FAILED
#define pass() results = PASSED

#define assert(expr, msg)  \
if (!(expr)) { \
  log("        " msg ". expected(" #expr ")\n"); \
  fail(); \
  break; \
}

#define wrap(DEFINITION) do DEFINITION while(0)

#endif  // _IP_TOOL_INCLUDE_TEST_H
