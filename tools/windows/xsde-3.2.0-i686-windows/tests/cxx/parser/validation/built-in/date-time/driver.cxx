// file      : tests/cxx/parser/validation/built-in/date-time/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in date and time types validation.
//
#include <cassert>

#include <xsde/cxx/parser/validating/xml-schema-pimpl.hxx>

using namespace xsde::cxx;
using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  using xsde::cxx::time;

  // Good.
  //

  // gday & time zone parsing
  //
  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("---1");
    p._characters ("2+12:00");
    p._post ();
    assert (p.post_gday () == gday (12, 12, 0));
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---01");
    p._post ();
    assert (p.post_gday () == gday (1));
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---31");
    p._post ();
    assert (p.post_gday () == gday (31));
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---15Z");
    p._post ();
    assert (p.post_gday () == gday (15, 0, 0));
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---15-14:00");
    p._post ();
    assert (p.post_gday () == gday (15, -14, -0));
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---15-12:59");
    p._post ();
    assert (p.post_gday () == gday (15, -12, -59));
  }

  // gmonth
  //
  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("--1");
    p._characters ("0+12:00");
    p._post ();
    assert (p.post_gmonth () == gmonth (10, 12, 0));
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--01");
    p._post ();
    assert (p.post_gmonth () == gmonth (1));
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12Z");
    p._post ();
    assert (p.post_gmonth () == gmonth (12, 0, 0));
  }

  // gyear
  //
  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("20");
    p._characters ("07+12:00");
    p._post ();
    assert (p.post_gyear () == gyear (2007, 12, 0));
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0001");
    p._post ();
    assert (p.post_gyear () == gyear (1));
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-20000Z");
    p._post ();
    assert (p.post_gyear () == gyear (-20000, 0, 0));
  }

  // gmonth_day
  //
  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("--1");
    p._characters ("0-28+12:00  ");
    p._post ();
    assert (p.post_gmonth_day () == gmonth_day (10, 28, 12, 00));
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12-31");
    p._post ();
    assert (p.post_gmonth_day () == gmonth_day (12, 31));
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--01-01Z");
    p._post ();
    assert (p.post_gmonth_day () == gmonth_day (1, 1, 0, 0));
  }

  // gyear_month
  //
  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("200");
    p._characters ("7-12+12:00  ");
    p._post ();
    assert (p.post_gyear_month () == gyear_month (2007, 12, 12, 0));
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2007-10");
    p._post ();
    assert (p.post_gyear_month () == gyear_month (-2007, 10));
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20007-10Z");
    p._post ();
    assert (p.post_gyear_month () == gyear_month (20007, 10, 0, 0));
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-20007-01");
    p._post ();
    assert (p.post_gyear_month () == gyear_month (-20007, 1));
  }

  // date
  //
  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("200");
    p._characters ("7-12-26+12:00  ");
    p._post ();
    assert (p.post_date () == date (2007, 12, 26, 12, 0));
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2007-10-15");
    p._post ();
    assert (p.post_date () == date (-2007, 10, 15));
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20007-12-31Z");
    p._post ();
    assert (p.post_date () == date (20007, 12, 31, 0, 0));
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-20007-01-01");
    p._post ();
    assert (p.post_date () == date (-20007, 1, 1));
  }

  // time
  //
  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("12:");
    p._characters ("46:23.456+12:00  ");
    p._post ();
    assert (p.post_time () == time (12, 46, 23.456, 12, 0));
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("12:13:14");
    p._post ();
    assert (p.post_time () == time (12, 13, 14.0));
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("12:13:14Z");
    p._post ();
    assert (p.post_time () == time (12, 13, 14.0, 0, 0));
  }

  // date_time
  //
  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("200");
    p._characters ("7-12-26T12:13:23.456+12:00  ");
    p._post ();
    assert (p.post_date_time () ==
            date_time (2007, 12, 26, 12, 13, 23.456, 12, 0));
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2007-10-15T12:13:14");
    p._post ();
    assert (p.post_date_time () == date_time (-2007, 10, 15, 12, 13, 14.0));
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20007-12-31T12:13:14Z");
    p._post ();
    assert (p.post_date_time () ==
            date_time (20007, 12, 31, 12, 13, 14.0, 0, 0));
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-20007-01-01T12:13:14");
    p._post ();
    assert (p.post_date_time () == date_time (-20007, 1, 1, 12, 13, 14.0));
  }

  // duration
  //
  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("-P200");
    p._characters ("7Y13M32DT25H61M234.56S  ");
    p._post ();
    assert (p.post_duration () ==
            duration (true, 2007, 13, 32, 25, 61, 234.56));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1Y");
    p._post ();
    assert (p.post_duration () == duration (false, 1, 0, 0, 0, 0, 0.0));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1M");
    p._post ();
    assert (p.post_duration () == duration (false, 0, 1, 0, 0, 0, 0.0));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1D");
    p._post ();
    assert (p.post_duration () == duration (false, 0, 0, 1, 0, 0, 0.0));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT1H");
    p._post ();
    assert (p.post_duration () == duration (false, 0, 0, 0, 1, 0, 0.0));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT1M");
    p._post ();
    assert (p.post_duration () == duration (false, 0, 0, 0, 0, 1, 0.0));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT1.1S");
    p._post ();
    assert (p.post_duration () == duration (false, 0, 0, 0, 0, 0, 1.1));
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1YT1S");
    p._post ();
    assert (p.post_duration () == duration (false, 1, 0, 0, 0, 0, 1.0));
  }

  // Bad
  //

  // gday & time zone parsing
  //
  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---1");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---32");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---2X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12asd");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---1212:00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12+2:00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12+1200");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12+15:00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12+12:60");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  {
    context c;
    gday_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("---12+14:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gday_value);
  }

  // gmonth
  //
  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--13");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--1X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  {
    context c;
    gmonth_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--11+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_value);
  }

  // gyear
  //
  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("207");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-207");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0000");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20X7");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  {
    context c;
    gyear_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_value);
  }

  // gmonth_day
  //
  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-12-12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--1212");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12?12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--00-12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12-00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--13-23");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12-32");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--1X-12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--12-2X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  {
    context c;
    gmonth_day_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--11-11+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gmonth_day_value);
  }

  // gyear_month
  //
  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("207-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-207-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0000-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20X7-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007?12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-0");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-13");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-1X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  {
    context c;
    gyear_month_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_gyear_month_value);
  }

  // date
  //
  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("207-01-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-207-01-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0000-01-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20X7-01-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007?01-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-0-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-00-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-13-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-1X-01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10?12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-0");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-32");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-2X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  {
    context c;
    date_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_value);
  }

  // time
  //
  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1:01:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2X:01:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23?01:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:0:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:60:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:4X:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10?12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10:");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10:0");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10:01.");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10:60");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:10:2X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("24:01:00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("24:00:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  {
    context c;
    time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:01:01+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_time_value);
  }

  // date_time
  //
  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("207-01-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-207-01-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0000-01-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("20X7-01-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007?01-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-0-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-00-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-13-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-1X-01T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10?12T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-0T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-00T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-32T12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-10-2XT12:13:14");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T1:01:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T2X:01:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23?01:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:0:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:60:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:4X:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10?12");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10:");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10:0");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10:01.");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10:60");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T23:10:2X");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T24:01:00");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T24:00:01");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("23:01:01+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  {
    context c;
    date_time_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007-01-01T12:13:14+12:3o");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_date_time_value);
  }

  // duration
  //
  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2007Y");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2007Y");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P-2007Y");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P-1M");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P-1D");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT-1H");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT-1M");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT-1.1S");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1H1M1S");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1M1Y");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT1S1H");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("PT1H1Y");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1Ygarbage");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  {
    context c;
    duration_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("P1YT");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_duration_value);
  }

  return 0;
}
