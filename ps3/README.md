# Problem Set 3:

## Plurality
### Instructions:
Implement a program that runs a "plurality" election, so that when user inputs # of voters, and candidate name of each vote, the output will be the winner based on inputs.

### Usage

```
$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice
```

<b> Full instructions <a href='https://cs50.harvard.edu/x/2020/psets/3/plurality/'> here </a>.</b>


## Runoff

### Instructions
Implement a program that runs a runoff election, per the below. 

While a "Plurality" election simply takes into account the voted candidate from each voter, 
and outputs the candidate with the most votes, a "Runoff" election allows voters to rank each candidate, which will thus require some additional logic
in the program to determine the winner.

### Usage

```
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```

<b> Full instructions <a href='https://cs50.harvard.edu/x/2020/psets/3/runoff/'> here </a>.</b>

 
