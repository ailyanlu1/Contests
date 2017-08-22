import sys
input = sys.stdin.readline

words = {'CU': 'see you', ':-)': "I'm happy", ':-(': "I'm unhappy", ';-)': 'wink',
         ':-P': 'stick out my tongue', '(~.~)': 'sleepy', 'TA': 'totally awesome',
         'CCC': 'Canadian Computing Competition', 'CUZ': 'because', 'TY': 'thank-you',
         'YW': "you're welcome", 'TTYL': 'talk to you later'}

short = ''
while (short != 'TTYL'):
    short = input().strip()
    print(words.get(short, short))
