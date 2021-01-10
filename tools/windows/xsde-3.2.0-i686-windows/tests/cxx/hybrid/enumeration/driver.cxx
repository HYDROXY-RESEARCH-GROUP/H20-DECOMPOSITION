// file      : tests/cxx/hybrid/enumeration/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test XML Schema enumeration to C++ enum mapping.
//

#include <cassert>
#include <iostream>

#include "test.hxx"
#include "test-pimpl.hxx"
#include "test-simpl.hxx"

using namespace std;
using namespace test;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  // Parse.
  //
  root_paggr root_p;

  xml_schema::document_pimpl doc_p (
    root_p.root_parser (),
    root_p.root_namespace (),
    root_p.root_name ());

  root_p.pre ();
  doc_p.parse (argv[1]);
  type* r = root_p.post ();

  // Test the mapping.
  //
  {
    simple x;
    x = simple::a;
    assert (x == simple::a);

    x.value (simple::b);
    assert (x == simple::b);

    simple y (simple::c);

    switch (y)
    {
    case simple::c:
      {
        break;
      }
    default:
      assert (false);
    }
  }

  {
    final x (final::c);
    assert (x == final::c);

    simple s = x;
    assert (s == simple::c);
  }

  {
    complex c;
    c.value (complex::a);
    assert (c == complex::a);

    simple s = c;
    assert (s == simple::a);
  }

  // Serialize.
  //
  root_saggr root_s;

  xml_schema::document_simpl doc_s (
    root_s.root_serializer (),
    root_s.root_namespace (),
    root_s.root_name ());

  doc_s.add_prefix ("t", "test");

  root_s.pre (*r);
  doc_s.serialize (cout);
  root_s.post ();

  delete r;

  return 0;
}
