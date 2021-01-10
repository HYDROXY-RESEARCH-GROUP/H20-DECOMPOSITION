// file      : examples/cxx/hybrid/streaming/object-pimpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

// Include position-pimpl.hxx (which includes object-pimpl.hxx)
// instead of object-pimpl.hxx.
//
#include "position-pimpl.hxx"

using namespace std;

void object_pimpl::
pre ()
{
  // Initialize the variables.
  //
  count_ = 0;
  avg_lat_ = 0.0;
  avg_lon_ = 0.0;
}

void object_pimpl::
id (unsigned int id)
{
  id_ = id;
}

void object_pimpl::
position (const ::position& p)
{
  count_++;
  avg_lat_ += p.lat ();
  avg_lon_ += p.lon ();
}

object* object_pimpl::
post_object ()
{
  avg_lat_ /= count_;
  avg_lon_ /= count_;

  cerr << "object " << id_ << ": " << avg_lat_ << " " << avg_lon_ << endl;

  return 0; // We don't construct the object so return NULL.
}
