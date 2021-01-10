// file      : tests/cxx/string/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test xsde::cxx::string string type.
//
#include <assert.h>

#include <xsde/cxx/string.hxx>

using xsde::cxx::string;

int
main ()
{
  // Start with un-initialized string.
  //
  {
    string s;
    assert (s.data () == 0 && s.size () == 0 && s.capacity () == 0);
  }

  // Test initialization with an empty string.
  //
  {
    string s;
    s.assign ("", 0);
    assert (s.size () == 0 && s.capacity () == 64 && s == "");
  }

  // String starts with at least 64 bytes.
  //
  {
    string s;
    s.assign ("aaa");
    assert (s.size () == 3 && s == "aaa" && s.capacity () == 64);
  }


  // If we grow beyond 32 it should be greater of new size and 2*64.
  //
  {
    const char v[] =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" // 32
      "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
      "cccccccccccccccccccccccccccccccc";

    string s;
    s.assign ("aaa");
    s.assign (v);
    assert (s.size () == 96 && s == v && s.capacity () == 128);
  }

  // If we grow beyond 32 it should be greater of new size and 2*32.
  //
  {
    const char v[] =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" // 32
      "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
      "cccccccccccccccccccccccccccccccc"
      "dddddddddddddddddddddddddddddddd"
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";

    string s;
    s.assign ("aaa");
    s.assign (v);
    assert (s.size () == 159 && s == v && s.capacity () == 160);
  }

  // Make sure the new capacity is even.
  //
  {
    const char v[] =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" // 32
      "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
      "cccccccccccccccccccccccccccccccc"
      "dddddddddddddddddddddddddddddddd"
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";

    string s;
    s.assign ("aaa");
    s.assign (v);
    assert (s.size () == 160 && s == v && s.capacity () == 162);
  }

  // Test append
  //
  {
    const char v[] =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" // 32
      "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
      "cccccccccccccccccccccccccccccccc"
      "dddddddddddddddddddddddddddddddd"
      "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";

    string s;
    s.assign ("aaa");
    s.append (&v[3]);
    assert (s.size () == 160 && s == v && s.capacity () == 162);
  }

  return 0;
}
