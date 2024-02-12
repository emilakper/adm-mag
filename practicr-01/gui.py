import tkinter as tk
from tkinter import ttk
import operations as oper

current_system = 10
prev_system = 0
first_num = ""
second_num = ""
current_operation = ''
current_operator_index = -1
second_operation = False # next operator will be second one(we do not want it)
first_comma_counter = 0
second_comma_counter = 0

def add_digit(digit):
    global user_input
    global second_operation
    global comma_btn

    if user_input[-1] in ('+', '-', '*', '/'):
        second_operation = True
        comma_btn.config(state='normal')
    if user_input[0] == '0' and len(user_input) == 1:
        user_input = str(digit)
    else:
        user_input += str(digit)
    label_input.config(text=user_input) 

def add_operation(operation):
    global user_input
    global second_operation
    global first_num
    global second_num
    global current_operation
    global current_operator_index
    if second_operation:
        get_answer()
        user_input += operation
        current_operation = operation
        current_operator_index = len(user_input) - 1

        label_input.config(text=user_input)
    else:
        if (user_input[-1] in ('+', '-', '*', '/')):
            user_input = user_input[0:len(user_input) - 1] + operation
            current_operation = operation
        else:
            first_num = user_input
            user_input += operation
            current_operation = operation
            current_operator_index = len(user_input) - 1
        label_input.config(text=user_input)

    global combobox_num_system
    combobox_num_system.config(state='disabled')

def get_answer():
    global user_input
    global first_num
    global second_num
    global current_system
    global label_input
    global second_operation
    global current_operator_index

    if (current_operator_index != -1):
        second_num = user_input[current_operator_index + 1 : len(user_input)]

        if current_operation == '+':
            user_input = oper.plus(first_num, second_num, current_system)
        elif current_operation == '-':
            user_input = oper.minus(first_num, second_num, current_system)
        elif current_operation == '*':
            user_input = oper.multiply(first_num, second_num, current_system)
        elif current_operation == '/':
            user_input = oper.divide(first_num, second_num, current_system)
        label_input.config(text=user_input)
        second_operation = False
        first_num = user_input
        second_num = ''
        current_operator_index = -1

    global combobox_num_system
    combobox_num_system.config(state='normal')

    global comma_btn
    if (not('.' in user_input)):
        comma_btn.config(state='normal')
def reset_input():
    global user_input
    user_input = "0"
    label_input.config(text=user_input)

    global combobox_num_system
    combobox_num_system.config(state='normal')

    global comma_btn
    comma_btn.config(state='normal')

def add_negative():
    global user_input
    if user_input and user_input[0] == '-':
        user_input = user_input[1:]
    else:
        user_input = '-' + user_input
    label_input.config(text=user_input)

def add_comma():
    global user_input
    global first_comma_counter
    global comma_btn
    if (current_operator_index == -1):
        user_input += "."
        comma_btn.config(state='disabled')
    else:
        user_input += "."
        comma_btn.config(state='disabled')

    label_input.config(text=user_input)

def change_system(*arg):
    global current_system
    global prev_system
    global number_buttons
    prev_system = current_system
    current_system = int(var.get())
    for j in range(16):
        if j < current_system:
            number_buttons[j].config(state="normal")
        else:
            number_buttons[j].config(state="disabled")
    label_input.config(text=oper.transform(label_input.cget("text"), prev_system, current_system))

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

var.trace('w', callback=change_system)

# User's input will be there
label_input = tk.Label(background="#a19797",
                       foreground="#000000",
                       width=17,
                       height=6,
                       relief=tk.RAISED,
                       bd=20,
                       font=('Arial', 20, 'bold'))
label_input.grid(padx=10, pady=15, columnspan=3, rowspan=3)

user_input = "0"
label_input.config(text=user_input)

# Operation buttons
add_btn = tk.Button(text="+", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500", command=lambda: add_operation('+')).grid(row=1, column = 3, padx=7,pady=5, sticky="wens")
sub_btn = tk.Button(text="-", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500", command=lambda: add_operation('-')).grid(row=1, column = 4, padx=7,pady=5, sticky="wens")
mul_btn = tk.Button(text="*", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500", command=lambda: add_operation('*')).grid(row=2, column = 3, padx=7,pady=5, sticky="wens")
div_btn = tk.Button(text="/", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500", command=lambda: add_operation('/')).grid(row=2, column = 4, padx=7,pady=5, sticky="wens")
ans_btn = tk.Button(text="=", font=("Arial", 20, 'bold'), width=4, height=1, background="#FFA500", command=get_answer).grid(row=7, column = 4, columnspan=1, sticky="wens", padx=5,pady=5)


# Number buttons
number_buttons = []
number_buttons.append(tk.Button(text="0", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit(0)))
for i in range(1, 10):
    number_buttons.append(tk.Button(text=str(i), font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda num=i: add_digit(num)))
    number_buttons[len(number_buttons) - 1].grid(row=4 + (i-1)//3, column=(i - 1)%3, padx=5, pady=10, sticky="we")
number_buttons[0].grid(row=7, column=0, columnspan=3, padx=5, pady=5, sticky="we")

# Letters buttons
number_buttons.append(tk.Button(text="A", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('A'), state='disabled'))
number_buttons[10].grid(row=4, column=3, padx=5, pady=10, sticky="we")
number_buttons.append(tk.Button(text="B", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('B'), state='disabled'))
number_buttons[11].grid(row=4, column=4, padx=5, pady=10, sticky="we")
number_buttons.append(tk.Button(text="C", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('C'), state='disabled'))
number_buttons[12].grid(row=5, column=3, padx=5, pady=10, sticky="we")
number_buttons.append(tk.Button(text="D", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('D'), state='disabled'))
number_buttons[13].grid(row=5, column=4, padx=5, pady=10, sticky="we")
number_buttons.append(tk.Button(text="E", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('E'), state='disabled'))
number_buttons[14].grid(row=6, column=3, padx=5, pady=10, sticky="we")
number_buttons.append(tk.Button(text="F", font=("Arial", 20, 'bold'), background="#6b6a6a", command=lambda: add_digit('F'), state='disabled'))
number_buttons[15].grid(row=6, column=4, padx=5, pady=10, sticky="we")
# Reset button
reset_btn = tk.Button(text="clear", font=("Arial", 20, 'bold'), background="#a19797", command=reset_input).grid(row=7, column=3, columnspan=1)

comma_btn = tk.Button(text=",", font=("Arial", 20, 'bold'), background="#FFA500", command=add_comma)
comma_btn.grid(row=3, column=3, padx=5, pady=10, sticky="we")

minus_btn = tk.Button(text="±", font=("Arial", 20, 'bold'), background="#FFA500", command=add_negative).grid(row=3, column=4, padx=5, pady=10, sticky="we")

window.mainloop()
