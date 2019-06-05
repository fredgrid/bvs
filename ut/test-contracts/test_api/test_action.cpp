/**
 * @file action_test.cpp
 * @copyright defined in bvs/LICENSE
 */
#include <bvsiolib/action.hpp>
#include <bvsiolib/chain.h>
#include <bvsiolib/crypto.h>
#include <bvsiolib/datastream.hpp>
#include <bvsiolib/db.h>
#include <bvsiolib/bvsio.hpp>
#include <bvsiolib/print.hpp>
#include <bvsiolib/privileged.h>
#include <bvsiolib/transaction.hpp>

#include "test_api.hpp"

using namespace bvsio;

void test_action::read_action_normal() {

   char buffer[100];
   uint32_t total = 0;

   bvsio_assert( action_data_size() == sizeof(dummy_action), "action_size() == sizeof(dummy_action)" );

   total = read_action_data( buffer, 30 );
   bvsio_assert( total == sizeof(dummy_action) , "read_action(30)" );

   total = read_action_data( buffer, 100 );
   bvsio_assert(total == sizeof(dummy_action) , "read_action(100)" );

   total = read_action_data(buffer, 5);
   bvsio_assert( total == 5 , "read_action(5)" );

   total = read_action_data(buffer, sizeof(dummy_action) );
   bvsio_assert( total == sizeof(dummy_action), "read_action(sizeof(dummy_action))" );

   dummy_action *dummy13 = reinterpret_cast<dummy_action *>(buffer);

   bvsio_assert( dummy13->a == DUMMY_ACTION_DEFAULT_A, "dummy13->a == DUMMY_ACTION_DEFAULT_A" );
   bvsio_assert( dummy13->b == DUMMY_ACTION_DEFAULT_B, "dummy13->b == DUMMY_ACTION_DEFAULT_B" );
   bvsio_assert( dummy13->c == DUMMY_ACTION_DEFAULT_C, "dummy13->c == DUMMY_ACTION_DEFAULT_C" );
}

void test_action::test_dummy_action() {
   char buffer[100];
   int total = 0;

   // get_action
   total = get_action( 1, 0, buffer, 0 );
   total = get_action( 1, 0, buffer, static_cast<size_t>(total) );
   bvsio_assert( total > 0, "get_action failed" );
   bvsio::action act = bvsio::get_action( 1, 0 );
   bvsio_assert( act.authorization.back().actor == "testapi"_n, "incorrect permission actor" );
   bvsio_assert( act.authorization.back().permission == "active"_n, "incorrect permission name" );
   bvsio_assert( bvsio::pack_size(act) == static_cast<size_t>(total), "pack_size does not match get_action size" );
   bvsio_assert( act.account == "testapi"_n, "expected testapi account" );

   dummy_action dum13 = act.data_as<dummy_action>();

   if ( dum13.b == 200 ) {
      // attempt to access context free only api
      get_context_free_data( 0, nullptr, 0 );
      bvsio_assert( false, "get_context_free_data() not allowed in non-context free action" );
   } else {
      bvsio_assert( dum13.a == DUMMY_ACTION_DEFAULT_A, "dum13.a == DUMMY_ACTION_DEFAULT_A" );
      bvsio_assert( dum13.b == DUMMY_ACTION_DEFAULT_B, "dum13.b == DUMMY_ACTION_DEFAULT_B" );
      bvsio_assert( dum13.c == DUMMY_ACTION_DEFAULT_C, "dum13.c == DUMMY_ACTION_DEFAULT_C" );
   }
}

void test_action::read_action_to_0() {
   read_action_data( (void *)0, action_data_size() );
}

void test_action::read_action_to_64k() {
   read_action_data( (void *)((1<<16)-2), action_data_size());
}

void test_action::test_cf_action() {

   bvsio::action act = bvsio::get_action( 0, 0 );
   cf_action cfa = act.data_as<cf_action>();
   if ( cfa.payload == 100 ) {
      // verify read of get_context_free_data, also verifies system api access
      int size = get_context_free_data( cfa.cfd_idx, nullptr, 0 );
      bvsio_assert( size > 0, "size determination failed" );
      std::vector<char> cfd( static_cast<size_t>(size) );
      size = get_context_free_data( cfa.cfd_idx, &cfd[0], static_cast<size_t>(size) );
      bvsio_assert(static_cast<size_t>(size) == cfd.size(), "get_context_free_data failed" );
      uint32_t v = bvsio::unpack<uint32_t>( &cfd[0], cfd.size() );
      bvsio_assert( v == cfa.payload, "invalid value" );

      // verify crypto api access
      capi_checksum256 hash;
      char test[] = "test";
      sha256( test, sizeof(test), &hash );
      assert_sha256( test, sizeof(test), &hash );
      // verify action api access
      action_data_size();
      // verify console api access
      bvsio::print("test\n");
      // verify memory api access
      uint32_t i = 42;
      memccpy( &v, &i, sizeof(i), sizeof(i) );
      // verify transaction api access
      bvsio_assert(transaction_size() > 0, "transaction_size failed");
      // verify softfloat api access
      float f1 = 1.0f, f2 = 2.0f;
      float f3 = f1 + f2;
      bvsio_assert( f3 >  2.0f, "Unable to add float.");
      // verify context_free_system_api
      bvsio_assert( true, "verify bvsio_assert can be called" );


   } else if ( cfa.payload == 200 ) {
      // attempt to access non context free api, privileged_api
      is_privileged(act.name.value);
      bvsio_assert( false, "privileged_api should not be allowed" );
   } else if ( cfa.payload == 201 ) {
      // attempt to access non context free api, producer_api
      get_active_producers( nullptr, 0 );
      bvsio_assert( false, "producer_api should not be allowed" );
   } else if ( cfa.payload == 202 ) {
      // attempt to access non context free api, db_api
      db_store_i64( "testapi"_n.value, "testapi"_n.value, "testapi"_n.value, 0, "test", 4 );
      bvsio_assert( false, "db_api should not be allowed" );
   } else if ( cfa.payload == 203 ) {
      // attempt to access non context free api, db_api
      uint64_t i = 0;
      db_idx64_store( "testapi"_n.value, "testapi"_n.value, "testapi"_n.value, 0, &i );
      bvsio_assert( false, "db_api should not be allowed" );
   } else if ( cfa.payload == 204 ) {
      db_find_i64( "testapi"_n.value, "testapi"_n.value, "testapi"_n.value, 1 );
      bvsio_assert( false, "db_api should not be allowed" );
   } else if ( cfa.payload == 205 ) {
      // attempt to access non context free api, send action
      bvsio::action dum_act;
      dum_act.send();
      bvsio_assert( false, "action send should not be allowed" );
   } else if ( cfa.payload == 206 ) {
      bvsio::require_auth("test"_n);
      bvsio_assert( false, "authorization_api should not be allowed" );
   } else if ( cfa.payload == 207 ) {
      now();
      bvsio_assert( false, "system_api should not be allowed" );
   } else if ( cfa.payload == 208 ) {
      current_time();
      bvsio_assert( false, "system_api should not be allowed" );
   } else if ( cfa.payload == 209 ) {
      publication_time();
      bvsio_assert( false, "system_api should not be allowed" );
   } else if ( cfa.payload == 210 ) {
      send_inline( (char*)"hello", 6 );
      bvsio_assert( false, "transaction_api should not be allowed" );
   } else if ( cfa.payload == 211 ) {
      send_deferred( "testapi"_n.value, "testapi"_n.value, "hello", 6, 0 );
      bvsio_assert( false, "transaction_api should not be allowed" );
   }

}

void test_action::require_notice( uint64_t receiver, uint64_t code, uint64_t action ) {
   (void)code;(void)action;
   if( receiver == "testapi"_n.value ) {
      bvsio::require_recipient( "acc1"_n );
      bvsio::require_recipient( "acc2"_n );
      bvsio::require_recipient( "acc1"_n, "acc2"_n );
      bvsio_assert( false, "Should've failed" );
   } else if ( receiver == "acc1"_n.value || receiver == "acc2"_n.value ) {
      return;
   }
   bvsio_assert( false, "Should've failed" );
}

void test_action::require_notice_tests( uint64_t receiver, uint64_t code, uint64_t action ) {
   bvsio::print( "require_notice_tests" );
   if( receiver == "testapi"_n.value ) {
      bvsio::print("require_recipient( \"acc5\"_n )");
      bvsio::require_recipient("acc5"_n);
   } else if( receiver == "acc5"_n.value ) {
      bvsio::print("require_recipient( \"testapi\"_n )");
      bvsio::require_recipient("testapi"_n);
   }
}

void test_action::require_auth() {
   prints("require_auth");
   bvsio::require_auth("acc3"_n);
   bvsio::require_auth("acc4"_n);
}

void test_action::assert_false() {
   bvsio_assert( false, "test_action::assert_false" );
}

void test_action::assert_true() {
   bvsio_assert( true, "test_action::assert_true" );
}

void test_action::assert_true_cf() {
   bvsio_assert( true, "test_action::assert_true" );
}

void test_action::test_abort() {
   abort();
   bvsio_assert( false, "should've aborted" );
}

void test_action::test_publication_time() {
   uint64_t pub_time = 0;
   uint32_t total = read_action_data( &pub_time, sizeof(uint64_t) );
   bvsio_assert( total == sizeof(uint64_t), "total == sizeof(uint64_t)" );
   bvsio_assert( pub_time == publication_time(), "pub_time == publication_time()" );
}

void test_action::test_current_receiver( uint64_t receiver, uint64_t code, uint64_t action ) {
   (void)code;(void)action;
   name cur_rec;
   read_action_data( &cur_rec, sizeof(name) );

   bvsio_assert( receiver == cur_rec.value, "the current receiver does not match" );
}

void test_action::test_current_time() {
   uint64_t tmp = 0;
   uint32_t total = read_action_data( &tmp, sizeof(uint64_t) );
   bvsio_assert( total == sizeof(uint64_t), "total == sizeof(uint64_t)" );
   bvsio_assert( tmp == current_time(), "tmp == current_time()" );
}

void test_action::test_assert_code() {
   uint64_t code = 0;
   uint32_t total = read_action_data(&code, sizeof(uint64_t));
   bvsio_assert( total == sizeof(uint64_t), "total == sizeof(uint64_t)" );
   bvsio_assert_code( false, code );
}

void test_action::test_ram_billing_in_notify( uint64_t receiver, uint64_t code, uint64_t action ) {
   uint128_t tmp = 0;
   uint32_t total = read_action_data( &tmp, sizeof(uint128_t) );
   bvsio_assert( total == sizeof(uint128_t), "total == sizeof(uint128_t)" );

   uint64_t to_notify = tmp >> 64;
   uint64_t payer = tmp & 0xFFFFFFFFFFFFFFFFULL;

   if( code == receiver ) {
      bvsio::require_recipient( name{to_notify} );
   } else {
      bvsio_assert( to_notify == receiver, "notified recipient other than the one specified in to_notify" );

      // Remove main table row if it already exists.
      int itr = db_find_i64( receiver, "notifytest"_n.value, "notifytest"_n.value, "notifytest"_n.value );
      if( itr >= 0 )
         db_remove_i64( itr );

      // Create the main table row simply for the purpose of charging code more RAM.
      if( payer != 0 )
         db_store_i64( "notifytest"_n.value, "notifytest"_n.value, payer, "notifytest"_n.value, &to_notify, sizeof(to_notify) );
   }
}
