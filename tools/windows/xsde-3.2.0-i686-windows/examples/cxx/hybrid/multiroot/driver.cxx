// file      : examples/cxx/hybrid/multiroot/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "protocol.hxx"
#include "protocol-pimpl.hxx"

using namespace std;
using xml_schema::ro_string;

namespace protocol
{
  // We are going to use our own "type ids" for the request types.
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
    document_pimpl ()
        : result_type_ (unknown_type)
    {
    }

    request_type
    result_type () const
    {
      return result_type_;
    }

    protocol::balance
    balance () const
    {
      return balance_;
    }

    protocol::withdraw
    withdraw () const
    {
      return withdraw_;
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
        if (name == balance_p_.root_name ())
        {
          balance_p_.pre ();
          return &balance_p_.root_parser ();
        }
        else if (name == "withdraw")
        {
          balance_p_.pre ();
          return &withdraw_p_.root_parser ();
        }

        // Ignore unknown request.
        //
        return 0;
      }
      else
      {
        // This document is from the wrong namespace. If the runtime and
        // the generated code are built with validation enabled then we
        // can set an XML Schema error. Otherwise, we ignore it.
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
      // instead of storing it in the result variables.
      //
      if (parser == &balance_p_.root_parser ())
      {
        result_type_ = balance_type;
        balance_ = balance_p_.post ();
      }
      else if (parser == &withdraw_p_.root_parser ())
      {
        result_type_ = withdraw_type;
        withdraw_ = withdraw_p_.post ();
      }
      else
        result_type_ = unknown_type;
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

      balance_p_.reset ();
      withdraw_p_.reset ();
    }

  private:
    // Result.
    //
    request_type result_type_;
    protocol::balance balance_;
    protocol::withdraw withdraw_;

    // Parsers for various root elements.
    //
    balance_paggr balance_p_;
    withdraw_paggr withdraw_p_;
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

    // Parse.
    //
    document_pimpl doc_p;

    // pre() and post() are called as part of the start_root_element()
    // and end_root_element() calls.
    //
    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);

    // Print what we've got.
    //
    switch (doc_p.result_type ())
    {
    case balance_type:
      {
        balance b (doc_p.balance ());
        cerr << "balance request for acc# " << b.account () << endl;
        break;
      }
    case withdraw_type:
      {
        withdraw w (doc_p.withdraw ());
        cerr << "withdrawal request for acc# " << w.account () << ", "
             << "amount: " << w.amount () << endl;
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
