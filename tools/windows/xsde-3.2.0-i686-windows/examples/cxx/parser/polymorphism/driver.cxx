// file      : examples/cxx/parser/polymorphism/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "supermen-pskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "supermen-pimpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "supermen-pimpl-tiein.hxx"
#else
#  error this example requires mixin or tiein parser reuse support
#endif

using std::cerr;
using std::endl;

int
main (int argc, char* argv[])
{
  // Check that the load in substitution and inheritance hashmaps
  // is not too high.
  //
#ifndef NDEBUG
  float load = (float) xml_schema::parser_smap_elements ();
  load /= xml_schema::parser_smap_buckets ();

  if (load > 0.8)
  {
    cerr << "substitution hashmap load is " << load << endl;
    cerr << "time to increase XSDE_PARSER_SMAP_BUCKETS" << endl;
  }

#ifdef XSDE_PARSER_VALIDATION
  load = (float) xml_schema::parser_imap_elements ();
  load /= xml_schema::parser_imap_buckets ();

  if (load > 0.8)
  {
    cerr << "inheritance hashmap load is " << load << endl;
    cerr << "time to increase XSDE_PARSER_IMAP_BUCKETS" << endl;
  }
#endif
#endif

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
    xml_schema::string_pimpl string_p;
    xml_schema::boolean_pimpl boolean_p;
    xml_schema::unsigned_int_pimpl unsigned_int_p;

    person_pimpl person_p;
    superman_pimpl superman_p;
    batman_pimpl batman_p;

    xml_schema::parser_map_impl person_map (5); // 5 hashtable buckets
    supermen_pimpl supermen_p;


    person_p.parsers (string_p);
    superman_p.parsers (string_p, boolean_p);
    batman_p.parsers (string_p, boolean_p, unsigned_int_p);

    // Here we are specifying several parsers that can be
    // used to parse the person element.
    //
    person_map.insert (person_p);
    person_map.insert (superman_p);
    person_map.insert (batman_p);

    supermen_p.person_parser (person_map);

    // Parse the XML document. The last argument to the document's
    // constructor indicates that we are parsing polymorphic XML
    // documents.
    //
    xml_schema::document_pimpl doc_p (supermen_p, "supermen", true);

    supermen_p.pre ();

    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);

    supermen_p.post_supermen ();
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
