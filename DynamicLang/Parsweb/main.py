import re, sqlite3
from urllib2 import urlopen
base = sqlite3.connect('aliexpress1.db')
c = base.cursor()
c.execute('''CREATE TABLE ali (name text, price text)''')
r_products = re.compile('<a  class="product ".*?>(.*?)</a>.*?</h3>', re.DOTALL|re.IGNORECASE)
r_price = re.compile('<span class="value" itemprop="price">(.*?)</span>', re.DOTALL|re.IGNORECASE)
for i in range(1, 5):
	page = urlopen('http://www.aliexpress.com/premium/category/100003070/{}.html?site=glo&shipCountry=RU&prNum=163&g=y&needQuery=n&tag='.format(i)).read()
	products = re.findall(r_products, page)
	price = re.findall(r_price, page)
	for x in range(len(products)):
		#print i, x
		c.execute("INSERT INTO ali VALUES ('{}', '{}')".format(products[x], price[x]))
base.commit()
base.close()		