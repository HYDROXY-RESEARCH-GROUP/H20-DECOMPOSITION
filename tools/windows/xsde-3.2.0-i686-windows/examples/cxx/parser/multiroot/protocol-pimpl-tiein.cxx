// file      : examples/cxx/parser/multiroot/protocol-pimpl-tiein.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "protocol-pimpl-tiein.hxx"

namespace protocol
{
  // request_pimpl
  //
  void request_pimpl::
  account (unsigned int account)
  {
    account_ = account;
  }

  request* request_pimpl::
  post_request ()
  {
    // This parser is never used directly.
    //
    return 0;
  }

  // balance_pimpl
  //
  balance_pimpl::
  balance_pimpl ()
      : balance_pskel (&base_impl_)
  {
  }

  balance* balance_pimpl::
  post_balance ()
  {
    return new balance (base_impl_.account_);
  }

  // withdraw_pimpl
  //
  withdraw_pimpl::
  withdraw_pimpl ()
      : withdraw_pskel (&base_impl_)
  {
  }

  void withdraw_pimpl::
  amount (unsigned int amount)
  {
    amount_ = amount;
  }

  withdraw* withdraw_pimpl::
  post_withdraw ()
  {
    return new withdraw (base_impl_.account_, amount_);
  }
}

