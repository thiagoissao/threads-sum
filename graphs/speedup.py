from matplotlib import lines
import matplotlib.pyplot as plt

# tempo de execução para arquivos simple.txt, medium.txt
serial = [8, 82]
x1Worker = [7, 61]
x2Worker = [7, 36]
x3Worker = [5, 32]
x4Worker = [5, 30]
x5Worker = [5, 28]

ySimple = [
    serial[0] / x1Worker[0],
    serial[0] / x2Worker[0],
    serial[0] / x3Worker[0],
    serial[0] / x4Worker[0],
    serial[0] / x5Worker[0],
]

yMedium = [
    serial[1] / x1Worker[1],
    serial[1] / x2Worker[1],
    serial[1] / x3Worker[1],
    serial[1] / x4Worker[1],
    serial[1] / x5Worker[1],
]


points = [1, 2, 3, 4, 5]
plt.plot(points, points, label="ideal")
plt.plot(points, ySimple, label="simple.txt", linestyle='dashed', marker='.')
plt.plot(points, yMedium, label="medium.txt", linestyle='dashed', marker='.')

plt.xlabel('Number of Workers')
plt.ylabel('Speedup')

plt.title('Tasks Queue')

plt.legend()

plt.show()
