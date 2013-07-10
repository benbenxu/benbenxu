#coding=utf-8

import urllib2
from myhtml import MyHTML
from Tkinter import *

'''
req = urllib2.Request(u'http://www.szjt.gov.cn/apts/APTSLine.aspx?LineGuid=1c237885-c9a5-4d96-a8fe-f8d5f8acf088')

debugf = open('debug.txt', 'w')

strhtml = ''
try:
    fd = urllib2.urlopen(req)
    print fd.geturl()
    for f in fd:
        strhtml += f
except urllib2.URLError, e:
    print u'网页不存在'

print >> debugf, strhtml
html = MyHTML()
html.feed(unicode(strhtml, 'utf-8'))
print html.gettitle().encode('utf-8')

'''

class App:
    def __init__(self, master):
        Label(master, text="First: ").grid(row=0, sticky=W)
        Label(master, text='second:').grid(row=1, sticky=W)

        self.e1 = Entry(master)
        self.e1.grid(row=0, column=1)

        self.e2 = Entry(master)
        self.e2.grid(row=1, column=1)

        self.cb = Checkbutton(master, text='hardcopy')
        self.cb.grid(row=2, columnspan=2)
    def sayHello(self):
        print 'hello'

mainDlg = Tk()
app = App(mainDlg)
mainDlg.mainloop()