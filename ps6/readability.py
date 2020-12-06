from cs50 import get_int
from cs50 import get_float
from cs50 import get_string

# The Coleman-Liau index assesses the readability grade level in the US of a text passage using the below algorithm.
    # L is the average number of letters per 100 words in the text
    # S is the average number of sentences per 100 words in the text
    # index = 0.0588 * L - 0.296 * S - 15.8

text = get_string("Text: ")

words = 1
letters = 0
sentences = 0

for i in text:
    if str.isalpha(i):
        letters += 1

for i in text:
    if i == " ":
        words += 1

for i in text:
    if i in (".", "!", "?"):
        sentences += 1

# print(letters)
# print(words)
# print(sentences)

L = letters / words * 100
S = sentences / words * 100

index = 0.0588 * L - 0.296 * S - 15.8
index = round(index)

if index >= 16:
    print("Grade 16+")
elif index <= 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")

# Expected Outputs:
    # Grade X
    # Before Grade 1
    # Grade 16+