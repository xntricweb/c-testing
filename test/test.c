#include "../test.h"

#define expectResults(STATUS) do {    \
if (results != STATUS) {          \
  printf("UNEXPECTED RESULTS!");  \
  return FAILED;                  \
}} while(0)

test(TESTING, {
  it("should pass a test", pass());
  expectResults(PASSED);

  it("shouldn't recover from a passed test", {
    recover("this should not have been displayed", fail());
  });

  it("should fail a test", {
    fail();
    if (!results) pass();
  });

  fail();

  recover("should recover from a failed test", { pass(); });

  it("should procede normally after recovery", { });

  it("should provide equality testing", {
    assert(1 == 1, "this is the error message and should not be displayed");
  });

  it("should fail equality testing", {
    do {assert(1 == 0, "this should fail");} while(0);
    if (!results) pass();
  });

  it("wrapping a failed assertion should allow code to run after", {
    wrap({
      assert(1 == 0, "this should fail");
    });
    pass();
  });
})

int main() {

  return run(TESTING);
}
