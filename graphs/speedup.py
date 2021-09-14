import matplotlib.pyplot as plt

# tempo de execução para arquivos simple.txt, medium.txt, almost-large.txt ,large.txt
serial = [6, 60, 79, 110]
# x1Worker = [7, 61]
# x2Worker = [7, 36]
# x3Worker = [5, 32]
# x4Worker = [5, 30]
# x5Worker = [5, 28]

# sem caso `wait`
x1Worker = [6, 60, 79.01, 111.01]
x2Worker = [4, 33, 41, 57.01]
x3Worker = [3, 27, 28, 39]
x4Worker = [3, 23, 21, 30]
x5Worker = [3, 21, 18, 25]
x6Worker = [3, 19, 16, 21]

ySimple = [
    serial[0] / x1Worker[0],
    serial[0] / x2Worker[0],
    serial[0] / x3Worker[0],
    serial[0] / x4Worker[0],
    serial[0] / x5Worker[0],
    serial[0] / x6Worker[0],
]

yMedium = [
    serial[1] / x1Worker[1],
    serial[1] / x2Worker[1],
    serial[1] / x3Worker[1],
    serial[1] / x4Worker[1],
    serial[1] / x5Worker[1],
    serial[1] / x6Worker[1],
]

yAlmostLarge = [
    serial[2] / x1Worker[2],
    serial[2] / x2Worker[2],
    serial[2] / x3Worker[2],
    serial[2] / x4Worker[2],
    serial[2] / x5Worker[2],
    serial[2] / x6Worker[2],
]

yLarge = [
    serial[3] / x1Worker[3],
    serial[3] / x2Worker[3],
    serial[3] / x3Worker[3],
    serial[3] / x4Worker[3],
    serial[3] / x5Worker[3],
    serial[3] / x6Worker[3],
]


points = [1, 2, 3, 4, 5, 6]
plt.plot(points, points, label="ideal")
plt.plot(points, ySimple, label="simple.txt", linestyle='dashed', marker='.')
plt.plot(points, yMedium, label="medium.txt", linestyle='dashed', marker='.')
plt.plot(points, yAlmostLarge, label="almost-large.txt",
         linestyle='dashed', marker='.')
plt.plot(points, yLarge, label="large.txt", linestyle='dashed', marker='.')


plt.xlabel('Number of Workers')
plt.ylabel('Speedup')

plt.title('Tasks Queue')

plt.legend()

plt.show()
