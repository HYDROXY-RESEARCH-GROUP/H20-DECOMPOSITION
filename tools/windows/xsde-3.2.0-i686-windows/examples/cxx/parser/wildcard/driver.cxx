// file      : examples/cxx/parser/wildcard/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string>
#include <memory>
#include <iostream>

#include "email-pskel.hxx"

#ifndef XSDE_REUSE_STYLE_TIEIN
#  error this example requires the tiein parser reuse support
#endif

using namespace std;
using xml_schema::ro_string;

namespace email
{
  class binary_pimpl: public binary_pskel
  {
  public:
    binary_pimpl ()
        : binary_pskel (&base_impl_)
    {
    }

    virtual void
    name (const string& n)
    {
      cerr << "binary: " << n << endl;
    }

    virtual void
    mime (const string& t)
    {
      cerr << "type:   " << t << endl;
    }

    virtual void
    post_binary ()
    {
      std::auto_ptr<xml_schema::buffer> buf (post_base64_binary ());

      cerr << "size:   " << buf->size () << endl
           << endl;
    }

  private:
    xml_schema::base64_binary_pimpl base_impl_;
  };

  class envelope_pimpl: public envelope_pskel
  {
  public:
    envelope_pimpl (xml_schema::unsigned_int_pskel& uint_p,
                    xml_schema::string_pskel& string_p,
                    binary_pskel& binary_p)
        : depth_ (0),
          uint_p_ (uint_p), string_p_ (string_p), binary_p_ (binary_p)
    {
    }

    virtual void
    to (const string& addr)
    {
      cerr << "To:        " << addr << endl;
    }

    virtual void
    from (const string& addr)
    {
      cerr << "From:      " << addr << endl;
    }

    virtual void
    subject (const string& s)
    {
      cerr << "Subject:   " << s << endl;
    }

    // Wildcard handling. All wildcard events are routed to the
    // _start_any_element, _end_any_element, _any_attribute, and
    // _any_characters functions. We can dynamically select a
    // parser from the _start_any_element after which all inner
    // content will be automatically routed to this parser. At
    // the end we will get a call to _end_any_element in which
    // we can call post(), clean up, etc.
    //
    // If we are not using exceptions or XML Schema validation
    // is enabled then we need to check for the error condition
    // and, if the (user) error was set in pre() or post(),
    // also copy the error code to the context. The _error_type()
    // function returns non-0 value if there an error pending.
    // The _copy_error() functions copies the error state to
    // the context.
    //
    // Finally, if the XSD runtime library was configured with
    // polymorphism support, then _start_any_element has a third
    // argument which is a dynamic type id that comes from xsi:type
    // or substitution groups.
    //
    virtual void
#ifndef XSDE_POLYMORPHIC
    _start_any_element (const ro_string& ns, const ro_string& name)
#else
    _start_any_element (const ro_string& ns,
                        const ro_string& name,
                        const char*)
#endif
    {
      // We use the depth_ counter to filter out nested elements
      // and attributes for the content matched by the wildcard
      // but which we don't know how to handle.
      //

      if (depth_++ == 0)
      {
        // Top-level (relative to this type) element matched by the
        // any wildcard.
        //
        xml_schema::parser_base* p = 0;

        if (ns == "http://www.codesynthesis.com/email")
        {
          if (name == "text")
          {
            p = &string_p_;
          }
          else if (name == "binary")
          {
            p = &binary_p_;
          }

          if (p != 0)
          {
            xml_schema::parser_context& ctx = _context ();

            p->pre ();

#ifndef XSDE_EXCEPTIONS
            if (p->_error_type ())
            {
              // Propagate the error.
              //
              p->_copy_error (ctx);
              return;
            }
#endif
            // Indicate transition to the nested parser.
            //
            ctx.nested_parser (p);
          }
        }

        if (p == 0)
        {
          cerr << "Unknown wildcard content: " << ns << "#" << name << endl;
        }
      }
    }

    virtual void
    _end_any_element (const ro_string& ns, const ro_string& name)
    {
      if (--depth_ == 0)
      {
        if (ns == "http://www.codesynthesis.com/email")
        {
          if (name == "text")
          {
            string text (string_p_.post_string ());

#ifndef XSDE_EXCEPTIONS
            if (string_p_._error_type ())
            {
              // Propagate the error.
              //
              string_p_._copy_error (_context ());
              return;
            }
#endif
            cerr << text << endl
                 << endl;
          }
          else if (name == "binary")
          {
            binary_p_.post_binary ();

#ifndef XSDE_EXCEPTIONS
            if (binary_p_._error_type ())
            {
              // Propagate the error.
              //
              binary_p_._copy_error (_context ());
              return;
            }
#endif
          }
        }
      }
    }

    virtual void
    _any_attribute (const ro_string& ns,
                    const ro_string& name,
                    const ro_string& value)
    {
      if (depth_ == 0)
      {
        // Top-level (relative to this type) attribute matched by the
        // anyAttribute wildcard.
        //
        if (ns == "http://www.codesynthesis.com/email" && name == "thread-id")
        {
          xml_schema::parser_context& ctx = _context ();

          uint_p_.pre ();

#ifndef XSDE_EXCEPTIONS
          if (uint_p_._error_type ())
          {
            uint_p_._copy_error (ctx);
            return;
          }
#endif

          uint_p_._pre_impl (ctx);

#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
          if (ctx.error_type ())
            return;
#endif

          uint_p_._characters (value);

#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
          if (ctx.error_type ())
            return;
#endif

          uint_p_._post_impl ();

#if defined(XSDE_PARSER_VALIDATION) || !defined(XSDE_EXCEPTIONS)
          if (ctx.error_type ())
            return;
#endif

          unsigned int tid = uint_p_.post_unsigned_int ();

#ifndef XSDE_EXCEPTIONS
          if (uint_p_._error_type ())
          {
            uint_p_._copy_error (ctx);
            return;
          }
#endif

          cerr << "Thread-id: " << tid << endl;
        }
      }
    }

    // If we need to be able to reset and reuse the parser after
    // an error then we also need to override _reset() and reset
    // the parsers that are used to handle wildcards. Note that
    // you always need to call _reset() from the base.
    //
    virtual void
    _reset ()
    {
      envelope_pskel::_reset ();

      depth_ = 0;
      uint_p_._reset ();
      string_p_._reset ();
      binary_p_._reset ();
    }

  private:
    std::size_t depth_;

    // Parsers for the unsigned int, string and binary types.
    //
  private:
    xml_schema::unsigned_int_pskel& uint_p_;
    xml_schema::string_pskel& string_p_;
    binary_pskel& binary_p_;
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
    // Construct the parser.
    //
    xml_schema::unsigned_int_pimpl unsigned_int_p;
    xml_schema::string_pimpl string_p;
    email::binary_pimpl binary_p;
    email::envelope_pimpl envelope_p (unsigned_int_p, string_p, binary_p);

    binary_p.parsers (string_p,  // name
                      string_p); // mime

    envelope_p.parsers (string_p,  // to
                        string_p,  // from
                        string_p); // subject

    // Parse the XML instance document.
    //
    xml_schema::document_pimpl doc_p (
      envelope_p,
      "http://www.codesynthesis.com/email",
      "message");

    envelope_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    envelope_p.post_envelope ();
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
