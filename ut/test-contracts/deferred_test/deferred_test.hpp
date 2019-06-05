/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>
#include <vector>

class [[bvsio::contract]] deferred_test : public bvsio::contract {
public:
   using bvsio::contract::contract;

   [[bvsio::action]]
   void defercall( bvsio::name payer, uint64_t sender_id, bvsio::name contract, uint64_t payload );

   [[bvsio::action]]
   void deferfunc( uint64_t payload );
   using deferfunc_action = bvsio::action_wrapper<"deferfunc"_n, &deferred_test::deferfunc>;

   [[bvsio::action]]
   void inlinecall( bvsio::name contract, bvsio::name authorizer, uint64_t payload );

   [[bvsio::on_notify("bvsio::onerror")]]
   void on_error( uint128_t sender_id, bvsio::ignore<std::vector<char>> sent_trx );
};
