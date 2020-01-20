// Problem 11947 - Cancer or Scorpio
// Vincent Cote - CPSC 3200
// Approach - Using given library for date manipulation. Use string manipulation to initialize the Date
// once the date is in memory use Date.addDay() to add 40 weeks (280 days). To get sign I checked date ranges
// and returned the proper sign. I also changed the overloaded << to match the date format requested by the question
// **My Code starts on line 211 / main at line 226**

// Date class
//
// This is an implementation of some common functionalities for dates.
// It can represent dates from Jan 1, 1753 to after (dates before that
// time are complicated...).
//

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <cctype>

using namespace std;
using namespace std::rel_ops;

struct Date {

  int yyyy;
  int mm;
  int dd;

  // no dates before 1753
  static int const BASE_YEAR = 1753;

  // Enumerated type for names of the days of the week
  enum dayName {SUN,MON,TUE,WED,THU,FRI,SAT};

  // Is a date valid
  static bool validDate(int yr, int mon, int day)
  {
    return yr >= BASE_YEAR && mon >= 1 && mon <= 12 &&
      day > 0 && day <= daysIn(mon, yr);
  }    

  bool isValid() const
  {
    return validDate(yyyy, mm, dd);
  }
  
  // Constructor to create a specific date.  If the date is invalid,
  // the behaviour is undefined
  Date(int yr = 1970, int mon = 1, int day = 1)
  {
    yyyy = yr;
    mm = mon;
    dd = day;
  }
  
  // Returns the day of the week for this
  dayName dayOfWeek() const
  {
    int a = (14 - mm) / 12;
    int y = yyyy - a;
    int m = mm + 12 * a - 2;
    return (dayName)((dd + y + y/4 - y/100 + y/400 + 31 * m / 12) % 7);
  }
  
  // comparison operators
  bool operator==(const Date &d) const
  {
    return dd == d.dd && mm == d.mm && yyyy == d.yyyy;
  }

  bool operator<(const Date &d) const
  {
    return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
      (yyyy == d.yyyy && mm == d.mm && dd < d.dd);
  }

  // Returns true if yr is a leap year
  static bool leapYear(int y)
  {
    return (y % 400 ==0 || (y % 4 == 0 && y % 100 != 0));
  }

  // number of days in this month
  static int daysIn(int m, int y)
  {
    switch (m) {
    case 4  :
    case 6  :
    case 9  :
    case 11 :
      return 30;
    case 2  :
      if (leapYear(y)) {
	return 29;
      }
      else {
	return 28;
      }
    default :
      return 31;
    }
  }
  
  // increment by day, month, or year
  //
  // Use negative argument to decrement
  //
  // If adding a month/year results in a date before BASE_YEAR, the result
  // is undefined.
  //
  // If adding a month/year results in an invalid date (Feb 29 on a non-leap
  // year, Feb 31, Jun 31, etc.), the results are automatically "rounded down"
  // to the last valid date

  // add n days to the date: complexity is about n/30 iterations
  void addDay(int n = 1)
  {
    dd += n;
    while (dd > daysIn(mm,yyyy)) {
      dd -= daysIn(mm,yyyy);
      if (++mm > 12) {
	mm = 1;
	yyyy++;
      }
    }
    
    while (dd < 1) {
      if (--mm < 1) {
	mm = 12;
	yyyy--;
      }
      dd += daysIn(mm,yyyy); 
    }
  }

  // add n months to the date: complexity is about n/12 iterations
  void addMonth(int n = 1)
  {
    mm += n;
    while (mm > 12) {
      mm -= 12;
      yyyy++;
    }
    
    while (mm < 1)  {
      mm += 12;
      yyyy--;
    }
    
    if (dd > daysIn(mm,yyyy)) {
      dd = daysIn(mm,yyyy);
    }
  }

  // add n years to the date
  void addYear(int n = 1)
  {
    yyyy += n;
    if (!leapYear(yyyy) && mm == 2 && dd == 29) {
      dd = 28;
    }
  }

  // number of days since 1753/01/01, including the current date
  int daysFromStart() const
  {
    int c = 0;
    Date d(BASE_YEAR, 1, 1);
    Date d2(d);

    d2.addYear(1);
    while (d2 < *this) {
      c += leapYear(d.yyyy) ? 366 : 365;
      d = d2;
      d2.addYear(1);
    }

    d2 = d;
    d2.addMonth(1);
    while (d2 < *this) {
      c += daysIn(d.mm, d.yyyy);
      d = d2;
      d2.addMonth(1);
    }
    while (d <= *this) {
      d.addDay();
      c++;
    }
    return c;
  }
};

// Reads a date in yyyy/mm/dd format, assumes date is valid and in the
// right format
istream& operator>>(istream &is, Date &d)
{
  char c;
  return is >> d.yyyy >> c >> d.mm >> c >> d.dd;
}

// print date in yyyy/mm/dd format
ostream& operator<< (ostream &os, const Date &d) {
  char t = os.fill('0');
	// Changed order to match question
	os << setw(2) << d.mm << '/' << setw(2) << d.dd << '/' << setw(4) << d.yyyy;
  os.fill(t);
  return os;
}

struct TableRow {
  std::string sign;
  Date start;
  Date end;

  TableRow(std::string s, Date st, Date e) {
    sign = s;
    start = st;
    end = e;
  }
};

TableRow Table[12] = {
  {TableRow("aquarius", Date(1900, 01, 21), Date(1900, 02, 19))},
  
};

std::string getSign(Date d) {
	if ((d.mm == 1 && d.dd >= 21) || (d.mm == 2 && d.dd <= 19)) return "aquarius";
	if ((d.mm == 2 && d.dd >= 20) || (d.mm == 3 && d.dd <= 20)) return "pisces";
	if ((d.mm == 3 && d.dd >= 21) || (d.mm == 4 && d.dd <= 20)) return "aries";
	if ((d.mm == 4 && d.dd >= 21) || (d.mm == 5 && d.dd <= 21)) return "taurus";
	if ((d.mm == 5 && d.dd >= 22) || (d.mm == 6 && d.dd <= 21)) return "gemini";
	if ((d.mm == 6 && d.dd >= 22) || (d.mm == 7 && d.dd <= 22)) return "cancer";
	if ((d.mm == 7 && d.dd >= 23) || (d.mm == 8 && d.dd <= 21)) return "leo";
	if ((d.mm == 8 && d.dd >= 22) || (d.mm == 9 && d.dd <= 23)) return "virgo";
	if ((d.mm == 9 && d.dd >= 24) || (d.mm == 10 && d.dd <= 23)) return "libra";
	if ((d.mm == 10 && d.dd >= 24) || (d.mm == 11 && d.dd <= 22)) return "scorpio";
	if ((d.mm == 11 && d.dd >= 23) || (d.mm == 12 && d.dd <= 22)) return "sagittarius";
	if ((d.mm == 12 && d.dd >= 23) || (d.mm == 01 && d.dd <= 20)) return "capricorn";
}

int main(void) {
	int x;
	std::cin>>x;
	std::cin.ignore();
	for (int i = 0; i < x; i++) {
		std::string line;
		std::getline(std::cin, line);
		Date givenDate(std::stoi(line.substr(4,4)), std::stoi(line.substr(0,2)), std::stoi(line.substr(2,2)));
		givenDate.addDay(280);
		std::cout<<i+1<<" "<<givenDate<<" "<<getSign(givenDate)<<std::endl;
	}
  return 0;
}
