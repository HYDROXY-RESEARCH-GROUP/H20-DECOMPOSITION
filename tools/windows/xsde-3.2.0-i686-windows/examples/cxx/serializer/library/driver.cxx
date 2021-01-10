// file      : examples/cxx/serializer/library/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "library.hxx"

#include "library-sskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "library-simpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "library-simpl-tiein.hxx"
#else
#  error this example requires mixin or tiein serializer reuse support
#endif

using std::cerr;
using std::endl;

int
main ()
{
  try
  {
    using namespace library;

    // Create a sample library catalog.
    //
    catalog cat;

    {
      book b (679760806,
              title ("The Master and Margarita"),
              fiction,
              false,
              "MM");

      author a ("Mikhail Bulgakov", "1891-05-15");
      a.died ("1940-03-10");
      a.recommends ("WP");

      b.author ().push_back (a);

      cat.push_back (b);
    }

    {
      book b (679600841,
              title ("War and Peace"),
              history,
              true,
              "WP");

      author a ("Leo Tolstoy", "1828-09-09");
      a.died ("1910-11-20");
      a.recommends ("CP");

      b.author ().push_back (a);

      cat.push_back (b);
    }

    {
      book b (679420290,
              title ("Crime and Punishment"),
              philosophy,
              false,
              "CP");

      author a ("Fyodor Dostoevsky", "1821-11-11");
      a.died ("1881-02-09");

      b.author ().push_back (a);

      cat.push_back (b);
    }


    // Construct the serializer.
    //
    xml_schema::id_simpl id_s;
    xml_schema::idref_simpl idref_s;
    xml_schema::string_simpl string_s;
    xml_schema::boolean_simpl boolean_s;

    isbn_simpl isbn_s;

    title_simpl title_s;
    title_s.lang_serializer (string_s);

    genre_simpl genre_s;

    author_simpl author_s;
    author_s.serializers (string_s,  // name
                          string_s,  // born
                          string_s,  // died
                          idref_s);  // recommends

    book_simpl book_s;
    book_s.serializers (boolean_s, // available
                        id_s,      // id
                        isbn_s,    // isbn
                        title_s,   // title
                        genre_s,   // genre
                        author_s); // author


    catalog_simpl catalog_s;
    catalog_s.book_serializer (book_s);


    // Create the XML instance document.
    //
    xml_schema::document_simpl doc_s (
      catalog_s,
      "http://www.codesynthesis.com/library", // root element namespace
      "catalog");                             // root element name

    doc_s.add_prefix ("lib", "http://www.codesynthesis.com/library");
    doc_s.add_schema ("http://www.codesynthesis.com/library", "library.xsd");

    catalog_s.pre (cat);
    doc_s.serialize (std::cout, xml_schema::document_simpl::pretty_print);
    catalog_s.post ();
  }
  catch (const xml_schema::serializer_exception& e)
  {
    cerr << "error: " << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << "error: write failure" << endl;
    return 1;
  }

  return 0;
}
