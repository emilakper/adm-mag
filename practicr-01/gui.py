import tkinter as tk
from tkinter import ttk

def add_digit(digit):
    global user_input
    user_input += str(digit)
    label_input.config(text=user_input) 

def reset_input():
    global user_input
    user_input = ""
    label_input.config(text=user_input)

def add_negative():
    global user_input
    if user_input and user_input[0] == '-':
        user_input = user_input[1:]
    else:
        user_input = '-' + user_input
    label_input.config(text=user_input)

def add_comma():
    global user_input
    if '.' not in user_input:
        user_input += "."
        label_input.config(text=user_input)

# General window config
window = tk.Tk()

window.title("Calculator")
window.geometry("550x600+500+100")
window.resizable(False, False)

window.config(background="#000000")
logo = tk.PhotoImage(file='logo.png')
window.iconphoto(False, logo)

# Text about number system input
label_num_system = tk.Label(text="Number system:",
                            background="#000000",
                            foreground="#FFFFFF",
                            font=("Arial", 15)
                            )
label_num_system.grid(row=0, column=0, padx=5, pady=5, columnspan=2)

# Choosing a number system
var = tk.IntVar()
combobox_num_system = ttk.Combobox(window, textvariable=var)
combobox_num_system['values'] = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
combobox_num_system['state'] = 'readonly'
combobox_num_system.config(width=5)
combobox_num_system.grid(row=0, column=2)
combobox_num_system.current(8)
combobox_num_system.config(background="#a19797")

# User's input will be there
label_input = tk.Label(background="#a19797",
                       foreground="#000000",
                       width=40,
                       height= 10,
                       relief=tk.RAISED,
                       bd=20)
label_input.grid(padx=10, pady=15, columnspan=3, rowspan=3)

user_input = ""
label_input.config(text=user_input)

# Operation buttons
add_btn = tk.Button(text="+", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500").grid(row=1, column = 3, padx=7,pady=5, sticky="wens")
sub_btn = tk.Button(text="-", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500").grid(row=1, column = 4, padx=7,pady=5, sticky="wens")
mul_btn = tk.Button(text="*", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500").grid(row=2, column = 3, padx=7,pady=5, sticky="wens")
div_btn = tk.Button(text="/", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500").grid(row=2, column = 4, padx=7,pady=5, sticky="wens")
ans_btn = tk.Button(text="=", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500").grid(row=7, column = 4, columnspan=1, sticky="wens", padx=5,pady=5)


# Number buttons
number_buttons = []
number_buttons.append(tk.Button(text="0", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit(0)))
for i in range(1, 10):
    number_buttons.append(tk.Button(text=str(i), font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda num=i: add_digit(num)).grid(row=4 + (i-1)//3, column=(i - 1)%3, padx=5, pady=10, sticky="we"))
number_buttons[0].grid(row=7, column=0, columnspan=3, padx=5, pady=5, sticky="we")

# Letters buttons
number_buttons.append(tk.Button(text="A", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('A')).grid(row=4, column=3, padx=5, pady=10, sticky="we"))
number_buttons.append(tk.Button(text="B", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('B')).grid(row=4, column=4, padx=5, pady=10, sticky="we"))
number_buttons.append(tk.Button(text="C", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('C')).grid(row=5, column=3, padx=5, pady=10, sticky="we"))
number_buttons.append(tk.Button(text="D", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('D')).grid(row=5, column=4, padx=5, pady=10, sticky="we"))
number_buttons.append(tk.Button(text="E", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('E')).grid(row=6, column=3, padx=5, pady=10, sticky="we"))
number_buttons.append(tk.Button(text="F", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('F')).grid(row=6, column=4, padx=5, pady=10, sticky="we"))

# Reset button
reset_btn = tk.Button(text="clear", font=("Arial", 20, 'bold'), background="#a19797", command=reset_input).grid(row=7, column=3, columnspan=1)

comma_btn = tk.Button(text=",", font=("Arial", 20, 'bold'), background="#FFA500", command=add_comma).grid(row=3, column=3, padx=5, pady=10, sticky="we")
minus_btn = tk.Button(text="±", font=("Arial", 20, 'bold'), background="#FFA500", command=add_negative).grid(row=3, column=4, padx=5, pady=10, sticky="we")

window.mainloop()
