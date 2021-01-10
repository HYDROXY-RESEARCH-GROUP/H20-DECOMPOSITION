// file      : examples/cxx/parser/multiroot/protocol-pimpl-tiein.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef PROTOCOL_PIMPL_HXX
#define PROTOCOL_PIMPL_HXX

#include "protocol.hxx"
#include "protocol-pskel.hxx"

namespace protocol
{
  class request_pimpl: public request_pskel
  {
  public:
    virtual void
    account (unsigned int);

    virtual request*
    post_request ();

  public:
    unsigned int account_;
  };

  class balance_pimpl: public balance_pskel
  {
  public:
    balance_pimpl ();

    virtual balance*
    post_balance ();

  private:
    request_pimpl base_impl_;
  };

  class withdraw_pimpl: public withdraw_pskel
  {
  public:
    withdraw_pimpl ();

    virtual void
    amount (unsigned int);

    virtual withdraw*
    post_withdraw ();

  private:
    request_pimpl base_impl_;
    unsigned int amount_;
  };
}

#endif // PROTOCOL_PIMPL_HXX
