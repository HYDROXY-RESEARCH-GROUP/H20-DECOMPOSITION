// file      : examples/cxx/hybrid/evolution/passthrough/unknown-type.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

// Include transform.hxx (which includes unknown-type.hxx) instead of
// unknown-type.hxx.
//
#include "transform.hxx"

namespace transform
{
  unknown_type::
  unknown_type ()
      : name_ ("unknown"), content_ ("unknown", 0) // Dummy names.
  {
  }
}
