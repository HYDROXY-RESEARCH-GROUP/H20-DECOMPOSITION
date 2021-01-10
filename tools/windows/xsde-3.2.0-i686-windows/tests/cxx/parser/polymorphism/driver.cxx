// file      : tests/cxx/parser/polymorphism/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test substitution groups and xsi:type support.
//
#include <iostream>

#include "test-pskel.hxx"

using namespace std;
using namespace test;

struct base_pimpl: base_pskel
{
  virtual void
  a (int i)
  {
    cout << "a: " << i << endl;
  }
};

struct interm_pimpl: interm_pskel
{
  interm_pimpl ()
      : interm_pskel (&base_impl_)
  {
  }

  virtual void
  b (int i)
  {
    cout << "b: " << i << endl;
  }

  base_pimpl base_impl_;
};

struct derived_pimpl: derived_pskel
{
  derived_pimpl ()
      : derived_pskel (&base_impl_)
  {
  }

  virtual void
  c (int i)
  {
    cout << "c: " << i << endl;
  }

  interm_pimpl base_impl_;
};

struct type_pimpl: type_pskel
{
};

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

#ifdef XSDE_EXCEPTIONS
  try
  {
#endif
    xml_schema::int_pimpl int_p;

    base_pimpl base_p;
    interm_pimpl interm_p;
    derived_pimpl derived_p;

    xml_schema::parser_map_impl map (5);
    type_pimpl type_p;

    base_p.parsers (int_p);
    interm_p.parsers (int_p, int_p);
    derived_p.parsers (int_p, int_p, int_p);

    map.insert (base_p);
    map.insert (interm_p);
    map.insert (derived_p);

    type_p.base_parser (map);

    xml_schema::document_pimpl doc_p (type_p, "test", "root", true);

    type_p.pre ();
    doc_p.parse (argv[1]);

#ifndef XSDE_EXCEPTIONS
    if (doc_p._error ())
    {
      cerr << "error" << endl;
      return 1;
    }
#endif

    type_p.post_type ();

    // Test parser resetting.
    //
    doc_p.reset ();

#ifdef XSDE_EXCEPTIONS
  }
  catch (xml_schema::parser_exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
  catch (std::ios_base::failure const&)
  {
    cerr << "io failure" << endl;
    return 1;
  }
#endif

  return 0;
}
