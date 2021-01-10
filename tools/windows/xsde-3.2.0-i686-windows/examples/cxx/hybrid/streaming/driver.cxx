// file      : examples/cxx/hybrid/streaming/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "position.hxx"
#include "position-pimpl.hxx"
#include "position-simpl.hxx"

using namespace std;

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
    // Parse.
    //
    object_paggr object_p;

    xml_schema::document_pimpl doc_p (
      object_p.root_parser (),
      object_p.root_name ());

    object_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    object_p.post (); // Ignore the NULL return value.

    // Serialize.
    //
    object_saggr object_s;

    xml_schema::document_simpl doc_s (
      object_s.root_serializer (),
      object_s.root_name ());

    // Create an object instance. Its only purpose is to carry the
    // object id. The position measurements will be supplied directly
    // by the custom serializer.
    //
    object obj;
    obj.id (456);

    object_s.pre (obj);
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    object_s.post ();
  }
  catch (const xml_schema::parser_exception& e)
  {
    cerr << input << ":" << e.line () << ":" << e.column () << ": "
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
    cerr << input << ": unable to open or read/write failure" << endl;
    return 1;
  }

  return 0;
}
