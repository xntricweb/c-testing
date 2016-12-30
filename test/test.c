#include "test.h"

#define expectResults(STATUS) do {    \
if (results != STATUS) {          \
  printf("UNEXPECTED RESULTS!");  \
  return FAILED;                  \
}} while(0)

test(TESTING, {
  it("should pass a test", { });
  expectResults(PASSED);

  recover("shouldn't have to recover from a passed test", {
    notify("RECOVERY SHOULD NOT HAVE RUN!");
    return FAILED;
  });

  it("should fail a test", {
    fail();
  });
  expectResults(FAILED);

  it("shouldn't run this test", {
    notify("skip test after failure failed!");
    return FAILED;
  });

  expectResults(FAILED);

  recover("should recover from a failure", { pass(); });
  expectResults(PASSED);

  it("should procede normally after recovery", { });
  expectResults(PASSED);

  it("should provide equality testing", {
    assert(1 == 1, "this should not be displayed");
  });
  expectResults(PASSED);

  it("should fail equality testing", {
    assert(1 == 0, "this should fail");
    notify("This line should not have been executed quiting!");
    return FAILED;
  });
  expectResults(FAILED);

  recover("should have to recover from failed test", { pass(); });

  it("should allow cleanup tasks if an assertion fails", {
    int x = 1;
    wrap({
      assert(x > 2, "this should fail.");
    });
    x = 0;
  })
});

int main() {

  return run(TESTING);
}
