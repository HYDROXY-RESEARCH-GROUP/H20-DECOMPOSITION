// file      : tests/cxx/hashmap/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test xsde::cxx::hashmap type.
//
#include <assert.h>
#include <string.h>

#include <iostream>

#include <xsde/cxx/hashmap.hxx>

using xsde::cxx::hashmap;
using namespace std;

const char* table[] =
{
  "apple",      "1",
  "orange",     "2",
  "peach",      "3",
  "apricot",    "4",
  "mango",      "5",
  "banana",     "6",
  "pear",       "7",
  "grapefruit", "8",
  "tangerine",  "9",
};

const size_t table_size = (sizeof (table) / sizeof (const char*)) / 2;

int
main ()
{
  {
    hashmap h (1, sizeof (const char*));
    assert (h.size () == 0 && h.empty () && h.max_bucket_size () == 0);
    assert (h.begin () == h.end ());
  }

  {
    hashmap h (2, sizeof (const char*));

    const char* v = "bar";
    h.insert ("foo", &v);
    assert (h.size () == 1 && !h.empty () && h.max_bucket_size () == 1);
    assert (h.begin () != h.end ());
    const void* p = h.find ("foo");
    assert (p != 0 && *static_cast<const char* const*> (p) == v);
  }

  {
    hashmap h (5, sizeof (const char*));

    for (size_t i = 0; i < table_size; ++i)
    {
      const char* v = table[i * 2 + 1];
      h.insert (table[i * 2], &v);
    }

    assert (h.size () == table_size);

    for (size_t i = 0; i < table_size; ++i)
    {
      const char* v = table[i * 2 + 1];
      const void* p = h.find (table[i * 2]);
      assert (p != 0 && *static_cast<const char* const*> (p) == v);
    }

    // Figure out how many elements are in each bucket.
    //
    size_t bucket_entries[5] = {0, 0, 0, 0, 0};

    for (size_t i = 0; i < table_size; ++i)
    {
      bucket_entries[hashmap::hash (table[i * 2]) % 5]++;
    }

    size_t max = 0;

    for (size_t i = 0; i < 5; ++i)
    {
      if (bucket_entries[i] > max)
        max = bucket_entries[i];
    }

    assert (max == h.max_bucket_size ());

    // Test iteration
    //
    unsigned int n = 0;

    for (hashmap::const_iterator i = h.begin (); i != h.end (); ++i)
    {
      const void* p = *i;
      n += *static_cast<const char* const*> (p) [0];
    }

    assert (n == '1' + '2' + '3' + '4' + '5' + '6' + '7' + '8' + '9');
  }

  return 0;
}
