// file      : examples/cxx/serializer/polyroot/driver.cxx
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

    person_s.serializers (string_s);
    superman_s.serializers (string_s, boolean_s);
    batman_s.serializers (string_s, boolean_s, unsigned_int_s);

    // Serialize each item in the supermen catalog as a separate XML
    // document.
    //
    for (supermen::const_iterator i = sm.begin (); i != sm.end (); ++i)
    {
      person& p = **i;
      person_sskel* ps = 0;

      switch (p.type ())
      {
      case person_type:
        {
          ps = &person_s;
          break;
        }
      case superman_type:
        {
          ps = &superman_s;
          break;
        }
      case batman_type:
        {
          ps = &batman_s;
          break;
        }
      }

      // Create a document serializer for this type. Note that we pass
      // true as the third argument to indicate polymorphic serialization
      // as well as the root element's static type as the last argument
      // which is necessary if the actual root type can differ from its
      // static type.
      //
      xml_schema::document_simpl doc_s (
        *ps, "person", true, person_sskel::_static_type ());

      doc_s.add_no_namespace_schema ("supermen.xsd");

      ps->pre (p);
      doc_s.serialize (std::cout, xml_schema::document_simpl::pretty_print);
      ps->post ();

      std::cout << endl
                << endl;
    }
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
