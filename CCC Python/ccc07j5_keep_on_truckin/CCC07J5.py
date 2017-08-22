import sys
input = sys.stdin.readline

motels = [0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000]
A = int(input())
B = int(input())
N = int(input())
for i in range(N):
    motels.append(int(input()))
motels.sort()
dp = [0] * len(motels)
dp[0] = 1
for i in range(len(motels)):
    for j in range(i + 1, len(motels)):
        if (motels[j] - motels[i] > B):
            break
        if (motels[j] - motels[i] >= A):
            dp[j] += dp[i]
print(dp[len(motels) - 1])
