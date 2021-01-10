// file      : examples/cxx/parser/multiroot/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include "protocol.hxx"
#include "protocol-pskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "protocol-pimpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "protocol-pimpl-tiein.hxx"
#else
#  error this example requires mixin or tiein parser reuse support
#endif

using std::cerr;
using std::endl;
using xml_schema::ro_string;

namespace protocol
{
  // We are going to use our own "type ids" for the request
  // types. You could instead use dynamic_cast if your system
  // provides RTTI.
  //
  enum request_type
  {
    unknown_type,
    balance_type,
    withdraw_type
  };

  // Customize the xml_schema::document_pimpl object to handle our protocol
  // vocabulary with multiple root elements.
  //
  class document_pimpl: public xml_schema::document_pimpl
  {
  public:
    document_pimpl (balance_pskel& balance_p, withdraw_pskel& withdraw_p)
        : result_type_ (unknown_type),
          balance_p_ (balance_p),
          withdraw_p_ (withdraw_p)
    {
    }

    request_type
    result_type () const
    {
      return result_type_;
    }

    request*
    result ()
    {
      return result_.release ();
    }

  protected:
    // This function is called to obtain the root element type parser.
    // If the returned pointed is 0 then the whole document content
    // is ignored. Note that the signature of this function varies
    // depending on whether the runtime was built with polymorphism
    // support.
    //
    virtual xml_schema::parser_base*
#ifndef XSDE_POLYMORPHIC
    start_root_element (const ro_string& ns,
                        const ro_string& name)
#else
    start_root_element (const ro_string& ns,
                        const ro_string& name,
                        const char* /* xsi:type */)
#endif
    {
      if (ns == "http://www.codesynthesis.com/protocol")
      {
        if (name == "balance")
        {
          balance_p_.pre ();
          return &balance_p_;
        }
        else if (name == "withdraw")
        {
          balance_p_.pre ();
          return &withdraw_p_;
        }

        cerr << "ignoring unknown request: " << name << endl;
        return 0;
      }
      else
      {
        // This document is from the wrong namespace. If the runtime and
        // the generated code are built with validation enabled then we
        // can set an XML Schema error.
        //
#ifdef XSDE_PARSER_VALIDATION
        context_.schema_error (
          xml_schema::parser_schema_error::unexpected_element);
#endif
        return 0;
      }
    }

    // This function is called to indicate the completion of document
    // parsing. The parser argument contains the pointer returned by
    // start_root_element.
    //
    virtual void
    end_root_element (const ro_string& /* ns */,
                      const ro_string& /* name */,
                      xml_schema::parser_base* parser)
    {
      // We could have handled the result directly in this function
      // instead of storing it in the result_ variable.
      //
      if (parser == &balance_p_)
      {
        result_type_ = balance_type;
        result_.reset (balance_p_.post_balance ());
      }
      else if (parser == &withdraw_p_)
      {
        result_type_ = withdraw_type;
        result_.reset (withdraw_p_.post_withdraw ());
      }
      else
      {
        result_type_ = unknown_type;
        result_.reset (0);
      }
    }


  public:
    // If we need to be able to reset and reuse the parser after
    // an error then we also need to override reset() and reset
    // the root parsers. We can also get smarter here by caching
    // the parser that was used last and only reset that. Note
    // that you always need to call _reset() from the base.
    //
    virtual void
    reset ()
    {
      xml_schema::document_pimpl::reset ();

      balance_p_._reset ();
      withdraw_p_._reset ();
    }

  private:
    request_type result_type_;
    std::auto_ptr<request> result_;

    balance_pskel& balance_p_;
    withdraw_pskel& withdraw_p_;
  };
}


int
main (int argc, char* argv[])
{
  const char* input;

  if (argc < 2)
  {
    input = "STDIN";
    cerr << "XML file not specified, reading from STDIN" << endl;
  }
  else
    input = argv[1];

  try
  {
    using namespace protocol;

    // Construct the parser.
    //
    xml_schema::unsigned_int_pimpl unsigned_int_p;

    balance_pimpl balance_p;
    withdraw_pimpl withdraw_p;

    balance_p.parsers (unsigned_int_p); // account

    withdraw_p.parsers (unsigned_int_p,  // account
                        unsigned_int_p); // amount

    // Parse the XML instance document.
    //
    document_pimpl doc_p (balance_p, withdraw_p);

    // pre() and post() will be called as part of the start_root_element()
    // and end_root_element() calls.
    //
    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);

    std::auto_ptr<request> r (doc_p.result ());
    request_type t = doc_p.result_type ();

    // Let's print what we've got.
    //
    switch (t)
    {
    case balance_type:
      {
        balance* b = static_cast<balance*> (r.get ());
        cerr << "balance request for acc# " << b->account () << endl;
        break;
      }
    case withdraw_type:
      {
        withdraw* w = static_cast<withdraw*> (r.get ());
        cerr << "withdrawal request for acc# " << w->account () << ", "
             << "amount: " << w->amount () << endl;
        break;
      }
    case unknown_type:
      {
        cerr << "unknown request" << endl;
        break;
      }
    }
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << input << ":" << e.line () << ":" << e.column () << ": "
         << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << input << ": unable to open or read failure" << endl;
    return 1;
  }

  return 0;
}
