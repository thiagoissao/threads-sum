import matplotlib.pyplot as plt

threads = [0, 1, 2, 3, 4, 8]
timeSmall = [26, 16, 12, 11, 11, 11]
timeMedium = [54, 40, 24.01, 22, 20, 20.01]
timeLarge = [91, 79, 42, 30, 23, 17]
timeExtraLarge = [205, 190, 97, 67, 51, 28]
timeExtraExtraLarge = [265, 242, 123.01, 84.01, 65.01, 35]

plt.plot(threads, timeSmall, label="small", linestyle='dashed', marker='.')
plt.plot(threads, timeMedium, label="medium", linestyle='dashed', marker='.')
plt.plot(threads, timeLarge, label="large", linestyle='dashed', marker='.')
plt.plot(threads, timeExtraLarge, label="extra-large",
         linestyle='dashed', marker='.')
plt.plot(threads, timeExtraExtraLarge, label="extra-extra-large",
         linestyle='dashed', marker='.')

plt.xlabel('Número de Trabalhadores')
plt.ylabel('Tempo (segundos)')

plt.legend()

plt.show()
