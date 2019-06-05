/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>

class [[bvsio::contract]] noop : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action]]
   void anyaction( bvsio::name                       from,
                   const bvsio::ignore<std::string>& type,
                   const bvsio::ignore<std::string>& data );
};
