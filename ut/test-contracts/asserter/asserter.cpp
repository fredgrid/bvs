/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#include "asserter.hpp"

using namespace bvsio;

static int global_variable = 45;

void asserter::procassert( int8_t condition, std::string message ) {
   check( condition != 0, message );
}

void asserter::provereset() {
   check( global_variable == 45, "Global Variable Initialized poorly" );
   global_variable = 100;
}
