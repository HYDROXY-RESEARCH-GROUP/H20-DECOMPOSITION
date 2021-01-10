// file      : examples/cxx/parser/minimal/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <stdio.h>

#include "people-pskel.hxx" // Get the configuration macros (XSDE_*).

#if defined(XSDE_REUSE_STYLE_MIXIN)
#  include "people-pimpl-mixin.hxx"
#elif defined(XSDE_REUSE_STYLE_TIEIN)
#  include "people-pimpl-tiein.hxx"
#else
#  error this example requires mixin or tiein parser reuse support
#endif

int
main (int argc, char* argv[])
{
  const char* input;

  if (argc < 2)
  {
    input = "STDIN";
    fprintf (stderr, "XML file not specified, reading from STDIN\n");
  }
  else
    input = argv[1];

  // Construct the parser.
  //
  xml_schema::unsigned_short_pimpl unsigned_short_p;
  xml_schema::string_pimpl string_p;

  gender_pimpl gender_p;
  person_pimpl person_p;
  people_pimpl people_p;

  person_p.parsers (string_p, string_p, gender_p, unsigned_short_p);
  people_p.parsers (person_p);

  // Open the file or use STDIN.
  //
  FILE* f = argc > 1 ? fopen (argv[1], "rb") : stdin;

  if (f == 0)
  {
    fprintf (stderr, "%s: unable to open\n", input);
    return 1;
  }

  // Parse.
  //
  typedef xml_schema::parser_error error;
  error e;
  bool io_error = false;

  do
  {
    xml_schema::document_pimpl doc_p (people_p, "people");

    if (e = doc_p._error ())
      break;

    people_p.pre ();

    if (e = people_p._error ())
      break;

    char buf[4096];

    do
    {
      size_t s = fread (buf, 1, sizeof (buf), f);

      if (s != sizeof (buf) && ferror (f))
      {
        io_error = true;
        break;
      }

      doc_p.parse (buf, s, feof (f) != 0);
      e = doc_p._error ();

    } while (!e && !feof (f));

    if (io_error || e)
      break;

    people_p.post_people ();

    e = people_p._error ();

  } while (false);

  if (argc > 1)
    fclose (f);

  // Handle errors.
  //

  if (io_error)
  {
    fprintf (stderr, "%s: read failure\n", input);
    return 1;
  }

  if (e)
  {
    switch (e.type ())
    {
    case error::sys:
      {
        fprintf (stderr, "%s: %s\n", input, e.sys_text ());
        break;
      }
    case error::xml:
      {
        fprintf (stderr, "%s:%lu:%lu: %s\n",
                 input, e.line (), e.column (), e.xml_text ());
        break;
      }
#ifdef XSDE_PARSER_VALIDATION
    case error::schema:
      {
        fprintf (stderr, "%s:%lu:%lu: %s\n",
                 input, e.line (), e.column (), e.schema_text ());
        break;
      }
#endif
    case error::app:
      {
        fprintf (stderr, "%s:%lu:%lu: application error %d\n",
                 input, e.line (), e.column (), e.app_code ());
        break;
      }
    default:
      break;
    }

    return 1;
  }

  return 0;
}
