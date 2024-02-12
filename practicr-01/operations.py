from math import *

digits = {'0' : 0, '1' : 1, '2' : 2, '3' : 3, '4' : 4, '5' : 5, '6' : 6, '7' : 7,
          '8' : 8, '9' : 9, 'A' : 10, 'B' : 11, 'C' : 12, 'D' : 13, 'E' : 14, 'F' : 15}
rdigits = {0 : '0', 1 : '1', 2 : '2', 3 : '3', 4 : '4', 5 : '5', 6 : '6', 7 : '7',
           8 : '8', 9 : '9', 10 : 'A', 11 :'B', 12 : 'C', 13 : 'D', 14 : 'E', 15 : 'F'}

def to_decimal(number, ss):
    pos = number.find('.') 
    power = 0
    if pos == -1:
        power = len(number) - 1
    else:
        power = pos - 1
    decimal = 0
    for digit in number:
        if digit != '.':
            decimal += digits[digit] * (ss ** power)
            power -= 1
    return decimal

def from_decimal(decimal, ss):
    negative = False
    if decimal < 0:
        negative = True
        decimal = -decimal
    power = 0
    while ss ** power < decimal:
        power += 1
    number = ""
    while decimal > 0.000000001 or power >= 0:
        digit = floor(decimal / ss ** power)
        number = number + rdigits[digit]
        if power == 0:
            number = number + '.'
        decimal -= digit * ss ** power
        power -= 1
    if number[-1] == '.':
        number = number[:-1]
    if number == "0":
        return number
    if number[0] == '0' and number[1] != '.':
        number = number[1:]
    if negative:
        number = negate(number)
    return number

def transform(number, ss_from, ss_to):
    decimal = to_decimal(number, ss_from)
    return from_decimal(decimal, ss_to)

def is_neative(number):
    if number[0] == '-':
        return True
    return False

def negate(number):
    if number[0] == '-':
        number = number[1:]
    else:
        number = '-' + number
    return number

def modulo(number):
    if is_neative(number):
        return negate(number)
    return number

def plus(number1, number2, ss):
    if is_neative(number1) and is_neative(number2):
        return negate(from_decimal(to_decimal(negate(number1), ss) + to_decimal(negate(number2), ss), ss))
    elif is_neative(number1):
        return from_decimal(to_decimal(number2, ss) - to_decimal(negate(number1), ss), ss)
    elif is_neative(number2):
        return from_decimal(to_decimal(number1, ss) - to_decimal(negate(number2), ss), ss)
    return from_decimal(to_decimal(number1, ss) + to_decimal(number2, ss), ss)

def minus(number1, number2, ss):
    if is_neative(number1) and is_neative(number2):
        return from_decimal(to_decimal(negate(number2), ss) - to_decimal(negate(number1), ss), ss)
    elif is_neative(number1):
        return negate(from_decimal(to_decimal(negate(number1), ss) + to_decimal(number2, ss), ss))
    elif is_neative(number2):
        return from_decimal(to_decimal(number1, ss) + to_decimal(negate(number2), ss), ss)
    return from_decimal(to_decimal(number1, ss) - to_decimal(number2, ss), ss)

def multiply(number1, number2, ss):
    if is_neative(number1) and is_neative(number2):
        return from_decimal(to_decimal(negate(number1), ss) * to_decimal(negate(number2), ss), ss)
    elif is_neative(number1):
        return negate(from_decimal(to_decimal(negate(number1), ss) * to_decimal(number2, ss), ss))
    elif is_neative(number2):
        return negate(from_decimal(to_decimal(number1, ss) * to_decimal(negate(number2), ss), ss))
    return from_decimal(to_decimal(number1, ss) * to_decimal(number2, ss), ss)

def divide(number1, number2, ss):
    if to_decimal(modulo(number2), ss) == 0:
        return "Error"
    if is_neative(number1) and is_neative(number2):
        return from_decimal(to_decimal(negate(number1), ss) / to_decimal(negate(number2), ss), ss)
    elif is_neative(number1):
        return negate(from_decimal(to_decimal(negate(number1), ss) / to_decimal(number2, ss), ss))
    elif is_neative(number2):
        return negate(from_decimal(to_decimal(number1, ss) / to_decimal(negate(number2), ss), ss))
    return from_decimal(to_decimal(number1, ss) / to_decimal(number2, ss), ss)
