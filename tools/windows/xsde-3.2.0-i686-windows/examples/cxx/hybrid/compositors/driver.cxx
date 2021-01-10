// file      : examples/cxx/hybrid/compositors/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "compositors.hxx"

int
main (int, char*[])
{
  // Simple choice.
  //
  simple_choice sc;

  sc.a (123); // Automatically sets arm to a_tag.

  switch (sc.choice_arm ())
  {
  case simple_choice::a_tag:
    {
      sc.a ()++;
      break;
    }
  case simple_choice::b_tag:
    {
      // The b element is optional so we first need to check
      // if it is present.
      //
      if (sc.b_present ())
      {
        sc.b_present (false);
      }

      break;
    }
  case simple_choice::c_tag:
    {
      // The c element is a sequence.
      //
      simple_choice::c_sequence& s = sc.c ();

      for (simple_choice::c_iterator i = s.begin (); i != s.end(); ++i)
      {
        *i += 10;
      }

      break;
    }
  }


  // Nested choice.
  //
  nested_choice nc;

  // Initialize the choice with the 'sequence' arm.
  //
  nc.choice_present (true);
  nested_choice::choice_type& c = nc.choice ();
  c.choice_arm (nested_choice::choice_type::sequence_tag);
  c.sequence ().b (123);
  c.sequence ().c (true);

  nc.d (456);


  // Nested sequence.
  //
  nested_sequence ns;
  nested_sequence::sequence_sequence& s = ns.sequence ();

  for (int i = 0; i < 10; ++i)
  {
    nested_sequence::sequence_type x;
    x.a (i);

    if (i % 2)
    {
      // Initialize the nested sequence.
      //
      x.sequence1_present (true);
      x.sequence1 ().b (i);
      x.sequence1 ().c (true);
    }

    s.push_back (x);
  }

  return 0;
}
