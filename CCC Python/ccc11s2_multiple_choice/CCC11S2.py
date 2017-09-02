import sys
input = sys.stdin.readline

N = int(input())
student = []
for i in range(N):
    student.append(input().strip())
correct = 0
for i in range(N):
    if student[i] == input().strip():
        correct += 1
print(correct)
