#coding = utf-8
from Tkinter import *
import webbrowser
import config

#界面逻辑
class UI(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
    
        #查询公交线路
        self.btnQueryLine = Button(master, text=u'线路查询', command=self.queryBus)
        self.btnQueryLine.grid(sticky=NE)

    def queryBus(self):
        webbrowser.open_new_tab(cfg.website)
        pass


cfg = config.Config()

ui = UI(Tk())
ui.master.title(u'苏州公交')
ui.master.geometry('500x300')
ui.mainloop()
