/**
 *  @file
 *  @copyright defined in bvs/LICENSE
 */
#pragma once

#include <bvsio/chain/types.hpp>
#include <bvsio/chain/contract_types.hpp>

namespace bvsio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_bvsio_newaccount(apply_context&);
   void apply_bvsio_updateauth(apply_context&);
   void apply_bvsio_deleteauth(apply_context&);
   void apply_bvsio_linkauth(apply_context&);
   void apply_bvsio_unlinkauth(apply_context&);

   /*
   void apply_bvsio_postrecovery(apply_context&);
   void apply_bvsio_passrecovery(apply_context&);
   void apply_bvsio_vetorecovery(apply_context&);
   */

   void apply_bvsio_setcode(apply_context&);
   void apply_bvsio_setabi(apply_context&);

   void apply_bvsio_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace bvsio::chain
