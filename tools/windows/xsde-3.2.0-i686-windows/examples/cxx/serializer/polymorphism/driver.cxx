// file      : examples/cxx/serializer/polymorphism/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "supermen.hxx"

#include "supermen-sskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "supermen-simpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "supermen-simpl-tiein.hxx"
#else
#  error this example requires mixin or tiein serializer reuse support
#endif

using std::cerr;
using std::endl;

int
main ()
{
  // Check that the load in substitution and inheritance hashmaps
  // is not too high.
  //
#ifndef NDEBUG
  float load = (float) xml_schema::serializer_smap_elements ();
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
#endif

  try
  {
    // Create a sample supermen catalog. To keep things simple the
    // following code is not exception-safe.
    //
    supermen sm;

    sm.push_back (new person ("John Doe"));
    sm.push_back (new superman ("James 007 Bond", false));
    sm.push_back (new batman ("Bruce Wayne", 10));

    // Construct the serializer.
    //
    xml_schema::string_simpl string_s;
    xml_schema::boolean_simpl boolean_s;
    xml_schema::unsigned_int_simpl unsigned_int_s;

    person_simpl person_s;
    superman_simpl superman_s;
    batman_simpl batman_s;

    xml_schema::serializer_map_impl person_map (5); // 5 hashtable buckets
    supermen_simpl supermen_s;

    person_s.serializers (string_s);
    superman_s.serializers (string_s, boolean_s);
    batman_s.serializers (string_s, boolean_s, unsigned_int_s);

    // Here we are specifying several serializers that can be
    // used to serialize the person element.
    //
    person_map.insert (person_s);
    person_map.insert (superman_s);
    person_map.insert (batman_s);

    supermen_s.person_serializer (person_map);

    // Create the XML instance document. The last argument to the
    // document's constructor indicates that we are serializing
    // polymorphic XML documents.
    //
    xml_schema::document_simpl doc_s (supermen_s, "supermen", true);

    doc_s.add_no_namespace_schema ("supermen.xsd");

    supermen_s.pre (sm);
    doc_s.serialize (std::cout, xml_schema::document_simpl::pretty_print);
    supermen_s.post ();
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
