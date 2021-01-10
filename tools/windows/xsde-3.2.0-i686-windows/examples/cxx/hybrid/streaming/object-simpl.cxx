// file      : examples/cxx/hybrid/streaming/object-simpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

// Include position-simpl.hxx (which includes object-simpl.hxx)
// instead of object-simpl.hxx.
//
#include "position-simpl.hxx"

// Position measurement instrument interface.
//
struct measurements
{
  float lat;
  float lon;
};

measurements test_measurements [8] =
{
  {-33.8569F, 18.5083F},
  {-33.8568F, 18.5083F},
  {-33.8568F, 18.5082F},
  {-33.8570F, 18.5083F},
  {-33.8569F, 18.5084F},
  {-33.8570F, 18.5084F},
  {-33.8570F, 18.5082F},
  {-33.8569F, 18.5082F}
};

static void
measure_position (unsigned int n, float& lat, float& lon)
{
  // Call the instrument to measure the position.
  //
  lat = test_measurements[n].lat;
  lon = test_measurements[n].lon;
}

// Serializer implementation.
//
void object_simpl::
pre (const object& obj)
{
  // Cache the object id and determine how many position measuremenets
  // we need to take.
  //
  id_ = obj.id ();
  count_ = 8;
}

unsigned int object_simpl::
id ()
{
  return id_;
}

bool object_simpl::
position_next ()
{
  return count_ > 0;
}

const position& object_simpl::
position ()
{
  count_--;
  measure_position (count_, cur_pos_.lat (), cur_pos_.lon ());
  return cur_pos_;
}
