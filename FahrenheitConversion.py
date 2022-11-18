#importing tkinter to be able to make a GUI
import tkinter
#importing tkinter.messagebox to be able to make pop-up messages from GUI
import tkinter.messagebox

class GUI(): #class GUI
    def __init__(self):
        #window pop up
        self.window = tkinter.Tk() #opening the GUI window
        self.window.title("Fahrenheit Converter") #naming the GUI window
        self.window.geometry('300x180') #shaping the GUI window

        #framing the top and bottom of the GUI window
        self.top_frame = tkinter.Frame(self.window)
        self.bottom_frame = tkinter.Frame(self.window)
        
        def buttonFahrenheit():
            #button for fahrenheit
            bt = tkinter.Button(self.bottom_frame, text = "To Fahrenheit", command = self.math)
            bt.pack(side = 'left') #packing and framing the button to the left horizontally
        buttonFahrenheit()

        
    
        def quitButton():
            #quit button
            quit_bt = tkinter.Button(self.bottom_frame, text = "Quit", command = self.window.destroy)
            quit_bt.pack(side = 'left')
        quitButton()
    
        #packing frames
        self.top_frame.pack()
        self.bottom_frame.pack()

        #entry input
            #putting both the message and the entry box on the top of the frame
        self.message = tkinter.Label(self.top_frame, text = "Enter Temperature: ")
        self.temperature = tkinter.Entry(self.top_frame, width = 5)
        
        #packing entry
        self.message.pack()
        self.temperature.pack()

        #loops the GUI window
        tkinter.mainloop()

        

    def math(self):
            #fahrenheit conversion and message box
            conversion = float(self.temperature.get())
            finalConversion = 9/5*conversion + 32
            tkinter.messagebox.showinfo('Conversion', format(finalConversion, '.1f'))

#creating an instance
my_gui = GUI()
