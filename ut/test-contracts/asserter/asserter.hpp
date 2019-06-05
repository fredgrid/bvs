/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>

class [[bvsio::contract]] asserter : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action]]
   void procassert( int8_t condition, std::string message );

   [[bvsio::action]]
   void provereset();
};
