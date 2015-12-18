from datetime import datetime
import re, unittest

MINYEAR = 1
MAXYEAR = 9999
DAYS_IN_MONTH = [-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def print_time (foo):
    def wrapper(*args, **kwargs): 
    	print "Functions: " + foo.__name__ + "\nCall time -> " + str(datetime.now()) + '\n'
    	return foo(*args, **kwargs)
    return wrapper

def is_leap (year):
	return year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)

def days_in_month (year, month):
	if month == 2 and is_leap(year):
		return 29
	return DAYS_IN_MONTH[month]

def isofromstr(data):
	date = re.findall(r'(\d{4}-\d{2}-\d{2})', data)
	time = re.findall(r'(\d{2}:\d{2}:\d{2}:\d{6})', data)
	date_elem = re.findall(r'(\d{4}|\d{2}|\d{2})', str(date))
	time_elem = re.findall(r'(\d{6}|\d{2})', str(time))
	try:
		y, m, d = list(map(int, date_elem))
		h, mn, s, mcs = list(map(int,time_elem))
		y, m, d = check_data_fields(y, m, d)
		h, mn, s, mcs = check_time_fields(h, mn, s, mcs)
		return mydatatime(y, m, d, h, mn, s, mcs)
	except ValueError as VE:
		print VE
		print "No valid data!" 

def _cmp(x, y):
	return 0 if x == y else 1 if x > y else -1

def check_int_field(value):
	if isinstance(value, int):
		return value
	raise TypeError('integer argument expected, got %s' % type(value).__name__)

def check_data_fields (year, month, day):
	year = check_int_field(year)
	month = check_int_field(month)
	day = check_int_field(day)
	if not MINYEAR <= year <= MAXYEAR:
		raise ValueError('year must be in 1..{}'.format(MAXYEAR), year)
	if not 1 <= month <= 12:
		raise ValueError('month must be in 1..12', month)
	d = days_in_month(year, month)
	if not 1 <= day <= d:
		raise ValueError('day must be in 1..{}'.format(d), day)
	return year, month, day

def check_time_fields (hour, minute, second, microsecond):
	hour = check_int_field(hour)
	minute = check_int_field(minute)
	second = check_int_field(second)
	microsecond = check_int_field(microsecond)
	if not 0 <= hour <= 23:
		raise ValueError('hour must be in 0..23', hour)
	if not 0 <= minute <= 59:
		raise ValueError('minute must be in 0..59', minute)
	if not 0 <= second <= 59:
		raise ValueError('second must be in 0..59', second)
	if not 0 <= microsecond <= 999999:
		raise ValueError('microsecond must be in 0..9999', microsecond)
	return hour, minute, second, microsecond

class mydatatime():
	def __init__(self, year = None, month = None, day = None, hour = None, 
		         minute = None, second = None, microsecond = None):
		year, mounth, day = check_data_fields(year, month, day)
		hour, minute, second, microsecond = check_time_fields(hour, minute, second, microsecond)
		self._year = year
		self._month = month
		self._day = day
		self._hour = hour
		self._minute = minute
		self._second = second
		self._microsecond = microsecond

	@print_time
	def replace(self, year=None, month=None, day=None, hour=None, minute=None, second=None, microsecond=None):
		if year is None:
			year = self._year
		if month is None:
			month = self._month
		if day is None:
			day = self._day
		if hour is None:
			hour = self._hour
		if minute is None:
			minute = self._minute
		if second is None:
			second = self._second
		if microsecond is None:
			microsecond = self._microsecond
		return mydatatime(year, month, day, hour, minute, second, microsecond)
	
	@print_time	
	def _cmp (self, other):
		y, ts, m = self._year, int(self.total_seconds()), (self._microsecond) % 10**6
		y2, ts2, m2 = other._year, int(other.total_seconds()), (other._microsecond) % 10**6
		return _cmp((y, ts, m), (y2, ts2, m2))

	@print_time
	def seconds_in_months(self):
		return (sum(DAYS_IN_MONTH[1: self._month]) + 1) * 86400 if is_leap(self._year) else int(sum(DAYS_IN_MONTH[1: self._month])*86400)

	@print_time	
	def total_seconds(self):	
		return ((self.seconds_in_months() + self._day * 86400 + self._hour * 3600 + self._minute * 60 + self._second) * 10**6 + self._microsecond) / 10**6

	@print_time
	def isoformat(self):
		return "%04d-%02d-%02d %02d:%02d:%02d:%06d" % (self._year, self._month, self._day, self._hour, self._minute, self._second, self._microsecond)

	@print_time
	def year(self):
		return self._year

	@print_time
	def month(self):
		return self._month
	
	@print_time
	def day(self):
		return self._day
	
	@print_time
	def hour(self):
		return self._hour

	@print_time
	def minute(self):	
		return self._minute

	@print_time
	def second(self):
		return self._second
	
	@print_time
	def microsecond(self):
		return self._microsecond

	@print_time
	def __str__(self):
		return self.isoformat()

	@print_time	
	def __lt__(self, other):
		return self._cmp(other) < 0

	@print_time
	def __le__(self, other):
		return self._cmp(other) <= 0		

	@print_time
	def __eq__(self, other):
		return self._cmp(other) == 0

	@print_time
	def __ne__(self, other):
		return self._cmp(other) != 0 

	@print_time
	def __gt__(self, other):
		return self._cmp(other) > 0

	@print_time
	def __ge__(self, other):
		return self._cmp(other) >= 0