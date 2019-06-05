/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>

class [[bvsio::contract]] integration_test : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action]]
   void store( bvsio::name from, bvsio::name to, uint64_t num );

   struct [[bvsio::table("payloads")]] payload {
      uint64_t              key;
      std::vector<uint64_t> data;

      uint64_t primary_key()const { return key; }

      BVSLIB_SERIALIZE( payload, (key)(data) )
   };

   using payloads_table = bvsio::multi_index< "payloads"_n,  payload >;

};
