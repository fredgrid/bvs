/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/bvsio.hpp>
#include <bvsio/singleton.hpp>
#include <bvsio/asset.hpp>

// Extacted from bvsio.token contract:
namespace bvsio {
   class [[bvsio::contract("bvsio.token")]] token : public bvsio::contract {
   public:
      using bvsio::contract::contract;

      [[bvsio::action]]
      void transfer( bvsio::name        from,
                     bvsio::name        to,
                     bvsio::asset       quantity,
                     const std::string& memo );
      using transfer_action = bvsio::action_wrapper<"transfer"_n, &token::transfer>;
   };
}

// This contract:
class [[bvsio::contract]] proxy : public bvsio::contract {
public:
   proxy( bvsio::name self, bvsio::name first_receiver, bvsio::datastream<const char*> ds );

   [[bvsio::action]]
   void setowner( bvsio::name owner, uint32_t delay );

   [[bvsio::on_notify("bvsio.token::transfer")]]
   void on_transfer( bvsio::name        from,
                     bvsio::name        to,
                     bvsio::asset       quantity,
                     const std::string& memo );

   [[bvsio::on_notify("bvsio::onerror")]]
   void on_error( uint128_t sender_id, bvsio::ignore<std::vector<char>> sent_trx );

   struct [[bvsio::table]] config {
      bvsio::name owner;
      uint32_t    delay   = 0;
      uint32_t    next_id = 0;

      BVSLIB_SERIALIZE( config, (owner)(delay)(next_id) )
   };

   using config_singleton = bvsio::singleton< "config"_n,  config >;

protected:
   config_singleton _config;
};
