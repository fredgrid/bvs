/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>

class [[bvsio::contract]] payloadless : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action]]
   void doit();
};
