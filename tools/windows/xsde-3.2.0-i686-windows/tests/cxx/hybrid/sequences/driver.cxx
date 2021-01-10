// file      : tests/cxx/hybrid/sequences/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test sequence templates.
//
#include <string>
#include <cassert>

#include <xsde/cxx/config.hxx>

#ifndef XSDE_STL
#include <xsde/cxx/strdupx.hxx>
#endif

#include <xsde/cxx/hybrid/sequence.hxx>

using std::string;
using namespace xsde::cxx;
using namespace xsde::cxx::hybrid;

void
data_destructor (void* p, size_t)
{
  delete static_cast<string*> (p);
}

void
data_destructor_pos (void* p, size_t i)
{
  switch (i)
  {
  case 0:
    {
      delete static_cast<string*> (p);
      break;
    }
  case 1:
    {
      delete static_cast<int*> (p);
      break;
    }
  }
}

int
main ()
{
  //
  // pod_sequence
  //
  typedef pod_sequence<int> pod;

  {
    pod s;
    s.push_back (111);
    assert (s.size () == 1 && s[0] == 111);
    s.pop_back ();
    assert (s.size () == 0);
  }

  {
    pod s;
    s.push_back (111);
    s.erase (s.begin ());
    assert (s.size () == 0);

    s.push_back (111);
    s.push_back (222);
    s.push_back (333);
    s.erase (s.begin ());
    assert (s.size () == 2 && s[0] == 222 && s[1] == 333);

    s.push_back (444);
    s.erase (s.begin () + 1);
    assert (s.size () == 2 && s[0] == 222 && s[1] == 444);

    s.push_back (555);
    s.erase (s.begin () + 2);
    assert (s.size () == 2 && s[0] == 222 && s[1] == 444);
  }

  {
    pod s;
    s.reserve (2);
    s.push_back (111);
    s.push_back (222);
    s.push_back (333);
    assert (s.size () == 3 && s[0] == 111 && s[1] == 222 && s[2] == 333);

    pod c;
    c.assign (s.begin (), s.size ());
    assert (c.size () == 3 && c[0] == 111 && c[1] == 222 && c[2] == 333);
  }

  {
    pod s;
    s.insert (s.begin (), 111);
    assert (s.size () == 1 && s[0] == 111);
    s.push_back (222);
    s.push_back (333);

    s.insert (s.begin (), 444);
    assert (s[0] == 444);

    s.insert (s.begin () + 1, 555);
    assert (s[1] == 555);

    s.insert (s.end (), 666);
    assert (s[5] == 666);

    assert (s[0] == 444 && s[1] == 555 && s[2] == 111 &&
            s[3] == 222 && s[4] == 333 && s[5] == 666);
  }

  {
    pod s;
    s.reserve (2);
    s.push_back (111);
    s.push_back (222);
    s.insert (s.begin () + 1, 333);
    assert (s[0] == 111 && s[1] == 333 && s[2] == 222);
  }

  //
  // fix_sequence
  //
  typedef fix_sequence<string> fix;

  {
    fix s;
    s.push_back ("aaa");
    assert (s.size () == 1 && s[0] == "aaa");
    s.pop_back ();
    assert (s.size () == 0);
  }

  {
    fix s;
    s.push_back ("aaa");
    s.erase (s.begin ());
    assert (s.size () == 0);

    s.push_back ("aaa");
    s.push_back ("bbb");
    s.push_back ("ccc");
    s.erase (s.begin ());
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ccc");

    s.push_back ("ddd");
    s.erase (s.begin () + 1);
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ddd");

    s.push_back ("eee");
    s.erase (s.begin () + 2);
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ddd");
  }

  {
    fix s;
    s.reserve (2);
    s.push_back ("aaa");
    s.push_back ("bbb");
    s.push_back ("ccc");
    assert (s.size () == 3 && s[0] == "aaa" &&
            s[1] == "bbb" && s[2] == "ccc");

    fix c;
    c.assign (s.begin (), s.size ());
    assert (c.size () == 3 && c[0] == "aaa" &&
            c[1] == "bbb" && c[2] == "ccc");
  }

  {
    fix s;
    s.insert (s.begin (), "aaa");
    assert (s.size () == 1 && s[0] == "aaa");
    s.push_back ("bbb");
    s.push_back ("ccc");

    s.insert (s.begin (), "ddd");
    assert (s[0] == "ddd");

    s.insert (s.begin () + 1, "eee");
    assert (s[1] == "eee");

    s.insert (s.end (), "fff");
    assert (s[5] == "fff");

    assert (s[0] == "ddd" && s[1] == "eee" && s[2] == "aaa" &&
            s[3] == "bbb" && s[4] == "ccc" && s[5] == "fff");
  }

  {
    fix s;
    s.reserve (2);
    s.push_back ("aaa");
    s.push_back ("bbb");
    s.insert (s.begin () + 1, "ccc");
    assert (s[0] == "aaa" && s[1] == "ccc" && s[2] == "bbb");
  }

  //
  // var_sequence
  //
  typedef var_sequence<string> var;

  {
    var s;
    s.push_back (new string ("aaa"));
    assert (s.size () == 1 && s[0] == "aaa");
    s.pop_back ();
    assert (s.size () == 0);
  }

  {
    var s;
    s.push_back (new string ("aaa"));
    s.erase (s.begin ());
    assert (s.size () == 0);

    s.push_back (new string ("aaa"));
    s.push_back (new string ("bbb"));
    s.push_back (new string ("ccc"));
    s.erase (s.begin ());
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ccc");

    s.push_back (new string ("ddd"));
    s.erase (s.begin () + 1);
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ddd");

    s.push_back (new string ("eee"));
    s.erase (s.begin () + 2);
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ddd");
  }

  {
    var s;
    s.reserve (2);
    s.push_back (new string ("aaa"));
    s.push_back (new string ("bbb"));
    s.push_back (new string ("ccc"));
    assert (s.size () == 3 && s[0] == "aaa" &&
            s[1] == "bbb" && s[2] == "ccc");
  }

  {
    var s;
    s.insert (s.begin (), new string ("aaa"));
    assert (s.size () == 1 && s[0] == "aaa");
    s.push_back (new string ("bbb"));
    s.push_back (new string ("ccc"));

    s.insert (s.begin (), new string ("ddd"));
    assert (s[0] == "ddd");

    s.insert (s.begin () + 1, new string ("eee"));
    assert (s[1] == "eee");

    s.insert (s.end (), new string ("fff"));
    assert (s[5] == "fff");

    assert (s[0] == "ddd" && s[1] == "eee" && s[2] == "aaa" &&
            s[3] == "bbb" && s[4] == "ccc" && s[5] == "fff");
  }

  {
    var s;
    s.reserve (2);
    s.push_back (new string ("aaa"));
    s.push_back (new string ("bbb"));
    s.insert (s.begin () + 1, new string ("ccc"));
    assert (s[0] == "aaa" && s[1] == "ccc" && s[2] == "bbb");
  }

  {
    var s;
    s.push_back (new string ("aaa"));
    s.push_back (new string ("bbb"));
    s.push_back (new string ("ccc"));
    delete s.detach (s.begin () + 1);
    s.attach (s.begin () + 1, new string ("bbb"));
    assert (s[0] == "aaa" && s[1] == "bbb" && s[2] == "ccc");
  }

  //
  // string_sequence
  //
  typedef string_sequence str;

#ifndef XSDE_STL
  using xsde::cxx::strdupx;

  {
    str s;
    s.push_back (strdupx ("aaa"));
    assert (s.size () == 1 && s[0] == string ("aaa"));
    s.pop_back ();
    assert (s.size () == 0);
  }

  {
    str s;
    s.push_back_copy ("aaa");
    s.erase (s.begin ());
    assert (s.size () == 0);

    s.push_back_copy ("aaa");
    s.push_back_copy ("bbb");
    s.push_back_copy ("ccc");
    s.erase (s.begin ());
    assert (s.size () == 2 &&
            s[0] == string ("bbb") && s[1] == string ("ccc"));

    s.push_back_copy ("ddd");
    s.erase (s.begin () + 1);
    assert (s.size () == 2 &&
            s[0] == string ("bbb") && s[1] == string ("ddd"));

    s.push_back_copy ("eee");
    s.erase (s.begin () + 2);
    assert (s.size () == 2 &&
            s[0] == string ("bbb") && s[1] == string ("ddd"));
  }

  {
    str s;
    s.reserve (2);
    s.push_back_copy ("aaa");
    s.push_back_copy ("bbb");
    s.push_back_copy ("ccc");
    assert (s.size () == 3 &&
            s[0] == string ("aaa") &&
            s[1] == string ("bbb") &&
            s[2] == string ("ccc"));
  }

  {
    str s;
    s.insert (s.begin (), strdupx ("aaa"));
    assert (s.size () == 1 && s[0] == string ("aaa"));
    s.push_back_copy ("bbb");
    s.push_back_copy ("ccc");

    s.insert (s.begin (), strdupx ("ddd"));
    assert (s[0] == string ("ddd"));

    s.insert (s.begin () + 1, strdupx ("eee"));
    assert (s[1] == string ("eee"));

    s.insert (s.end (), strdupx ("fff"));
    assert (s[5] == string ("fff"));

    assert (s[0] == string ("ddd") && s[1] == string ("eee") &&
            s[2] == string ("aaa") && s[3] == string ("bbb") &&
            s[4] == string ("ccc") && s[5] == string ("fff"));
  }

  {
    str s;
    s.reserve (2);
    s.push_back_copy ("aaa");
    s.push_back_copy ("bbb");
    s.insert (s.begin () + 1, strdupx ("ccc"));
    assert (s[0] == string ("aaa") &&
            s[1] == string ("ccc") &&
            s[2] == string ("bbb"));
  }

  {
    str s;
    s.reserve (2);
    s.push_back_copy ("aaa");
    s.push_back_copy ("bbb");
    s.push_back_copy ("ccc");
    delete[] s.detach (s.begin () + 1);
    s.attach (s.begin () + 1, strdupx ("bbb"));
    assert (s[0] == string ("aaa") &&
            s[1] == string ("bbb") &&
            s[2] == string ("ccc"));
  }

#else

  {
    str s;
    s.push_back ("aaa");
    assert (s.size () == 1 && s[0] == "aaa");
    s.pop_back ();
    assert (s.size () == 0);
  }

  {
    str s;
    s.push_back ("aaa");
    s.erase (s.begin ());
    assert (s.size () == 0);

    s.push_back ("aaa");
    s.push_back ("bbb");
    s.push_back ("ccc");
    s.erase (s.begin ());
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ccc");

    s.push_back ("ddd");
    s.erase (s.begin () + 1);
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ddd");

    s.push_back ("eee");
    s.erase (s.begin () + 2);
    assert (s.size () == 2 && s[0] == "bbb" && s[1] == "ddd");
  }

  {
    str s;
    s.reserve (2);
    s.push_back ("aaa");
    s.push_back ("bbb");
    s.push_back ("ccc");
    assert (s.size () == 3 &&
            s[0] == "aaa" && s[1] == "bbb" && s[2] == "ccc");
  }

  {
    str s;
    s.insert (s.begin (), "aaa");
    assert (s.size () == 1 && s[0] == "aaa");
    s.push_back ("bbb");
    s.push_back ("ccc");

    s.insert (s.begin (), "ddd");
    assert (s[0] == "ddd");

    s.insert (s.begin () + 1, "eee");
    assert (s[1] == "eee");

    s.insert (s.end (), "fff");
    assert (s[5] == "fff");

    assert (s[0] == "ddd" && s[1] == "eee" && s[2] == "aaa" &&
            s[3] == "bbb" && s[4] == "ccc" && s[5] == "fff");
  }

  {
    str s;
    s.reserve (2);
    s.push_back ("aaa");
    s.push_back ("bbb");
    s.insert (s.begin () + 1, "ccc");
    assert (s[0] == "aaa" && s[1] == "ccc" && s[2] == "bbb");
  }
#endif

  //
  // data_sequence
  //
  typedef data_sequence data;

  {
    data s;
    s.destructor (&data_destructor);
    s.push_back (new string ("aaa"));
    s.push_back (new string ("bbb"));
    assert (*static_cast<string*> (s[0]) == "aaa" &&
            *static_cast<string*> (s[1]) == "bbb");
  }

  {
    data s;
    s.destructor (&data_destructor_pos);
    s.push_back (new string ("aaa"));
    s.push_back (new int (5));
    assert (*static_cast<string*> (s[0]) == "aaa" &&
            *static_cast<int*> (s[1]) == 5);
  }

  return 0;
}
