// file      : examples/cxx/hybrid/evolution/passthrough/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <string>
#include <iostream>

#include "transform.hxx"
#include "transform-pimpl.hxx"
#include "transform-simpl.hxx"

using namespace std;
using namespace transform;

// Parser substitution map callback. This callback is called when the
// parser needs to check whether an element belongs to a substitution
// group. We use this callback to handle unknown transformations.
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
      // Tell the parser to use unknown_type to parse this element.
      //
      type = unknown_type_pimpl::_static_type ();
      return true;
    }
  }

  return false;
}

// Serializer substitution map callback. This callback is called when
// the serializer needs to map a type to an element belonging to a
// substitution group. We use this callback to handle unknown
// transformations.
//
static bool
serializer_callback (const char* type,
                     const void* obj,
                     const char*& ns,
                     const char*& name)
{
  // Check whether this is unknown_type.
  //
  if (string (type) == unknown_type_simpl::_static_type ())
  {
    // Cast the opaque obj pointer to unknown_type.
    //
    const unknown_type* u = reinterpret_cast<const unknown_type*> (obj);

    // Extract the actual element name from the object.
    //
    const xml::qname& n (u->element_name ());
    ns = n.ns ().c_str ();
    name = n.name ().c_str ();

    return true;
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
    // Set the substitution map callbacks.
    //
    xml_schema::parser_smap_callback (&parser_callback);
    xml_schema::serializer_smap_callback (&serializer_callback);

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
      else if (unknown_type* u = dynamic_cast<unknown_type*> (&t))
      {
        cout << u->name () << ": " << u->description () << endl
             << "\ttransformation is unknown" << endl
             << endl;
      }
    }

    // Serialize.
    //
    transformations_saggr transformations_s;

    // The last argument to the document's constructor indicates that we
    // are serializing polymorphic XML documents.
    //
    xml_schema::document_simpl doc_s (
      transformations_s.root_serializer (),
      transformations_s.root_namespace (),
      transformations_s.root_name (),
      true);

    doc_s.add_prefix ("", "http://www.codesynthesis.com/transform");

    transformations_s.pre (*tf);
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    transformations_s.post ();
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
