// file      : examples/cxx/serializer/minimal/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <stdio.h>

#include "people.hxx"
#include "people-sskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "people-simpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "people-simpl-tiein.hxx"
#else
#  error this example requires mixin or tiein serializer reuse support
#endif

struct writer: xml_schema::writer
{
  virtual bool
  write (const char* s, size_t n)
  {
    return fwrite (s, n, 1, stdout) == 1;
  }

  virtual bool
  flush ()
  {
    return fflush (stdout) == 0;
  }
};

int
main ()
{
  // Create a sample person list.
  //
  people p;

  p.size_ = 2;
  p.people_ = new person[p.size_];

  if (p.people_ == 0)
  {
    fprintf (stderr, "error: no memory\n");
    return 1;
  }

  p.people_[0].first_name_ = "John";
  p.people_[0].last_name_ = "Doe";
  p.people_[0].gender_ = male;
  p.people_[0].age_ = 32;

  p.people_[1].first_name_ = "Jane";
  p.people_[1].last_name_ = "Doe";
  p.people_[1].gender_ = female;
  p.people_[1].age_ = 28;

  // Construct the serializer.
  //
  xml_schema::unsigned_short_simpl unsigned_short_s;
  xml_schema::string_simpl string_s;

  gender_simpl gender_s;
  person_simpl person_s;
  people_simpl people_s;

  person_s.serializers (string_s, string_s, gender_s, unsigned_short_s);
  people_s.serializers (person_s);

  // Serialize.
  //
  typedef xml_schema::serializer_error error;

  error e;
  writer w;

  do
  {
    xml_schema::document_simpl doc_s (people_s, "people");

    e = doc_s._error ();
    if (e)
      break;

    people_s.pre (p);

    e = people_s._error ();
    if (e)
      break;

    doc_s.serialize (w, xml_schema::document_simpl::pretty_print);

    e = doc_s._error ();
    if (e)
      break;

    people_s.post ();

    e = people_s._error ();

  } while (false);

  delete[] p.people_;

  // Handle errors.
  //
  if (e)
  {
    switch (e.type ())
    {
    case error::sys:
      {
        fprintf (stderr, "error: %s\n", e.sys_text ());
        break;
      }
    case error::xml:
      {
        fprintf (stderr, "error: %s\n", e.xml_text ());
        break;
      }
#ifdef XSDE_SERIALIZER_VALIDATION
    case error::schema:
      {
        fprintf (stderr, "error: %s\n", e.schema_text ());
        break;
      }
#endif
    case error::app:
      {
        fprintf (stderr, "application error: %d\n", e.app_code ());
        break;
      }
    default:
      break;
    }

    return 1;
  }

  return 0;
}
