#define	IS_LEAP_YEAR(year)			((year)%4!=0?0:(year)==2000?1:(year)%100==0?0:1)
#define	REAL_DAYS_IN_YEAR(year)		(DAYS_IN_YEAR + IS_LEAP_YEAR(year))
#define	LAST_DAY_OF_YEAR(year)		(REAL_DAYS_IN_YEAR(year)-1)

int	YearDayToInt						(int Year, int DayOfYear);
void	IntToYearDay						(int year_day, int& Year, int& DayOfYear);

