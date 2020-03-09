find_package(Boost 1.58 COMPONENTS unit_test_framework REQUIRED)
include(UnitTest)

unit_test(NAME constants_test SRC constants_test.cpp DEPENDS observables)
unit_test(NAME arithmetic_test SRC arithmetic_test.cpp DEPENDS observables)
unit_test(NAME vector_test SRC vector_test.cpp DEPENDS observables)
