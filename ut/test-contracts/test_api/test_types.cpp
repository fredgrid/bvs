/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#include <bvsiolib/bvsio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   bvsio_assert( sizeof(int64_t)   ==  8, "int64_t size != 8"   );
   bvsio_assert( sizeof(uint64_t)  ==  8, "uint64_t size != 8"  );
   bvsio_assert( sizeof(uint32_t)  ==  4, "uint32_t size != 4"  );
   bvsio_assert( sizeof(int32_t)   ==  4, "int32_t size != 4"   );
   bvsio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   bvsio_assert( sizeof(int128_t)  == 16, "int128_t size != 16" );
   bvsio_assert( sizeof(uint8_t)   ==  1, "uint8_t size != 1"   );

   bvsio_assert( sizeof(bvsio::name) ==  8, "name size !=  8");
}

void test_types::char_to_symbol() {

   bvsio_assert( bvsio::name::char_to_value('1') ==  1, "bvsio::char_to_symbol('1') !=  1" );
   bvsio_assert( bvsio::name::char_to_value('2') ==  2, "bvsio::char_to_symbol('2') !=  2" );
   bvsio_assert( bvsio::name::char_to_value('3') ==  3, "bvsio::char_to_symbol('3') !=  3" );
   bvsio_assert( bvsio::name::char_to_value('4') ==  4, "bvsio::char_to_symbol('4') !=  4" );
   bvsio_assert( bvsio::name::char_to_value('5') ==  5, "bvsio::char_to_symbol('5') !=  5" );
   bvsio_assert( bvsio::name::char_to_value('a') ==  6, "bvsio::char_to_symbol('a') !=  6" );
   bvsio_assert( bvsio::name::char_to_value('b') ==  7, "bvsio::char_to_symbol('b') !=  7" );
   bvsio_assert( bvsio::name::char_to_value('c') ==  8, "bvsio::char_to_symbol('c') !=  8" );
   bvsio_assert( bvsio::name::char_to_value('d') ==  9, "bvsio::char_to_symbol('d') !=  9" );
   bvsio_assert( bvsio::name::char_to_value('e') == 10, "bvsio::char_to_symbol('e') != 10" );
   bvsio_assert( bvsio::name::char_to_value('f') == 11, "bvsio::char_to_symbol('f') != 11" );
   bvsio_assert( bvsio::name::char_to_value('g') == 12, "bvsio::char_to_symbol('g') != 12" );
   bvsio_assert( bvsio::name::char_to_value('h') == 13, "bvsio::char_to_symbol('h') != 13" );
   bvsio_assert( bvsio::name::char_to_value('i') == 14, "bvsio::char_to_symbol('i') != 14" );
   bvsio_assert( bvsio::name::char_to_value('j') == 15, "bvsio::char_to_symbol('j') != 15" );
   bvsio_assert( bvsio::name::char_to_value('k') == 16, "bvsio::char_to_symbol('k') != 16" );
   bvsio_assert( bvsio::name::char_to_value('l') == 17, "bvsio::char_to_symbol('l') != 17" );
   bvsio_assert( bvsio::name::char_to_value('m') == 18, "bvsio::char_to_symbol('m') != 18" );
   bvsio_assert( bvsio::name::char_to_value('n') == 19, "bvsio::char_to_symbol('n') != 19" );
   bvsio_assert( bvsio::name::char_to_value('o') == 20, "bvsio::char_to_symbol('o') != 20" );
   bvsio_assert( bvsio::name::char_to_value('p') == 21, "bvsio::char_to_symbol('p') != 21" );
   bvsio_assert( bvsio::name::char_to_value('q') == 22, "bvsio::char_to_symbol('q') != 22" );
   bvsio_assert( bvsio::name::char_to_value('r') == 23, "bvsio::char_to_symbol('r') != 23" );
   bvsio_assert( bvsio::name::char_to_value('s') == 24, "bvsio::char_to_symbol('s') != 24" );
   bvsio_assert( bvsio::name::char_to_value('t') == 25, "bvsio::char_to_symbol('t') != 25" );
   bvsio_assert( bvsio::name::char_to_value('u') == 26, "bvsio::char_to_symbol('u') != 26" );
   bvsio_assert( bvsio::name::char_to_value('v') == 27, "bvsio::char_to_symbol('v') != 27" );
   bvsio_assert( bvsio::name::char_to_value('w') == 28, "bvsio::char_to_symbol('w') != 28" );
   bvsio_assert( bvsio::name::char_to_value('x') == 29, "bvsio::char_to_symbol('x') != 29" );
   bvsio_assert( bvsio::name::char_to_value('y') == 30, "bvsio::char_to_symbol('y') != 30" );
   bvsio_assert( bvsio::name::char_to_value('z') == 31, "bvsio::char_to_symbol('z') != 31" );

   for(unsigned char i = 0; i<255; i++) {
      if( (i >= 'a' && i <= 'z') || (i >= '1' || i <= '5') ) continue;
      bvsio_assert( bvsio::name::char_to_value((char)i) == 0, "bvsio::char_to_symbol() != 0" );
   }
}

void test_types::string_to_name() {
   return;
   bvsio_assert( bvsio::name("a") == "a"_n, "bvsio::string_to_name(a)" );
   bvsio_assert( bvsio::name("ba") == "ba"_n, "bvsio::string_to_name(ba)" );
   bvsio_assert( bvsio::name("cba") == "cba"_n, "bvsio::string_to_name(cba)" );
   bvsio_assert( bvsio::name("dcba") == "dcba"_n, "bvsio::string_to_name(dcba)" );
   bvsio_assert( bvsio::name("edcba") == "edcba"_n, "bvsio::string_to_name(edcba)" );
   bvsio_assert( bvsio::name("fedcba") == "fedcba"_n, "bvsio::string_to_name(fedcba)" );
   bvsio_assert( bvsio::name("gfedcba") == "gfedcba"_n, "bvsio::string_to_name(gfedcba)" );
   bvsio_assert( bvsio::name("hgfedcba") == "hgfedcba"_n, "bvsio::string_to_name(hgfedcba)" );
   bvsio_assert( bvsio::name("ihgfedcba") == "ihgfedcba"_n, "bvsio::string_to_name(ihgfedcba)" );
   bvsio_assert( bvsio::name("jihgfedcba") == "jihgfedcba"_n, "bvsio::string_to_name(jihgfedcba)" );
   bvsio_assert( bvsio::name("kjihgfedcba") == "kjihgfedcba"_n, "bvsio::string_to_name(kjihgfedcba)" );
   bvsio_assert( bvsio::name("lkjihgfedcba") == "lkjihgfedcba"_n, "bvsio::string_to_name(lkjihgfedcba)" );
   bvsio_assert( bvsio::name("mlkjihgfedcba") == "mlkjihgfedcba"_n, "bvsio::string_to_name(mlkjihgfedcba)" );
}
