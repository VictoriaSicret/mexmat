numbers = [[1, 2], [3, 4]]

def func(x):
    res = [x]*2
    return res


for i in range(len(numbers)):
    for j in range(len(numbers[i])):
        numbers[i][j] = func(5)

print (numbers)
