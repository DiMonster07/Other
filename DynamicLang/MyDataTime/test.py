from datetime import datetime
from mydatatime import *
import unittest

#a = mydatatime(2015, 5, 2, 12, 30, 30, 300)

class Test(unittest.TestCase):
	def setUp(self):
		self.a = 0 
	
	def test_valid_init(self):
		self.a = mydatatime(2015, 5, 2, 12, 30, 35, 300)
		self.assertEqual(2015, self.a.year())
		self.assertEqual(5, self.a.month())
		self.assertEqual(2, self.a.day())
		self.assertEqual(12, self.a.hour())
		self.assertEqual(30, self.a.minute())
		self.assertEqual(35, self.a.second())
		self.assertEqual(300, self.a.microsecond())
	
	def test_is_leap(self):
		self.assertEqual(True, is_leap(2012))
		#self.assertEqual(True, is_leap(2013))

	def test_days_in_month(self):
		self.assertEqual(29, days_in_month(2012, 2))
		#self.assertEqual(29, days_in_month(2013, 2))


if __name__ == "__main__":
	unittest.main()