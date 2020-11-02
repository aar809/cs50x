from cs50 import get_int
# import cs50

while True:
    H = get_int("Height: ")
    if H > 0 and H <= 8:
        break

# for i in [1,2,3,4,5,6,7,8]:
for i in range(1, H + 1):
    for k in range(H - i):
        print(" ", end="")
    for j in range(i):
        print("#", end="")
    print("  ", end="")
    for j in range(i):
        print("#", end="")
    print("\n", end="")