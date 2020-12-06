from cs50 import get_int
from cs50 import get_float
from cs50 import get_string

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

change = 100 * change
Q = int(change / 25)
# print(Q)
# print(int(Q))
D = int((change - (Q * 25))/10)
N = int((change - (Q * 25) - (D * 10))/5)
P = int((change - (Q * 25) - (D * 10) - (N * 5)))

print(Q+D+N+P)
# print(f"{change}")
