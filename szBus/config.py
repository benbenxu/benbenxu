#coding = utf-8

from xml.dom import minidom

class Config():
    def __init__(self):
        self.website = u''
        self.loadXml()

    #加载配置文件
    def loadXml(self):
        cfgXml = minidom.parse('config.xml')
        self.website = cfgXml.getElementsByTagName('website')[0].getAttribute('ref')


if __name__ == '__main__':
    cfg = Config()
    print cfg.website