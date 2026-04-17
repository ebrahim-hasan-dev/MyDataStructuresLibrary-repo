#pragma once

#include <iostream>
#include <string>
#include <vector>


using namespace std;

#pragma warning(disable : 4996)


class clsDate
{
private:

	short _Day = 0;
	short _Month = 0;
	short _Year = 0;

public:

	// constructor :
	clsDate()
	{
		time_t t = time(0);

		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}



	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	_declspec(property(get = GetDay, put = SetDay)) short Day;


	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	_declspec(property(get = GetMonth, put = SetMonth)) short Month;


	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	_declspec(property(get = GetYear, put = SetYear)) short Year;

private:

	void ConvertDateFromStringToDigits(string DateAsString) 
	{

		char sep = ' ';

		for (short i = 0; i < DateAsString.length(); i++)
		{
			if (!isdigit(DateAsString[i]))
			{
				sep = DateAsString[i];
			}
		}

		short pos = 0;

		pos = DateAsString.find(sep);
		_Day = stoi(DateAsString.substr(0, pos));
		DateAsString.erase(0, pos + 1);

		
		pos = DateAsString.find(sep);
		_Month = stoi(DateAsString.substr(0, pos));
		DateAsString.erase(0, pos + 1);
		

		_Year = stoi(DateAsString);
		
	}

public:

	// constructor :
	clsDate(string Date)
	{
		ConvertDateFromStringToDigits(Date);
	}

	// constructor :
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}



	static clsDate GetCurrentDate()
	{
		clsDate CurrentDate;

		time_t t = time(0);

		tm* now = localtime(&t);

		CurrentDate._Day = now->tm_mday;
		CurrentDate._Month = now->tm_mon + 1;
		CurrentDate._Year = now->tm_year + 1900;

		return CurrentDate;

	}

	static bool IsLeapYear(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	bool IsLeapYear()
	{
		return  IsLeapYear(_Year);
	}

	static short NumberOfDayInMonth(short year, short month)
	{
		if (month < 1 || month > 12)
			return 0;

		short arr31Dayes[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return month == 2 ? IsLeapYear(year) ? 29 : 28 : arr31Dayes[month - 1];
	}
	short NumberOfDayInMonth()
	{
		return NumberOfDayInMonth(_Year, _Month);
	}

	void UpdateDateByOrderOfDayInYear(short OrderDayInYear, short year) 
	{

		_Year = year;
		_Month = 1;
		
		short RaminderDays = OrderDayInYear;

		short NumberDayInMonth = 0;

		while (true)
		{
			NumberDayInMonth = NumberOfDayInMonth(_Year, _Month);

			if (RaminderDays < NumberDayInMonth)
			{
				_Day = RaminderDays;
				break;
			}

			RaminderDays -= NumberDayInMonth;
			_Month++;

		}
		
	}


	// constructor :
	clsDate(short OrderOfDayinYear, short Year)
	{
		UpdateDateByOrderOfDayInYear(OrderOfDayinYear, Year);
	}


	static short NumberOfDayInYear(short year) 
	{
		return IsLeapYear(year) ? 366 : 365;
	}
	short NumberOfDayInYear()
	{
		return NumberOfDayInYear(_Year);
	}

	static short NumberOfHoursInYear(short year) 
	{
		return NumberOfDayInYear(year) * 24;
	}
	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short year) 
	{
		return NumberOfHoursInYear(year) * 60;
	}
	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short year)
	{
		return NumberOfMinutesInYear(year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_Year);
	}

	static short NumberOfHoursInMonth(short year, short month)
	{
		return NumberOfDayInMonth(year, month) * 24;
	}
	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInMonth(short year, short month)
	{
		return NumberOfHoursInMonth(year, month) * 60;
	}
	int NumberOfMinutesInMonth() 
	{
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short year, short month) 
	{
		return NumberOfMinutesInMonth(year, month) * 60;
	}
	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short OrderOfDayInWeek(short day, short month, short year)
	{

		short a = (14 - month) / 12;
		short y = year - a;
		short m = month + 12 * a - 2;

		short d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;

		return d;

	}
	short OrderOfDayInWeek()
	{
		return OrderOfDayInWeek(_Day, _Month, _Year);
	}

	static string NameOfDay(short OrderOfDayinWeek)
	{
		string arr[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		
		return arr[OrderOfDayinWeek];

	}
	string NameOfDay()
	{
		return NameOfDay(OrderOfDayInWeek());
	}

	static string NameOfMonth(short month)
	{

		string arrMonth[] = { "Jan", "Feb", "Mar", "Apr", "May",
			"Jun", "Juy", "Aug", "Sep", "Oct", "Nov", "Dec" };


		return arrMonth[month - 1];

	}
	string NameOfMonth()
	{
		return NameOfMonth(_Month);
	}

	static void PrintMonthCalendar(short year, short month) 
	{

		short OrderDayInWeek = OrderOfDayInWeek(1, month, year);

		short NumberOfDayinMon = NumberOfDayInMonth(year, month);

		/*string arrDay[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

		cout << "\n\n --------------------------[" << NameOfMonth(month) << "]------------------------\n\n";

		for (short i = 0; i < 7; i++)
		{
			cout << setw(5) << arrDay[i] << "\t";

		}
		cout << "\n";
		short c = 0;
		for (short d = 0; d < 7; d++)
		{
			if (d == OrderDayInWeek)
			{
				for (short j = 1; j <= NumberOfDayinMon; j++)
				{
					if (c == 7)
					{
						cout << endl;
						c = 0;
					}

					cout << setw(5) << j << "\t";
					c++;
				}
			}
			else
			{
				cout << setw(5) << "" << "\t";
				c++;
			}
		}
		cout << "\n\n -------------------------------------------------------\n";*/


		printf("\n\n --------------------------[%s]------------------------\n\n", NameOfMonth(month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < OrderDayInWeek; i++)
		{
			printf("     ");
		}

		for (short j = 1; j <= NumberOfDayinMon; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		cout << "\n\n -------------------------------------------------------\n\n";
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short year)
	{

		cout << "\n\n-------------------------------------------------------\n\n";
		cout << "\t\tCalendar  -  " << year;
		cout << "\n\n-------------------------------------------------------\n\n";

		for (short month = 1; month <= 12; month++)
		{
			PrintMonthCalendar(year, month);
		}
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short OrderOfDayInYear(short day, short month, short year) {

		short OrderDayInYear = 0;

		for (short m = 1; m < month; m++)
		{
			OrderDayInYear += NumberOfDayInMonth(year, m);
		}

		return OrderDayInYear + day;
	}
	short OrderOfDayInYear()
	{
		return OrderOfDayInYear(_Day, _Month, _Year);
	}

	void UpdateDateAfterAddDays(short DaysToAdding)
	{

		short Rim = DaysToAdding + _Day;

		/*if (Rim > NumberOfDayInMonth(this->_Year, this->_Month))
		{
			Rim -= NumberOfDayInMonth(this->_Year, this->_Month);
			this->_Month++;
		}*/

		while (true)
		{
			if (_Month > 12)
			{
				_Year++;
				_Month = 1;
			}

			if (Rim <= NumberOfDayInMonth(_Year, _Month))
				break;

			Rim -= NumberOfDayInMonth(_Year, _Month);
			_Month++;
		}

		_Day = Rim;

	}

	static bool IsDate1LessThanDate2(clsDate Date1, clsDate Date2)
	{
		
		if (Date1._Year < Date2._Year)
			return true;

		else if (Date1._Year == Date2._Year)
		{

			if (Date1._Month < Date2._Month)
				return true;

			else if (Date1._Month == Date2._Month)
			{

				if (Date1._Day < Date2._Day)
					return true;

			}
		}

		return false;

	}
	bool IsMyDateLessThanDate2(clsDate Date2)
	{
		return IsDate1LessThanDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day;
	}
	bool IsMyDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date._Day == NumberOfDayInMonth(Date._Year, Date._Month);
	}

	public:

	bool IsLastDayInMonth()
		{
			return IsLastDayInMonth(*this);
		}

	static bool IsLastMonthInYear(short month) 
	{
		return month == 12;
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate & Date)
	{
		
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Month))
			{
				Date._Day = 1;
				Date._Month = 1;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
		{
			Date._Day++;
		}

		return Date;
	}

	void IncreaseDateByOneDay()
		{
			IncreaseDateByOneDay(*this);
		}

	static void SwapDate(clsDate& Date1, clsDate& Date2)
	{

		clsDate tmpDate;

		tmpDate = Date1;
		Date1 = Date2;
		Date2 = tmpDate;

	}
	void SwapMyDateWithDate2(clsDate& Date2)
	{
		SwapDate(*this, Date2);
	}

	static int GetDiffrenceBetweenDate1AndDate2_FastAlgorithm(clsDate Date1, clsDate Date2, bool includingEndDay = false)
	{

		if (IsDate1EqualDate2(Date1, Date2))
		{
			return 0;
		}

		short Flag = 1;

		if (!IsDate1LessThanDate2(Date1, Date2))
		{
			SwapDate(Date1, Date2);
			Flag = -1;
		}

		int diffrence = 0;

		if (Date1._Year != Date2._Year)
		{
			short OrderDayInYear_2_AndNumberOfDaysInYears = OrderOfDayInYear(Date2._Day, Date2._Month, Date2._Year);

			for (short i = Date1._Year; i < Date2._Year; i++)
			{
				OrderDayInYear_2_AndNumberOfDaysInYears += NumberOfDayInYear(i);
			}

			diffrence = OrderDayInYear_2_AndNumberOfDaysInYears - OrderOfDayInYear(Date1._Day, Date1._Month, Date1._Year);
		}
		else
		{
			diffrence = OrderOfDayInYear(Date2._Day, Date2._Month, Date2._Year) - OrderOfDayInYear(Date1._Day, Date1._Month, Date1._Year);
		}


		return includingEndDay ? (++diffrence) * Flag : diffrence * Flag;

	}
	int GetDiffrenceBetweenMyDateAndDate2_FastAlgorithm(clsDate Date2, bool includingEndDay = false)
	{
		return GetDiffrenceBetweenDate1AndDate2_FastAlgorithm(*this, Date2, includingEndDay);
	}

	int GetDiffrenceBetweenMyDateAndDate2_SlowAlgorithm(clsDate Date2, bool includingEndDay = false)
	{

		if (IsDate1EqualDate2(*this, Date2))
		{
			return 0;
		}

		int days = 0;
		short SwapFlage = 1;

		if (!IsDate1LessThanDate2(*this, Date2))
		{
			SwapDate(*this, Date2);
			SwapFlage = -1;
		}

		while (IsDate1LessThanDate2(*this, Date2))
		{
			days++;

			*this = IncreaseDateByOneDay(*this);
		}

		return includingEndDay ? (++days) * SwapFlage : days * SwapFlage;
	}


	// Increase Functions :-)


	void IncreaseDateBy_X_Days(short x_Days)
	{

		for (short i = 0; i < x_Days; i++)
		{
			IncreaseDateByOneDay();
		}

	}

	void IncreaseDateByOneWeek() 
	{

		for (short i = 0; i < 7; i++)
		{
			IncreaseDateByOneDay();
		}

	}

	void IncreaseDateBy_X_Week(short X_Week) 
	{

		for (short i = 0; i < X_Week; i++)
		{
			IncreaseDateByOneWeek();
		}

	}

	void IncreaseDateByOneMonth() 
	{

		if (IsLastMonthInYear(_Month))
		{
			_Month = 1;
			_Year++;
		}
		else
		{
			_Month++;
		}

		short NumberDayInMonth = NumberOfDayInMonth(_Year, _Month);

		if (_Day > NumberDayInMonth)
		{
			_Day = NumberDayInMonth;
		}

	}

	void IncreaseDateBy_X_Month(short X_Month) 
	{

		for (short i = 0; i < X_Month; i++)
		{
			IncreaseDateByOneMonth();
		}

	}

	void IncreaseDateByOneYear() 
	{
		_Year++;
	}

	void IncreaseDateBy_X_Year(short X_Year)
	{

		for (short i = 0; i < X_Year; i++)
		{
			IncreaseDateByOneYear();
		}

	}

	void IncreaseDateBy_X_YearFaster(short X_Year) 
	{
		_Year += X_Year;
	}

	void IncreaseDateByOneDecade()
	{
		_Year += 10;
	}
	
	void IncreaseDateBy_X_Decads(short X_Decads) 
	{
		for (short i = 0; i < X_Decads; i++)
		{
			IncreaseDateByOneDecade();
		}

	}

	void IncreaseDateBy_X_DecadsFaster(short X_Decads)
	{
		_Year += (X_Decads * 10);
	}

	void IncreaseDateByOneCentury()
	{
		_Year += 100;
	}
	
	void IncreaseDateByOneMillennium() 
	{
		_Year += 1000;
	}


	// Decrease Functions :-)


	void UpdateDateAfterDecreaseDays(short DaysToDecrease) 
	{

		short Days = DaysToDecrease;

		if (Days >= _Day)
		{
			Days -= _Day;
			_Month--;
		}
		else
		{
			_Day -= Days;
			return;
		}

		while (true)
		{
			if (_Month < 1)
			{
				_Year--;
				_Month = 12;
			}

			if (Days == 0)
			{
				_Day = NumberOfDayInMonth(_Year, _Month);
				return;
			}

			if (Days >= NumberOfDayInMonth(_Year, _Month))
			{
				Days -= NumberOfDayInMonth(_Year, _Month);
				_Month--;
			}
			else
			{
				_Day = NumberOfDayInMonth(_Year, _Month) - Days;
				break;
			}
		}
	}

	void DecreaseDateByOneDay() 
	{

		if (_Day == 1)
		{
			if (_Month == 1)
			{
				_Day = 31;
				_Month = 12;
				_Year--;
			}
			else
			{
				_Month--;
				_Day = NumberOfDayInMonth(_Year, _Month);
			}
		}
		else
		{
			_Day--;
		}

	}

	void DecreaseDateBy_X_Days(short x_Days) 
	{
		for (short i = 0; i < x_Days; i++)
		{
			DecreaseDateByOneDay();
		}
	}

	void DecreaseDateByOneWeek() 
	{
		for (short i = 0; i < 7; i++)
		{
			DecreaseDateByOneDay();
		}
	}

	void DecreaseDateBy_X_Week(short X_Week) 
	{
		for (short i = 0; i < X_Week; i++)
		{
			DecreaseDateByOneWeek();
		}
	}

	void DecreaseDateByOneMonth() 
	{

		if (_Month == 1)
		{
			_Month = 12;
			_Year--;
		}
		else
		{
			_Month--;
		}

		short NumberDayInMonth = NumberOfDayInMonth(_Year, _Month);

		if (_Day > NumberDayInMonth)
		{
			_Day = NumberDayInMonth;
		}

	}

	void DecreaseDateBy_X_Month(short X_Month) 
	{
		for (short i = 0; i < X_Month; i++)
		{
			DecreaseDateByOneMonth();
		}
	}

	void DecreaseDateByOneYear() 
	{
		_Year--;
	}

	void DecreaseDateBy_X_Year(short X_Year) 
	{
		for (short i = 0; i < X_Year; i++)
		{
			DecreaseDateByOneYear();
		}
	}

	void DecreaseDateBy_X_YearFaster(short X_Year) 
	{
		_Year -= X_Year;
	}

	void DecreaseDateByOneDecade()
	{
		_Year -= 10;
	}

	void DecreaseDateBy_X_Decads(short X_Decads)
	{

		for (short i = 0; i < X_Decads; i++)
		{
			DecreaseDateByOneDecade();
		}

	}

	void DecreaseDateBy_X_DecadsFaster(short X_Decads) 
	{
		_Year -= (X_Decads * 10);
	}

	void DecreaseDateByOneCentury()
	{
		_Year -= 100;
	}

	void DecreaseDateByOneMillennium()
	{
		_Year -= 1000;
	}

	bool IsEndOfWeek()
	{
		return OrderOfDayInWeek() == 6;
	}

	bool IsWeekEnd()
	{
		return OrderOfDayInWeek() == 5 || OrderOfDayInWeek() == 6;
	}

	bool IsBusinessDay() 
	{
		return !IsWeekEnd();

		//return OrderOfDayInWeek(Date) != 5 && OrderOfDayInWeek(Date) != 6;

	}

	short DaysUntillTheEndOfWeek() 
	{
		return 6 - OrderOfDayInWeek();
	}

	short DaysUntillTheEndOfMonth() 
	{
		return NumberOfDayInMonth(_Year, _Month) - _Day;
	}

	short DaysUntillTheEndOfYear() 
	{

		short DaysUntillEndOfYear = NumberOfDayInYear(_Year) - OrderOfDayInYear(_Day, _Month, _Year);

		return DaysUntillEndOfYear;
	}

	short GetActucalVacationBetweenMyDataAndDate2(clsDate Date2, bool IncludingEnd = false)
	{

		short ActucalVacation = 0;

		while (IsDate1LessThanDate2(*this, Date2))
		{
			if (IsBusinessDay())
				ActucalVacation++;

			*this = IncreaseDateByOneDay(*this);
		}

		//if (IsBusinessDay(Date2))
			//ActucalVacation++;

		return IncludingEnd ? ++ActucalVacation : ActucalVacation;
	}

	void UpdateDateAfterAddingVacationDays(short VacationDays) 
	{

		// Better Algorithm

		short EqualVacationDays = 0;

		while (EqualVacationDays != VacationDays)
		{
			if (IsBusinessDay())
			{
				EqualVacationDays++;
			}

			*this = IncreaseDateByOneDay(*this);
		}

		while (IsWeekEnd())
		{
			*this = IncreaseDateByOneDay(*this);
		}

	}

	void UpdateDateAfterAddingVacationDays_2(short VacationDays)
	{

		short WeekEndDays = 0;

		for (short i = 0; i < VacationDays + WeekEndDays; i++)
		{
			if (IsWeekEnd())
			{
				WeekEndDays++;
			}

			IncreaseDateByOneDay();
		}

		while (IsWeekEnd())
		{
			 IncreaseDateByOneDay();
		}

	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) 
	{
		return !IsDate1LessThanDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}
	bool  IsMyDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}


	enum Results { Before = -1, Equal = 0, After = 1 };


	static Results CompareDates(clsDate Date1, clsDate Date2)
	{

		if (IsDate1AfterDate2(Date1, Date2))
		{
			return Results::After;
		}
		else if (IsDate1LessThanDate2(Date1, Date2))
		{
			return Results::Before;
		}

		return Results::Equal;

	}
	Results CompareBtweenMyDateAndDate2(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	bool IsValide()
	{

		if (_Month >= 1 && _Month <= 12)
		{
			if (_Day >= 1 && _Day <= NumberOfDayInMonth(_Year, _Month))
			{
				return true;
			}
		}

		return false;

	}

	static int CalculateAgeInDays(clsDate DateOfBirth)
	{
		return 	GetDiffrenceBetweenDate1AndDate2_FastAlgorithm(DateOfBirth, GetCurrentDate(), true);
	}

	static string ConvertDateToString(clsDate Date)
	{
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}

	static clsDate ConvertDateFromStringToclsDate(string DateAsString) {

		clsDate Date;

		short tmp = 0;

		vector <short> vec;

		for (short i = 0; i < DateAsString.length(); i++)
		{
			if (isdigit(DateAsString[i]))
			{
				tmp = tmp * 10 + (DateAsString[i] - 48);
			}
			else
			{
				if (tmp > 0)
				{
					vec.push_back(tmp);
					tmp = 0;
				}
			}
		}

		if (vec.size() < 3)
		{
			vec.push_back(tmp);
		}

		if (vec.size() == 3)
		{
			Date._Day = vec.at(0);
			Date._Month = vec.at(1);
			Date._Year = vec.at(2);
		}

		return Date;
	}

	static string FormateDate(clsDate Date, string Fotmate = "dd/mm/yyyy") 
	{
		
		short pos = 0;
		
		pos = Fotmate.find("dd");
		Fotmate.replace(pos, 2, to_string(Date._Day));
		
		pos = Fotmate.find("mm");
		Fotmate.replace(pos, 2, to_string(Date._Month));
		
		pos = Fotmate.find("yyyy");
		Fotmate.replace(pos, 4, to_string(Date._Year));
		
		return Fotmate;
		
		
				/*string StrDate = "";
		
				for (short i = 0; i < Fotmate.length(); i++)
				{
					if (Fotmate[i] == 'd')
					{
						StrDate += to_string(Date.d);
						i++;
					}
					else if (Fotmate[i] == 'm')
					{
						StrDate += to_string(Date.m);
						i++;
					}
					else if (Fotmate[i] == 'y')
					{
						StrDate += to_string(Date.y);
						i += 3;
					}
					else
					{
						StrDate += Fotmate[i];
					}
				}
		
				return StrDate;*/

	}

	void PrintDate()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	static string GetCurrentTimeAsString()
	{
		time_t t = time(0);

		tm* now = localtime(&t);

		short h = now->tm_hour;

		string MorningOrEvening = "";

		if (h < 12)
		{
			h = h == 0 ? 12 : h;
			MorningOrEvening = " AM";
		}
		else
		{
			h = h > 12 ? h -= 12 : h;

			MorningOrEvening = " PM";
		}

		return to_string(h) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec) + MorningOrEvening;
	}

	static string GetCurrentDateAsString()
	{
		clsDate CurrentDate = GetCurrentDate();
		
		return to_string(CurrentDate._Day) + "/" + to_string(CurrentDate._Month) + "/" + to_string(CurrentDate._Year);
	}


};



