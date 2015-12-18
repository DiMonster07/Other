from datetime import datetime
from mydatatime import *
import unittest


class Test_Init(unittest.TestCase):
	def setUp(self):
		self.a = mydatatime(2015, 5, 2, 12, 30, 35, 300)
	def test_1 (self):
		self.assertEqual(2015, self.a.year())
		self.assertEqual(5, self.a.month())
		self.assertEqual(2, self.a.day())
		self.assertEqual(12, self.a.hour())
		self.assertEqual(30, self.a.minute())
		self.assertEqual(35, self.a.second())
		self.assertEqual(300, self.a.microsecond())

class Test_is_leap(unittest.TestCase):		
	def test_1(self):
		self.assertEqual(True, is_leap(2012))
	def test_2(self):
		self.assertEqual(True, is_leap(2013)) 


class Test_days_in_month(unittest.TestCase):
	def test_1(self):
		self.assertEqual(29, days_in_month(2012, 2))
	def test_2(self):
		self.assertEqual(29, days_in_month(2013, 2))

class Test_cmp(unittest.TestCase):
	def test_1(self):
		self.assertEqual(1, _cmp(3, 2))
	def test_2(self):
		self.assertEqual(-1, _cmp(1, 2))
	def test_3(self):
		self.assertEqual(0, _cmp(2, 2))

class Test_check_int_field(unittest.TestCase):
	def test_1(self):
		self.assertEqual(4, check_int_field(4))
	def test_2(self):
		self.assertEqual(TypeError, check_int_field(4.455))

class Test_check_data_fields(unittest.TestCase):
	def test_1(self):
		self.assertEqual((4, 4, 4), check_data_fields(4, 4, 4))
	def test_2(self):
		self.assertEqual(ValueError, check_data_fields(99999, 4, 4))
	def test_3(self):
		self.assertEqual(ValueError, check_data_fields("99999", 4, 4))
	def test_4(self):
		self.assertEqual(ValueError, check_data_fields(99999, 15, 60))
	def test_5(self):
		self.assertEqual(ValueError, check_data_fields(34, 30, 4))
	def test_6(self):
		self.assertEqual(ValueError, check_data_fields(34, 4, 80))

class Test_check_time_fields(unittest.TestCase):
	def test_1(self):
		self.assertEqual((12, 10, 4, 56748), check_time_fields(12, 10, 4, 56748))
	def test_2(self):
		self.assertEqual(ValueError, check_time_fields(26, 10, 4, 56748))
	def test_3(self):
		self.assertEqual(ValueError, check_time_fields("99999", 462, 3241, 999999999))
	def test_4(self):
		self.assertEqual(ValueError, check_time_fields(12, 462, 3241, 999999999))
	def test_5(self):
		self.assertEqual(ValueError, check_time_fields(12, 10, 3241, 999999999))
	def test_6(self):
		self.assertEqual(ValueError, check_time_fields(12, 10, 5, 999999999))

class Test_replace(unittest.TestCase):
	def setUp(self):
		self.a = mydatatime(2015, 5, 2, 12, 30, 35, 300)
		self.b = mydatatime(2015, 5, 2, 12, 30, 35, 300)
	def test_1(self):
		self.assertEqual(self.a, self.b.replace())
	def test_2(self):
		self.assertEqual(self.a.replace(day = 5), self.b.replace(day = 5))

class Test_cmp_classmethod(unittest.TestCase):
	def setUp(self):
		self.a = mydatatime(2015, 5, 2, 12, 30, 35, 300)
		self.b = mydatatime(2015, 5, 2, 12, 30, 36, 600)
	def test_1(self):
		self.assertEqual(-1, self.a._cmp(self.b))
	def test_2(self):
		self.assertEqual(0, self.a._cmp(self.b.replace(2015, 5, 2, 12, 30, 35, 300)))
	def test_3(self):
		self.assertEqual(0, self.a._cmp(self.b.replace(2013, 4, 2, 12, 30, 35, 300)))

class Test_second_in_month(unittest.TestCase):
	def setUp(self):
		self.a = mydatatime(2013, 4, 2, 12, 30, 35, 300)
	def test_1(self):
		self.assertEqual(int(sum(DAYS_IN_MONTH[1: 4]))*86400, self.a.seconds_in_months())
	def test_2(self):
		self.assertEqual(int(sum(DAYS_IN_MONTH[1: 2]))*86400, (self.a.replace(2013, 2, 2, 12, 30, 35, 300)).seconds_in_months())
	def test_3(self):
		self.assertEqual((int(sum(DAYS_IN_MONTH[1: 2])) + 1)*86400, self.a.replace(2012, 2, 2, 12, 30, 35, 300).seconds_in_months())

class Test_isorofmat_str(unittest.TestCase):
	def test_1(self):
		self.assertEqual("2012-02-02 12:30:35:000300", mydatatime(2012, 2, 2, 12, 30, 35, 300).isoformat())
	def test_2(self):
		self.assertEqual("2012-02-02 12:30:35:000300", str(mydatatime(2012, 2, 2, 12, 30, 35, 300)))

class Test_compairson(unittest.TestCase):
	def setUp(self):
		self.a = mydatatime(2012, 2, 2, 12, 30, 35, 300)
		self.b = mydatatime(2015, 12, 19, 11, 30, 35, 333)
		self.c = mydatatime(2015, 12, 19, 11, 30, 35, 333)
	def test_1(self):
		self.assertEqual(True, self.a < self.b)
	def test_2(self):
		self.assertEqual(True, self.a <= self.b)
	def test_3(self):
		self.assertEqual(True, self.b == self.c)
	def test_4(self):
		self.assertEqual(True, self.a != self.b)
	def test_5(self):
		self.assertEqual(True, self.b > self.a)
	def test_6(self):
		self.assertEqual(True, self.b >= self.c)

class test_isofromstr(unittest.TestCase):
	def setUp(self):
		self.a = mydatatime(2012, 2, 2, 12, 30, 35, 300)
	def test_1(self):
		self.assertEqual(self.a, isofromstr("2012-02-02 12:30:35:000300"))
	def test_2(self):
		self.assertEqual(self.a, isofromstr("2012-02-02 12:30:35:000333"))
	def test_3(self):
		self.assertEqual(self.a, isofromstr("2012-20-02 12:30:35:000300"))
	


if __name__ == '__main__':
    unittest.main()