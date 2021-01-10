// file      : examples/cxx/hybrid/evolution/ignore/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <string>
#include <iostream>

#include "transform.hxx"
#include "transform-pimpl.hxx"

using namespace std;
using namespace transform;

// Parser substitution map callback. This callback is called when the
// parser needs to check whether an element belongs to a substitution
// group. We use this callback to return a special ignored type marker
// for unknown transformations.
//
static bool
parser_callback (const xml_schema::ro_string& root_ns,
                 const xml_schema::ro_string& root_name,
                 const xml_schema::ro_string& /*member_ns*/,
                 const xml_schema::ro_string& member_name,
                 const char*& type)
{
  // Check that the root of the substitution group is 'transformation'.
  //
  if (root_name == "transformation" &&
      root_ns == "http://www.codesynthesis.com/transform")
  {
    // Check that the element's name has the '-transformation' suffix. This
    // is the convention we use in our schema to minimize the chance of
    // treating any unknown elements as a transformation.
    //
    //
    string s ("-transformation");
    string n (member_name);

    if (n.size () > s.size () &&
        string (n, n.size () - s.size (), s.size ()) == s)
    {
      // Set type to the special ignore marker.
      //
      type = "*";
      return true;
    }
  }

  return false;
}

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
    // Set the substitution map callback.
    //
    xml_schema::parser_smap_callback (&parser_callback);

    // Parse.
    //
    transformations_paggr transformations_p;

    // The last argument to the document's constructor indicates that we
    // are parsing polymorphic XML documents.
    //
    xml_schema::document_pimpl doc_p (
      transformations_p.root_parser (),
      transformations_p.root_namespace (),
      transformations_p.root_name (),
      true);

    transformations_p.pre ();

    if (argc < 2)
      doc_p.parse (cin);
    else
      doc_p.parse (argv[1]);

    auto_ptr<transformations_type> tf (transformations_p.post ());

    // Print what we've got.
    //
    for (transformations_type::transformation_iterator i =
           tf->transformation ().begin ();
         i != tf->transformation ().end ();
         ++i)
    {
      transformation_type& t = *i;

      if (move_type* m = dynamic_cast<move_type*> (&t))
      {
        cout << m->name () << ": " << m->description () << endl
             << "\tx: " << m->x () << endl
             << "\ty: " << m->y () << endl
             << endl;
      }
      else if (rotate_type* r = dynamic_cast<rotate_type*> (&t))
      {
        cout << r->name () << ": " << r->description () << endl
             << "\tangle: " << r->angle () << endl
             << endl;
      }
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
    cerr << input << ": unable to open or read/write failure" << endl;
    return 1;
  }

  return 0;
}
