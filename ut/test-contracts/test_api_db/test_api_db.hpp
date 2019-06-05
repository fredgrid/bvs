/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>

class [[bvsio::contract]] test_api_db : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action("pg")]]
   void primary_i64_general();

   [[bvsio::action("pl")]]
   void primary_i64_lowerbound();

   [[bvsio::action("pu")]]
   void primary_i64_upperbound();

   [[bvsio::action("s1g")]]
   void idx64_general();

   [[bvsio::action("s1l")]]
   void idx64_lowerbound();

   [[bvsio::action("s1u")]]
   void idx64_upperbound();

   [[bvsio::action("tia")]]
   void test_invalid_access( bvsio::name code, uint64_t val, uint32_t index, bool store );

   [[bvsio::action("sdnancreate")]]
   void idx_double_nan_create_fail();

   [[bvsio::action("sdnanmodify")]]
   void idx_double_nan_modify_fail();

   [[bvsio::action("sdnanlookup")]]
   void idx_double_nan_lookup_fail( uint32_t lookup_type );

   [[bvsio::action("sk32align")]]
   void misaligned_secondary_key256_tests();

};
