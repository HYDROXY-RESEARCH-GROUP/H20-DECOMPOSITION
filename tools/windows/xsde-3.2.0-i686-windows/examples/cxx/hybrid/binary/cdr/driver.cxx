// file      : examples/cxx/hybrid/binary/cdr/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <string.h>  // memcpy

#include <memory>    // std::auto_ptr
#include <iostream>

#include <ace/Log_Msg.h>   // ACE_HEX_DUMP
#include <ace/CDR_Stream.h>

#include "library.hxx"
#include "library-pimpl.hxx"
#include "library-simpl.hxx"

using std::cerr;
using std::endl;

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
    using namespace library;

    // Parse.
    //
    catalog_paggr catalog_p;

    xml_schema::document_pimpl doc_p (
      catalog_p.root_parser (),
      catalog_p.root_namespace (),
      catalog_p.root_name ());

    catalog_p.pre ();

    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);

    std::auto_ptr<catalog> c (catalog_p.post ());

    // Save the object model to a CDR stream.
    //
    ACE_OutputCDR ace_ocdr;
    xml_schema::ocdrstream ocdr (ace_ocdr);
    ocdr << *c;

    // Print the binary representation and at the same time save
    // it into a continuous buffer.
    //
    cerr << "binary representation size: " << ace_ocdr.total_length () << endl
         << endl;

    xml_schema::buffer buf (ace_ocdr.total_length ());
    char* data = buf.data ();

    for (const ACE_Message_Block* mb = ace_ocdr.begin ();
         mb != 0;
         mb = mb->cont ())
    {
      memcpy (data, mb->rd_ptr (), mb->length ());
      data += mb->length ();

      ACE_HEX_DUMP ((LM_DEBUG, mb->rd_ptr (), mb->length ()));
    }

    // Load the object model from a CDR stream. Note that ACE_InputCDR
    // expects the buffer to be properly aligned. Since our buffer is
    // dynamically allocated, its alignment should be good enough.
    //
    ACE_InputCDR ace_icdr (buf.data (), buf.size ());
    xml_schema::icdrstream icdr (ace_icdr);
    std::auto_ptr<catalog> copy (new catalog);
    icdr >> *copy;

    // Serialize the copy back to XML.
    //
    catalog_saggr catalog_s;

    xml_schema::document_simpl doc_s (
      catalog_s.root_serializer (),
      catalog_s.root_namespace (),
      catalog_s.root_name ());

    doc_s.add_prefix ("lib", "http://www.codesynthesis.com/library");
    doc_s.add_schema ("http://www.codesynthesis.com/library", "library.xsd");

    catalog_s.pre (*copy);
    doc_s.serialize (std::cout, xml_schema::document_simpl::pretty_print);
    catalog_s.post ();
  }
  catch (const xml_schema::cdr_exception&)
  {
    cerr << "CDR operation failed" << endl;
    return 1;
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
