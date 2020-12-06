from cs50 import get_int
from cs50 import get_float
from cs50 import get_string

# Implement a program that determines whether a provided credit card number is valid according to Luhn’s algorithm
# and if valid, also checks whether it is a AMEX, MASTERCARD, or VISA card.
# American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
# 4003600000000014
while True:
    card = get_string("Number: ")
    # if len(card) == 15 or len(card) == 16 or len(card) == 13 or len(card) == 16:
    #   break
    # else:
    #   print("INVALID\n")
    if card.isnumeric():
        break

# card = '4003600000000014'

# print("length:", len(card))
# print(card[-2] + card[-4] + card[-6] + card[-8] + card[-10] + card[-12] + card[-14] + card[-16])
n = len(card)
# n =

step1 = []

for i in range(-2, -n-1, -2):
    #  print(card[i])
    #  print(int(card[i]) * 2)
    x = int(card[i]) * 2
    step1.append(x)

# print(step1)
# [2, 0, 0, 0, 0, 12, 0, 8]

# sum(step1)

step2 = ([str(i) for i in step1])
# print(step2)
# ['2', '0', '0', '0', '0', '12', '0', '8']]

step3 = []
for i in step2:
    for j in range(len(i)):
        step3.append(i[j])
# print(step3)

step4 = [int(i) for i in step3]
step5 = sum(step4)
# print("step5:", step5)

step6 = []

for i in range(-1, -n-1, -2):
    # print(card[i])
    x = int(card[i])
    step6.append(x)

final_sum = sum(step6) + step5
# print(final_sum)

if (final_sum % 10 == 0) == False:
    print("INVALID")
    exit()

# print("LEGIT!")

card = str(card)

# American Express numbers start with 34 or 37
# MasterCard numbers start with 51, 52, 53, 54, or 55
# Visa numbers start with 4
if card[:2] in ("34", "37"):
    print("AMEX")
elif card[:2] in ("51", "52", "53", "54", "55"):
    print("MASTERCARD")
elif card[0] == "4":
    print("VISA")
else:
    print("INVALID")