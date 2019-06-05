/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>

class [[bvsio::contract]] test_api_multi_index : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action("s1g")]]
   void idx64_general();

   [[bvsio::action("s1store")]]
   void idx64_store_only();

   [[bvsio::action("s1check")]]
   void idx64_check_without_storing();

   [[bvsio::action("s1findfail1")]]
   void idx64_require_find_fail();

   [[bvsio::action("s1findfail2")]]
   void idx64_require_find_fail_with_msg();

   [[bvsio::action("s1findfail3")]]
   void idx64_require_find_sk_fail();

   [[bvsio::action("s1findfail4")]]
   void idx64_require_find_sk_fail_with_msg();

   [[bvsio::action("s1pkend")]]
   void idx64_pk_iterator_exceed_end();

   [[bvsio::action("s1skend")]]
   void idx64_sk_iterator_exceed_end();

   [[bvsio::action("s1pkbegin")]]
   void idx64_pk_iterator_exceed_begin();

   [[bvsio::action("s1skbegin")]]
   void idx64_sk_iterator_exceed_begin();

   [[bvsio::action("s1pkref")]]
   void idx64_pass_pk_ref_to_other_table();

   [[bvsio::action("s1skref")]]
   void idx64_pass_sk_ref_to_other_table();

   [[bvsio::action("s1pkitrto")]]
   void idx64_pass_pk_end_itr_to_iterator_to();

   [[bvsio::action("s1pkmodify")]]
   void idx64_pass_pk_end_itr_to_modify();

   [[bvsio::action("s1pkerase")]]
   void idx64_pass_pk_end_itr_to_erase();

   [[bvsio::action("s1skitrto")]]
   void idx64_pass_sk_end_itr_to_iterator_to();

   [[bvsio::action("s1skmodify")]]
   void idx64_pass_sk_end_itr_to_modify();

   [[bvsio::action("s1skerase")]]
   void idx64_pass_sk_end_itr_to_erase();

   [[bvsio::action("s1modpk")]]
   void idx64_modify_primary_key();

   [[bvsio::action("s1exhaustpk")]]
   void idx64_run_out_of_avl_pk();

   [[bvsio::action("s1skcache")]]
   void idx64_sk_cache_pk_lookup();

   [[bvsio::action("s1pkcache")]]
   void idx64_pk_cache_sk_lookup();

   [[bvsio::action("s2g")]]
   void idx128_general();

   [[bvsio::action("s2store")]]
   void idx128_store_only();

   [[bvsio::action("s2check")]]
   void idx128_check_without_storing();

   [[bvsio::action("s2autoinc")]]
   void idx128_autoincrement_test();

   [[bvsio::action("s2autoinc1")]]
   void idx128_autoincrement_test_part1();

   [[bvsio::action("s2autoinc2")]]
   void idx128_autoincrement_test_part2();

   [[bvsio::action("s3g")]]
   void idx256_general();

   [[bvsio::action("sdg")]]
   void idx_double_general();

   [[bvsio::action("sldg")]]
   void idx_long_double_general();

};
