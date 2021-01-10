// file      : tests/cxx/hybrid/binary/cdr/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test CDR insertion and extraction.
//

#include <memory>
#include <iostream>

#include <ace/CDR_Stream.h>

#include "test.hxx"
#include "test-pimpl.hxx"
#include "test-simpl.hxx"

using std::cerr;
using std::endl;

using namespace test;

int
main (int argc, char* argv[])
{
  /*
  try
  {
  */

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
  std::auto_ptr<type> r (root_p.post ());

  // Save to a CDR stream.
  //
  ACE_OutputCDR ace_ocdr;
  xml_schema::ocdrstream ocdr (ace_ocdr);
  ocdr << *r;

  // Load from a CDR stream.
  //
  ACE_InputCDR ace_icdr (ace_ocdr);
  xml_schema::icdrstream icdr (ace_icdr);
  std::auto_ptr<type> c (new type);
  icdr >> *c;

  // Serialize.
  //
  root_saggr root_s;

  xml_schema::document_simpl doc_s (
    root_s.root_serializer (),
    root_s.root_namespace (),
    root_s.root_name ());

  doc_s.add_prefix ("t", "test");

  root_s.pre (*c);
  doc_s.serialize (std::cout);
  root_s.post ();

  /*
  }
  catch (const xml_schema::xdr_exception&)
  {
    cerr << "XDR operation filed" << endl;
    return 1;
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << argv[0] << ":" << e.line () << ":" << e.column () << ": "
         << e.text () << endl;
    return 1;
  }
  catch (const xml_schema::serializer_exception& e)
  {
    cerr << "error: " << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << argv[0] << ": unable to open or read/write failure" << endl;
    return 1;
  }
  */

  return 0;
}
