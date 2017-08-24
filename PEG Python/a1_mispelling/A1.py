for t in range(int(input())):
    line = input()
    x = line.split()[0]
    string = line[len(x) + 1:]
    print(str(t + 1) + ' ' + string[:int(x) - 1] + string[int(x):])
