/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "test/tests/api/utilTests.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "test/crossPlatformTestRunner.hpp"

void testUtil() {
  using namespace okapi;
  using namespace snowhouse;

  {
    test_printf("Testing ipow");

    test_printf("Integer tests");
    test("0^0 == 1", TEST_BODY(AssertThat, ipow(0, 0), Equals(1)));
    test("0^1 == 0", TEST_BODY(AssertThat, ipow(0, 1), Equals(0)));
    test("1^0 == 1", TEST_BODY(AssertThat, ipow(1, 0), Equals(1)));
    test("1^1 == 1", TEST_BODY(AssertThat, ipow(1, 1), Equals(1)));
    test("2^1 == 2", TEST_BODY(AssertThat, ipow(2, 1), Equals(2)));
    test("2^2 == 4", TEST_BODY(AssertThat, ipow(2, 2), Equals(4)));

    test_printf("Floating point tests");
    test("0.5^1 == 0.5", TEST_BODY(AssertThat, ipow(0.5, 1), EqualsWithDelta(0.5, 0.0001)));
    test("2.5^2 == 6.25", TEST_BODY(AssertThat, ipow(2.5, 2), EqualsWithDelta(6.25, 0.0001)));
  }

  {
    test_printf("Testing cutRange");

    test("1 : [-2, 2] -> 0", TEST_BODY(AssertThat, cutRange(1, -2, 2), EqualsWithDelta(2, 0.0001)));
    test("2 : [-2, 2] -> 0", TEST_BODY(AssertThat, cutRange(2, -2, 2), EqualsWithDelta(2, 0.0001)));
    test("0 : [-2, 2] -> 0", TEST_BODY(AssertThat, cutRange(0, -2, 2), EqualsWithDelta(2, 0.0001)));
    test("-2 : [-2, 2] -> 0",
         TEST_BODY(AssertThat, cutRange(-2, -2, 2), EqualsWithDelta(-2, 0.0001)));
    test("-3 : [-2, 2] -> -3",
         TEST_BODY(AssertThat, cutRange(-3, -2, 2), EqualsWithDelta(-3, 0.0001)));
    test("3 : [-2, 2] -> -3",
         TEST_BODY(AssertThat, cutRange(3, -2, 2), EqualsWithDelta(3, 0.0001)));
  }

  {
    test_printf("Testing deadband");

    test("0 : [-2, 2] -> 0", TEST_BODY(AssertThat, deadband(0, -2, 2), EqualsWithDelta(0, 0.0001)));
    test("1 : [-2, 2] -> 0", TEST_BODY(AssertThat, deadband(1, -2, 2), EqualsWithDelta(0, 0.0001)));
    test("2 : [-2, 2] -> 0", TEST_BODY(AssertThat, deadband(2, -2, 2), EqualsWithDelta(0, 0.0001)));
    test("-2 : [-2, 2] -> 0",
         TEST_BODY(AssertThat, deadband(-2, -2, 2), EqualsWithDelta(0, 0.0001)));
    test("3 : [-2, 2] -> 3", TEST_BODY(AssertThat, deadband(3, -2, 2), EqualsWithDelta(3, 0.0001)));
    test("-3 : [-2, 2] -> -3",
         TEST_BODY(AssertThat, deadband(-3, -2, 2), EqualsWithDelta(-3, 0.0001)));
  }

  {
    test_printf("Testing remapRange");

    test("0 : [-1, 1] -> [-2, 2]",
         TEST_BODY(AssertThat, remapRange(0, -1, 1, -2, 2), EqualsWithDelta(0, 0.0001)));
    test("0.1 : [-1, 1] -> [-2, 2]",
         TEST_BODY(AssertThat, remapRange(0.1, -1, 1, -2, 2), EqualsWithDelta(0.2, 0.0001)));
    test("-0.1 : [-1, 1] -> [2, -2]",
         TEST_BODY(AssertThat, remapRange(-0.1, -1, 1, 2, -2), EqualsWithDelta(0.2, 0.0001)));
    test("0 : [-1, 1] -> [-5, 2]",
         TEST_BODY(AssertThat, remapRange(0, -1, 1, -5, 2), EqualsWithDelta(-1.5, 0.0001)));
  }
}
