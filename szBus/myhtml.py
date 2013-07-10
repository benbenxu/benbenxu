from HTMLParser import HTMLParser

class MyHTML(HTMLParser):
    def __init__(self):
        self.title = ''
        self.readingtitle = 0
        HTMLParser.__init__(self)

    def handle_data(self, data):
        if self.readingtitle:
            self.title += data

    def handle_starttag(self, tag, attrs):
        if tag == 'title':
            self.readingtitle = 1

    def handle_endtag(self, tag):
        if tag == 'title':
            self.readingtitle = 0

    def gettitle(self):
        return self.title