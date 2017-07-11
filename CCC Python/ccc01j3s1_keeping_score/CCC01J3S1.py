import sys
input = sys.stdin.readline

line = input().strip()
cur = ''
suits = ['Clubs', 'Diamonds', 'Hearts', 'Spades']
hand = {'C': [], 'D': [], 'H': [], 'S': []}
subtotal = {'C': 0, 'D': 0, 'H': 0, 'S': 0}
points = {'A': 4, 'K': 3, 'Q': 2, 'J': 1}
for char in line:
    if char in hand:
        cur = char
    else:
        hand[cur].append(char)
        subtotal[cur] += points.get(char, 0)
print('Cards Dealt\t\t\tPoints')
for suit in suits:
    subtotal[suit[0]] += max(0, 3 - len(hand.get(suit[0])))
    print(suit + ' ' + ' '.join(hand.get(suit[0])) + '\t\t' + str(subtotal.get(suit[0])))
print('Total ' + str(sum(subtotal.values())))
