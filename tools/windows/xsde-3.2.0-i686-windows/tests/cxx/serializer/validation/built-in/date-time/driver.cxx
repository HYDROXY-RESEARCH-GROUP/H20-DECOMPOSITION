// file      : tests/cxx/serializer/validation/built-in/date-time/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in date and time types validation.
//
#include <cassert>

#include <xsde/cxx/serializer/validating/xml-schema-simpl.hxx>

using namespace xsde::cxx;
using namespace xsde::cxx::serializer;
using namespace xsde::cxx::serializer::validating;

int
main ()
{
  using xsde::cxx::time; // Conflicts with system time.

  // gday & time zone
  //
  {
    gday_simpl s;
    context c (0);
    s.pre (gday (0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    gday_simpl s;
    context c (0);
    s.pre (gday (32));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    gday_simpl s;
    context c (0);
    s.pre (gday (15, 15, 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    gday_simpl s;
    context c (0);
    s.pre (gday (15, 12, 60));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    gday_simpl s;
    context c (0);
    s.pre (gday (15, -12, 30));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    gday_simpl s;
    context c (0);
    s.pre (gday (15, 12, -30));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    gday_simpl s;
    context c (0);
    s.pre (gday (15, 14, 1));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  // gmonth
  //
  {
    gmonth_simpl s;
    context c (0);
    s.pre (gmonth (0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  {
    gmonth_simpl s;
    context c (0);
    s.pre (gmonth (13));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  // gyear
  //
  {
    gyear_simpl s;
    context c (0);
    s.pre (gyear (0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  // gmonth_day
  //
  {
    gmonth_day_simpl s;
    context c (0);
    s.pre (gmonth_day (0, 15));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    gmonth_day_simpl s;
    context c (0);
    s.pre (gmonth_day (6, 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    gmonth_day_simpl s;
    context c (0);
    s.pre (gmonth_day (13, 15));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    gmonth_day_simpl s;
    context c (0);
    s.pre (gmonth_day (6, 32));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  // gyear_month
  //
  {
    gyear_month_simpl s;
    context c (0);
    s.pre (gyear_month (0, 6));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    gyear_month_simpl s;
    context c (0);
    s.pre (gyear_month (2007, 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    gyear_month_simpl s;
    context c (0);
    s.pre (gyear_month (2007, 32));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  // date
  //
  {
    date_simpl s;
    context c (0);
    s.pre (date (0, 6, 15));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    date_simpl s;
    context c (0);
    s.pre (date (2007, 0, 15));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    date_simpl s;
    context c (0);
    s.pre (date (2007, 13, 15));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    date_simpl s;
    context c (0);
    s.pre (date (2007, 6, 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    date_simpl s;
    context c (0);
    s.pre (date (2007, 6, 32));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  // time
  //
  {
    time_simpl s;
    context c (0);
    s.pre (time (25, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    time_simpl s;
    context c (0);
    s.pre (time (24, 1, 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    time_simpl s;
    context c (0);
    s.pre (time (24, 0, 0.1));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    time_simpl s;
    context c (0);
    s.pre (time (12, 60, 30));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    time_simpl s;
    context c (0);
    s.pre (time (12, 30, 60.1));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    time_simpl s;
    context c (0);
    s.pre (time (12, 30, -30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  // date_time
  //
  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (0, 6, 32, 12, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 0, 32, 12, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 13, 32, 12, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 0, 12, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 32, 12, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 15, 25, 30, 30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 15, 24, 1, 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 15, 24, 0, 0.1));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 15, 12, 60, 30));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 15, 12, 30, 60.1));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    date_time_simpl s;
    context c (0);
    s.pre (date_time (2007, 6, 15, 12, 30, -30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  // duration
  //
  {
    duration_simpl s;
    context c (0);
    s.pre (duration (false, 2007, 6, 15, 12, 30, -30.0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  return 0;
}
