import sys
input = sys.stdin.readline

vowels = 'aeiou'
word = input().strip()
newWord = []
for ch in word:
    newWord.append(ch)
    if ch not in vowels:
        i = ord(ch)
        while i > ord('a') and chr(i) not in vowels:
            i -= 1
        j = ord(ch)
        while j < ord('z') and chr(j) not in vowels:
            j += 1
        if j == ord('z') or ord(ch) - i <= j - ord(ch):
            newWord.append(chr(i))
        else:
            newWord.append(chr(j))
        k = ord(ch)
        if k != ord('z'):
            k += 1
            while k < ord('z') and chr(k) in vowels:
                k += 1
        newWord.append(chr(k))
print(''.join(newWord))
