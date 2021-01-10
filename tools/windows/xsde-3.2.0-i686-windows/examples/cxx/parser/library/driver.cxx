// file      : examples/cxx/parser/library/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "library.hxx"

#include "library-pskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "library-pimpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "library-pimpl-tiein.hxx"
#else
#  error this example requires mixin or tiein parser reuse support
#endif

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


    // Construct the parser.
    //
    xml_schema::id_pimpl id_p;
    xml_schema::idref_pimpl idref_p;
    xml_schema::string_pimpl string_p;
    xml_schema::boolean_pimpl boolean_p;

    isbn_pimpl isbn_p;

    title_pimpl title_p;
    title_p.lang_parser (string_p);

    genre_pimpl genre_p;

    author_pimpl author_p;
    author_p.parsers (string_p,  // name
                      string_p,  // born
                      string_p,  // died
                      idref_p);  // recommends

    book_pimpl book_p;
    book_p.parsers (boolean_p, // available
                    id_p,      // id
                    isbn_p,    // isbn
                    title_p,   // title
                    genre_p,   // genre
                    author_p); // author

    catalog_pimpl catalog_p;
    catalog_p.book_parser (book_p);


    // Parse the XML instance document.
    //
    xml_schema::document_pimpl doc_p (
      catalog_p,
      "http://www.codesynthesis.com/library", // root element namespace
      "catalog");                             // root element name

    catalog_p.pre ();

    if (argc < 2)
      doc_p.parse (std::cin);
    else
      doc_p.parse (argv[1]);

    catalog c (catalog_p.post_catalog ());


    // Let's print what we've got.
    //
    for (catalog::const_iterator bi (c.begin ()); bi != c.end (); ++bi)
    {
      cerr << endl
           << "ID           : " << bi->id () << endl
           << "ISBN         : " << bi->isbn () << endl
           << "Title        : " << bi->title ()  << endl
           << "Genre        : " << bi->genre () << endl;

      for (book::authors::const_iterator ai (bi->author ().begin ());
           ai != bi->author ().end ();
           ++ai)
      {
        cerr << "Author       : " << ai->name () << endl;
        cerr << "  Born       : " << ai->born () << endl;

        if (!ai->died ().empty ())
          cerr << "  Died       : " << ai->died () << endl;

        if (!ai->recommends ().empty ())
        {
          cerr << "  Recommends : " << ai->recommends () << endl;
        }
      }

      cerr  << "Available    : " << std::boolalpha << bi->available () << endl;
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
