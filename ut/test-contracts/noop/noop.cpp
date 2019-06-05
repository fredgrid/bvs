/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#include "noop.hpp"

using namespace bvsio;

void noop::anyaction( name                       from,
                      const ignore<std::string>& type,
                      const ignore<std::string>& data )
{
   require_auth( from );
}
