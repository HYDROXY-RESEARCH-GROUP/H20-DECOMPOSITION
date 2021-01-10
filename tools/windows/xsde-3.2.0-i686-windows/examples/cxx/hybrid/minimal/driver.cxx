// file      : examples/cxx/hybrid/minimal/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <stdio.h>

#include "people.hxx"
#include "people-pimpl.hxx"
#include "people-simpl.hxx"

// eVC++ 4.0 does not like using xml_schema::strdupx;
//
inline char*
strdupx (const char* s)
{
  return xml_schema::strdupx (s);
}

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
  using xml_schema::parser_error;

  parser_error pe;
  bool io_error = false;
  people* ppl = 0;

  do
  {
    people_paggr people_p;
    xml_schema::document_pimpl doc_p (people_p.root_parser (),
                                      people_p.root_name ());

    if (pe = doc_p._error ())
      break;

    people_p.pre ();

    if (pe = people_p._error ())
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
      pe = doc_p._error ();

    } while (!pe && !feof (f));

    if (io_error || pe)
      break;

    ppl = people_p.post ();

    pe = people_p._error ();

  } while (false);

  if (argc > 1)
    fclose (f);

  // Handle parsing errors.
  //
  if (io_error)
  {
    fprintf (stderr, "%s: read failure\n", input);
    return 1;
  }

  if (pe)
  {
    switch (pe.type ())
    {
    case parser_error::sys:
      {
        fprintf (stderr, "%s: %s\n", input, pe.sys_text ());
        break;
      }
    case parser_error::xml:
      {
        fprintf (stderr, "%s:%lu:%lu: %s\n",
                 input, pe.line (), pe.column (), pe.xml_text ());
        break;
      }
#ifdef XSDE_PARSER_VALIDATION
    case parser_error::schema:
      {
        fprintf (stderr, "%s:%lu:%lu: %s\n",
                 input, pe.line (), pe.column (), pe.schema_text ());
        break;
      }
#endif
    case parser_error::app:
      {
        fprintf (stderr, "%s:%lu:%lu: application error %d\n",
                 input, pe.line (), pe.column (), pe.app_code ());
        break;
      }
    default:
      break;
    }

    return 1;
  }

  // Print what we've got.
  //
  people::person_sequence& ps = ppl->person ();

  for (people::person_const_iterator i = ps.begin (); i != ps.end (); ++i)
  {
    printf ("first: %s\n" "last: %s\n" "gender: %s\n" "age: %hu\n\n",
            i->first_name (),
            i->last_name (),
            i->gender ().string (),
            i->age ());
  }

  // Remove people that are younger than 30.
  //
  for (people::person_iterator j = ps.begin (); j != ps.end ();)
  {
    if (j->age () < 30)
      j = ps.erase (j);
    else
      ++j;
  }

  // Insert a new person.
  //
  {
    person* p = 0;
    bool mem_error = false;

    do
    {
      p = new person;

      if (p == 0)
      {
        mem_error = true;
        break;
      }

      char* s = strdupx ("Joe");

      if (s == 0)
      {
        mem_error = true;
        break;
      }

      p->first_name (s);

      s = strdupx ("Dirt");

      if (s == 0)
      {
        mem_error = true;
        break;
      }

      p->last_name (s);

      p->age (36);
      p->gender (gender::male);

      if (ps.insert (ps.begin (), p) != 0)
      {
        mem_error = true;
        p = 0; // The sequence has already deleted the object.
        break;
      }

    } while (false);

    if (mem_error)
    {
      fprintf (stderr, "error: no memory\n");
      delete p;
      delete ppl;
      return 1;
    }
  }

  // Serialize.
  //
  using xml_schema::serializer_error;

  serializer_error se;
  writer w;

  do
  {
    people_saggr people_s;
    xml_schema::document_simpl doc_s (people_s.root_serializer (),
                                      people_s.root_name ());

    doc_s.add_no_namespace_schema ("people.xsd");

    se = doc_s._error ();
    if (se)
      break;

    people_s.pre (*ppl);

    se = people_s._error ();
    if (se)
      break;

    doc_s.serialize (w, xml_schema::document_simpl::pretty_print);

    se = doc_s._error ();
    if (se)
      break;

    people_s.post ();

    se = people_s._error ();

  } while (false);

  delete ppl;

  // Handle serializer errors.
  //
  if (se)
  {
    switch (se.type ())
    {
    case serializer_error::sys:
      {
        fprintf (stderr, "error: %s\n", se.sys_text ());
        break;
      }
    case serializer_error::xml:
      {
        fprintf (stderr, "error: %s\n", se.xml_text ());
        break;
      }
#ifdef XSDE_SERIALIZER_VALIDATION
    case serializer_error::schema:
      {
        fprintf (stderr, "error: %s\n", se.schema_text ());
        break;
      }
#endif
    case serializer_error::app:
      {
        fprintf (stderr, "application error: %d\n", se.app_code ());
        break;
      }
    default:
      break;
    }

    return 1;
  }

  return 0;
}
