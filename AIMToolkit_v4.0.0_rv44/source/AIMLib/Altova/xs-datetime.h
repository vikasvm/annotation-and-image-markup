/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

////////////////////////////////////////////////////////////////////////
//
// xs-datetime.h
//
// This file was generated by XMLSpy 2012r2sp1 Enterprise Edition.
//
// YOU SHOULD NOT MODIFY THIS FILE, BECAUSE IT WILL BE
// OVERWRITTEN WHEN YOU RE-RUN CODE GENERATION.
//
// Refer to the XMLSpy Documentation for further details.
// http://www.altova.com/xmlspy
//
////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _INCLUDED_XS_DATETIME_H_
#define _INCLUDED_XS_DATETIME_H_

#include "AltovaDefs.h"
#include "exception.h"


namespace altova
{

	const __int64 TicksPerSecond = 10000000;
	const __int64 SecondsPerDay = 86400;
	const __int64 TicksPerDay = SecondsPerDay * TicksPerSecond;

	class DateTime
	{
		__int64 m_value;
		short	m_reserved[3];
		short	m_timezone;


		static ALTOVA_DECLSPECIFIER __int64 Init(int year, unsigned char month, unsigned char day, 
			unsigned char hour, unsigned char minute, double second);

	public:
		static ALTOVA_DECLSPECIFIER bool IsLeapYear(int year);
		enum {
			NO_TIMEZONE = -32768
		};

		explicit DateTime(__int64 value) : m_value(value), m_timezone(NO_TIMEZONE) {}
		DateTime() : m_value(0), m_timezone(NO_TIMEZONE) {}
		DateTime(__int64 value, short timezone) : m_value(value), m_timezone(timezone) {}
		ALTOVA_DECLSPECIFIER DateTime(int year, unsigned char month, unsigned char day, 
			unsigned char hour, unsigned char minute, double second);
		ALTOVA_DECLSPECIFIER DateTime(int year, unsigned char month, unsigned char day, 
			unsigned char hour, unsigned char minute, double second, short timezone);

		ALTOVA_DECLSPECIFIER int Year() const;
		ALTOVA_DECLSPECIFIER unsigned char Month() const;
		ALTOVA_DECLSPECIFIER unsigned char Day() const;
		ALTOVA_DECLSPECIFIER unsigned char Hour() const;
		ALTOVA_DECLSPECIFIER unsigned char Minute() const;
		ALTOVA_DECLSPECIFIER double Second() const;
		ALTOVA_DECLSPECIFIER short Timezone() const { return m_timezone; }
		ALTOVA_DECLSPECIFIER bool HasTimezone() const { return m_timezone != NO_TIMEZONE; }

		/** Returns the day of year. 1-366 */
		ALTOVA_DECLSPECIFIER int DayOfYear() const;

		/** Returns the week of the month */
		ALTOVA_DECLSPECIFIER int WeekOfMonth() const;

		/** Returns the weekday, monday is zero (ISO-8601). */
		ALTOVA_DECLSPECIFIER int Weekday() const { return ( m_value / TicksPerDay ) % 7; }

		/** Returns the week number according to ISO-8601. */
		ALTOVA_DECLSPECIFIER int Weeknumber() const;


		__int64 Value() const { return m_value; }
		ALTOVA_DECLSPECIFIER __int64 NormalizedValue() const;

		ALTOVA_DECLSPECIFIER static void GetDateFromTimeValue(__int64 tvTime, int& rnYear, int& rnMonth, int& rnDay);
	};


	class DayTimeDuration
	{
		__int64 m_value;
	
	public:
		DayTimeDuration() : m_value(0) {}
		ALTOVA_DECLSPECIFIER DayTimeDuration(int days, int hours, int minutes, double seconds);
		explicit DayTimeDuration(__int64 value) : m_value(value) {}

		ALTOVA_DECLSPECIFIER int Days() const;
		ALTOVA_DECLSPECIFIER int Hours() const;
		ALTOVA_DECLSPECIFIER int Minutes() const;
		ALTOVA_DECLSPECIFIER double Seconds() const;

		__int64 Value() const { return m_value; }

		bool IsNegative() const { return m_value < 0; }
		bool IsPositive() const { return m_value > 0; }
	};


	class YearMonthDuration
	{
		int m_value;

	public:
		YearMonthDuration() : m_value(0) {}
		ALTOVA_DECLSPECIFIER YearMonthDuration(int years, int months);
		explicit YearMonthDuration(int value) : m_value(value) {}

		ALTOVA_DECLSPECIFIER int Years() const;
		ALTOVA_DECLSPECIFIER int Months() const;

		int Value() const { return m_value; }

		bool IsNegative() const { return m_value < 0; }
		bool IsPositive() const { return m_value > 0; }
	};


	class Duration
	{
		DayTimeDuration dayTime;
		YearMonthDuration yearMonth;

	public:
		Duration() {}
		Duration(const DayTimeDuration& dt) : dayTime(dt) {}
		Duration(const YearMonthDuration& ym) : yearMonth(ym) {}
		ALTOVA_DECLSPECIFIER Duration(const YearMonthDuration& ym, const DayTimeDuration& dt);

		DayTimeDuration DayTime() const { return dayTime; }
		YearMonthDuration YearMonth() const { return yearMonth; }

		int Years() const { return yearMonth.Years(); }
		int Months() const { return yearMonth.Months(); }
		int Days() const { return dayTime.Days(); }
		int Hours() const { return dayTime.Hours(); }
		int Minutes() const { return dayTime.Minutes(); }
		double Seconds() const { return dayTime.Seconds(); }
		
		bool IsNegative() const { return dayTime.IsNegative() || yearMonth.IsNegative(); }
		bool IsPositive() const { return dayTime.IsPositive() || yearMonth.IsPositive(); }
	};


	// dateTime arithmetics
	ALTOVA_DECLSPECIFIER DayTimeDuration operator- (const DateTime& first, const DateTime& second);
	
	ALTOVA_DECLSPECIFIER DayTimeDuration operator- (const DayTimeDuration& x);
	ALTOVA_DECLSPECIFIER DayTimeDuration operator+ (const DayTimeDuration& first, const DayTimeDuration& second);
	ALTOVA_DECLSPECIFIER DayTimeDuration operator- (const DayTimeDuration& first, const DayTimeDuration& second);

	ALTOVA_DECLSPECIFIER YearMonthDuration operator- (const YearMonthDuration& x);
	ALTOVA_DECLSPECIFIER YearMonthDuration operator+ (const YearMonthDuration& first, const YearMonthDuration& second);
	ALTOVA_DECLSPECIFIER YearMonthDuration operator- (const YearMonthDuration& first, const YearMonthDuration& second);

	ALTOVA_DECLSPECIFIER DateTime operator+ (const DateTime& first, const DayTimeDuration& second);
	ALTOVA_DECLSPECIFIER DateTime operator- (const DateTime& first, const DayTimeDuration& second);
	ALTOVA_DECLSPECIFIER DateTime operator+ (const DateTime& first, const YearMonthDuration& second);
	ALTOVA_DECLSPECIFIER DateTime operator- (const DateTime& first, const YearMonthDuration& second);

	ALTOVA_DECLSPECIFIER DateTime operator+ (const DateTime& first, const Duration& second);
	ALTOVA_DECLSPECIFIER DateTime operator- (const DateTime& first, const Duration& second);

	inline Duration operator-(const Duration& a) { return Duration(-a.YearMonth(), -a.DayTime()); }

	inline Duration operator+(const Duration& a, const Duration& b) 
	{ 
		return Duration(a.YearMonth() + b.YearMonth(), a.DayTime() + b.DayTime() ); 
	}

	inline Duration operator-(const Duration& a, const Duration& b) 
	{ 
		return Duration(a.YearMonth() - b.YearMonth(), a.DayTime() - b.DayTime() ); 
	}

	// these have their complexities... 
	ALTOVA_DECLSPECIFIER bool operator== (const DateTime& first, const DateTime& second);
	ALTOVA_DECLSPECIFIER bool operator!= (const DateTime& first, const DateTime& second);
	ALTOVA_DECLSPECIFIER bool operator< (const DateTime& first, const DateTime& second);
	inline bool operator> (const DateTime& first, const DateTime& second) { return second < first; }
	ALTOVA_DECLSPECIFIER bool operator<= (const DateTime& first, const DateTime& second);
	inline bool operator>= (const DateTime& first, const DateTime& second) { return second <= first; }

	inline bool operator== (const DayTimeDuration& first, const DayTimeDuration& second) { return first.Value() == second.Value(); }
	inline bool operator!= (const DayTimeDuration& first, const DayTimeDuration& second) { return first.Value() != second.Value(); }
	inline bool operator< (const DayTimeDuration& first, const DayTimeDuration& second) { return first.Value() < second.Value(); }
	inline bool operator> (const DayTimeDuration& first, const DayTimeDuration& second) { return first.Value() > second.Value(); }
	inline bool operator<= (const DayTimeDuration& first, const DayTimeDuration& second) { return first.Value() <= second.Value(); }
	inline bool operator>= (const DayTimeDuration& first, const DayTimeDuration& second) { return first.Value() >= second.Value(); }

	inline bool operator== (const YearMonthDuration& first, const YearMonthDuration& second) { return first.Value() == second.Value(); }
	inline bool operator!= (const YearMonthDuration& first, const YearMonthDuration& second) { return first.Value() != second.Value(); }
	inline bool operator< (const YearMonthDuration& first, const YearMonthDuration& second) { return first.Value() < second.Value(); }
	inline bool operator> (const YearMonthDuration& first, const YearMonthDuration& second) { return first.Value() > second.Value(); }
	inline bool operator<= (const YearMonthDuration& first, const YearMonthDuration& second) { return first.Value() <= second.Value(); }
	inline bool operator>= (const YearMonthDuration& first, const YearMonthDuration& second) { return first.Value() >= second.Value(); }

	ALTOVA_DECLSPECIFIER bool operator== (const Duration& first, const Duration& second);
	inline bool operator!= (const Duration& first, const Duration& second) { return !(first == second); }
	ALTOVA_DECLSPECIFIER bool operator< (const Duration& first, const Duration& second);
	inline bool operator> (const Duration& first, const Duration& second) { return second < first; }
	ALTOVA_DECLSPECIFIER bool operator<= (const Duration& first, const Duration& second);
	inline bool operator>= (const Duration& first, const Duration& second) { return second <= first; }
}

#endif // guard

