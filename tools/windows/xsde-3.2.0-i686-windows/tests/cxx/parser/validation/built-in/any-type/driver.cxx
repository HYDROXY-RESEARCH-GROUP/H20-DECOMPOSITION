// file      : tests/cxx/parser/validation/built-in/any-type/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the anyType and anySimpleType validation.
//

#include <string>
#include <iostream>

#include "test-pskel.hxx"

using namespace std;
using namespace test;
using xml_schema::ro_string;

struct any_type_pimpl: xml_schema::any_type_pimpl
{
  virtual void
  pre ()
  {
    cout << "{" << endl;
  }

  virtual void
#ifndef XSDE_POLYMORPHIC
  _start_any_element (ro_string const&, ro_string const& n)
#else
  _start_any_element (ro_string const&, ro_string const& n, const char*)
#endif
  {
    cout << "  start any element '" << n << "'" << endl;
  }

  virtual void
  _end_any_element (ro_string const&, ro_string const& n)
  {
    cout << "  end any element '" << n << "'" << endl;
  }

  virtual void
  _any_attribute (ro_string const&,
                  ro_string const& n,
		  ro_string const& v)
  {
    cout << "  any attribute " << n << " = '" << v << "'" << endl;
  }

  virtual void
  _any_characters (ro_string const& s)
  {
    cout << "  any text: '" << s << "'" << endl;
  }

  virtual void
  post_any_type ()
  {
    cout << "}" << endl
         << endl;
  }
};

struct any_extension_pimpl: any_extension_pskel
{
  any_extension_pimpl ()
      : any_extension_pskel (&base_impl_)
  {
  }

#ifdef XSDE_STL
  virtual void
  x (const string& v)
  {
    cout << "  x = " << v << endl;
  }
#else
  virtual void
  x (char* v)
  {
    cout << "  x = " << v << endl;
    delete[] v;
  }
#endif

private:
  any_type_pimpl base_impl_;
};

struct any_simple_extension_pimpl: any_simple_extension_pskel
{
  any_simple_extension_pimpl ()
      : any_simple_extension_pskel (&base_impl_)
  {
  }

#ifdef XSDE_STL
  virtual void
  x (const string& v)
  {
    cout << "  x = " << v << endl;
  }

  virtual void
  post_any_simple_extension ()
  {
    cout << "'" << post_any_simple_type () << "'" << endl;
  }
#else
  virtual void
  x (char* v)
  {
    cout << "  x = " << v << endl;
    delete[] v;
  }

  virtual void
  post_any_simple_extension ()
  {
    char* v = post_any_simple_type ();
    cout << "'" << v << "'" << endl;
    delete[] v;
  }
#endif

private:
  xml_schema::any_simple_type_pimpl base_impl_;
};

struct type_pimpl: type_pskel
{
#ifdef XSDE_STL
  virtual void
  as (std::string const& v)
  {
    cout << "'" << v << "'" << endl;
  }
#else // XSDE_STL
  virtual void
  as (char* v)
  {
    cout << "'" << v << "'" << endl;
    delete[] v;
  }
#endif
};

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  try
  {
    xml_schema::string_pimpl string_p;

    any_type_pimpl any_type_p;
    xml_schema::any_simple_type_pimpl any_simple_type_p;

    any_extension_pimpl any_extension_p;
    any_simple_extension_pimpl any_simple_extension_p;

    type_pimpl type_p;

    any_extension_p.parsers (string_p);
    any_simple_extension_p.parsers (string_p);

    type_p.parsers (any_simple_type_p,
                    any_type_p,
                    any_extension_p,
                    any_simple_extension_p);

    xml_schema::document_pimpl doc_p (type_p, "test", "root");

    type_p.pre ();
    doc_p.parse (argv[1]);
    type_p.post_type ();
  }
  catch (xml_schema::parser_exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
  catch (ios_base::failure const&)
  {
    cerr << "io failure" << endl;
    return 1;
  }

  return 0;
}
