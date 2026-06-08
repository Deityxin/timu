import matplotlib
import numpy as np
from matplotlib import pyplot as plt

font = {'family' : 'Microsoft YaHei',
        'weight' : 'bold',
        'size'   : '12'}
matplotlib.rc("font",**font)
plt.figure(figsize=(20,8),dpi=80)

np.random.seed(1)

lr = 0.005
epochs = 2000

x = np.arange(-1,1,step=2/100)
noise = np.random.uniform(low=-0.5,high=0.5,size=100)
y = 5 * x + 2 + noise

plt.figure(1)
plt.title("柳鑫 2024301309的线性模型样本分布图")
plt.xlabel("x")
plt.ylabel("y")
plt.scatter(x,y)
plt.show()

def cost(k,b,x,y):
    return np.mean((k*x+b-y)**2)

k = 0
b = 0

for i in range(epochs):
    k_gra = 2*np.mean((k*x+b-y)*x)
    b_gra = 2*np.mean(k*x+b-y)

    k -= k_gra*lr
    b -= b_gra*lr

    if i%10 == 0:
        rcost = cost(k,b,x,y)
        print(f'第{i+1}次结果为：k_gra={k_gra}, b_gra={b_gra}, k={k}, b={b}, loss={rcost}')

        y_pred = k * x + b
        plt.figure(3)
        plt.cla()
        plt.title("柳鑫 2024301309的线性模型样本训练图")
        plt.scatter(x,y)
        plt.plot(x,y_pred,'r-',lw=5)
        plt.pause(0.1)

print(f"最终的结果为：k={k:.4f} | b={b:4f} | 函数表达式：y={k:.4f}*x+{b:.4f} ")