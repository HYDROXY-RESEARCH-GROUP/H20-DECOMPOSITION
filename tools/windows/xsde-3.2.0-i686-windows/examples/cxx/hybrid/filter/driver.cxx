// file      : examples/cxx/hybrid/filter/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include "people.hxx"
#include "people-pimpl.hxx"
#include "people-simpl.hxx"

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
    people_paggr people_p;
    people_pimpl& root_p = people_p.root_parser ();

    // Initialize the filter.
    //
    root_p.age_filter (1, 30);

    xml_schema::document_pimpl doc_p (root_p, people_p.root_name ());

    people_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    auto_ptr<people> ppl (people_p.post ());

    // Print what we've got.
    //
    people::person_sequence& ps = ppl->person ();

    for (people::person_iterator i = ps.begin (); i != ps.end (); ++i)
    {
      cerr << "first:  " << i->first_name () << endl
           << "last:   " << i->last_name () << endl
           << "gender: " << i->gender ().string () << endl
           << "age:    " << i->age () << endl
           << endl;
    }

    // Serialize.
    //
    people_saggr people_s;
    people_simpl& root_s = people_s.root_serializer ();

    // Initialize the filter.
    //
    root_s.gender_filter (gender::female);

    xml_schema::document_simpl doc_s (root_s, people_s.root_name ());

    people_s.pre (*ppl);
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    people_s.post ();
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
