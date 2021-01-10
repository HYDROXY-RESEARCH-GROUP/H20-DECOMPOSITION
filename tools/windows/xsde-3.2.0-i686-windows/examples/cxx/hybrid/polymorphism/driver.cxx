// file      : examples/cxx/hybrid/polymorphism/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include "supermen.hxx"
#include "supermen-pimpl.hxx"
#include "supermen-simpl.hxx"

using namespace std;

void
check_load (); // Defined after main().

int
main (int argc, char* argv[])
{
  // Check that the load in substitution and inheritance hashmaps
  // is not too high.
  //
#ifndef NDEBUG
  check_load ();
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
    // Parse.
    //
    supermen_paggr supermen_p;

    // The last argument to the document's constructor indicates that we
    // are parsing polymorphic XML documents.
    //
    xml_schema::document_pimpl doc_p (
      supermen_p.root_parser (),
      supermen_p.root_name (),
      true);

    supermen_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    auto_ptr<supermen> sm (supermen_p.post ());

    // Print what we've got.
    //
    for (supermen::person_iterator i = sm->person ().begin ();
         i != sm->person ().end ();
         ++i)
    {
      person& p = *i;

      // You can use the standard C++ RTTI or custom type information
      // provided by the object model (--generate-typeinfo option) to
      // detect the object's actual (dynamic) type.
      //
      if (p._dynamic_type () == batman::_static_type ())
      {
        batman& b = static_cast<batman&> (p);
        cerr << b.name () << ", batman, wing span " << b.wing_span () << endl;
      }
      else if (superman* s = dynamic_cast<superman*> (&p))
      {
        cerr << s->name () << ", ";

        if (s->can_fly ())
          cerr << "flying ";

        cerr << "superman" << endl;
      }
      else
      {
        cerr << p.name () << ", ordinary person" << endl;
      }
    }

    // Add another superman entry.
    //
    auto_ptr<superman> s (new superman);
#ifdef XSDE_STL
    s->name ("Clark Kent");
#else
    s->name (xml_schema::strdupx ("Clark Kent"));
#endif
    s->can_fly (true);
    sm->person ().push_back (s.release ());

    // Serialize.
    //
    supermen_saggr supermen_s;

    // The last argument to the document's constructor indicates that we
    // are serializing polymorphic XML documents.
    //
    xml_schema::document_simpl doc_s (
      supermen_s.root_serializer (),
      supermen_s.root_name (),
      true);

    doc_s.add_no_namespace_schema ("supermen.xsd");

    supermen_s.pre (*sm);
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    supermen_s.post ();
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

#ifndef NDEBUG
// Check that the load in substitution and inheritance hashmaps is not
// too high. See the C++/Parser and C++/Serializer Mappings Getting
// Started Guides for details.
//
void
check_load ()
{
  // Parser.
  //
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

  // Serializer.
  //
  load = (float) xml_schema::serializer_smap_elements ();
  load /= xml_schema::serializer_smap_buckets ();

  if (load > 0.8)
  {
    cerr << "substitution hashmap load is " << load << endl;
    cerr << "time to increase XSDE_SERIALIZER_SMAP_BUCKETS" << endl;
  }

  load = (float) xml_schema::serializer_smap_bucket_elements ();
  load /= xml_schema::serializer_smap_bucket_buckets ();

  if (load > 0.8)
  {
    cerr << "substitution inner hashmap load is " << load << endl;
    cerr << "time to increase XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS" << endl;
  }

#ifdef XSDE_SERIALIZER_VALIDATION
  load = (float) xml_schema::serializer_imap_elements ();
  load /= xml_schema::serializer_imap_buckets ();

  if (load > 0.8)
  {
    cerr << "inheritance hashmap load is " << load << endl;
    cerr << "time to increase XSDE_SERIALIZER_IMAP_BUCKETS" << endl;
  }
#endif
}
#endif
