// file      : examples/cxx/hybrid/library/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include "library.hxx"
#include "library-pimpl.hxx"
#include "library-simpl.hxx"

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
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    auto_ptr<catalog> c (catalog_p.post ());

    // Print what we've got.
    //
    catalog::book_sequence& books (c->book ());

    for (catalog::book_const_iterator i = books.begin ();
         i != books.end ();
         ++i)
    {
      cerr << "ISBN         : " << i->isbn () << endl
           << "Title        : " << i->title () << endl
           << "Genre        : " << i->genre ().string () << endl;

      for (book::author_const_iterator j = i->author ().begin ();
           j != i->author ().end ();
           ++j)
      {
        cerr << "Author       : " << j->name () << endl;

        xml_schema::date born (j->born ());

        cerr << "  Born       : "
             << born.year () << '-'
             << born.month () << '-'
             << born.day () << endl;

        if (j->died_present ())
        {
          xml_schema::date died (j->died ());

          cerr << "  Died       : "
               << died.year () << '-'
               << died.month () << '-'
               << died.day () << endl;
        }
      }

      cerr  << "Available    : " << i->available () << endl;
    }

    // Remove all unavailable books.
    //
    for (catalog::book_iterator j = books.begin (); j != books.end ();)
    {
      if (!j->available ())
        j = books.erase (j);
      else
        ++j;
    }

    // Insert a new book.
    //
    {
      auto_ptr<book> b (new book);

      isbn n;
      n.base_value (679776443);
      b->isbn (n);

      title t;
      t.assign ("Dead Souls");
      b->title (t);

      b->genre (genre::philosophy);

      author a;
      a.name ("Nikolai Gogol");
      a.born (xml_schema::date (1809, 3, 31));
      b->author ().push_back (a);

      books.insert (books.begin (), b.release ());
    }

    // Serialize.
    //
    catalog_saggr catalog_s;

    xml_schema::document_simpl doc_s (
      catalog_s.root_serializer (),
      catalog_s.root_namespace (),
      catalog_s.root_name ());

    doc_s.add_prefix ("lib", "http://www.codesynthesis.com/library");
    doc_s.add_schema ("http://www.codesynthesis.com/library", "library.xsd");

    catalog_s.pre (*c);
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    catalog_s.post ();
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
