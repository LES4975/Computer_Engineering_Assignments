import pandas as pd
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from sklearn import preprocessing
# import seaborn as sns

# data = pd.read_csv('data_for_clustering.csv')
# data.head()
# data.shape


# #k=2 클러스터 생성
# processed_data = data.copy()

# #화면 생성
# # x=[]
# # y=[]
# # x.append(row[0])
# # y.append(row[1])
# X, y = data
# plt.figure(figsize = (2, 2))
# # plt.show()
# plt.scatter(X[:,0], X[:,1], marker='.')

x1 = [-1, 0, 1, -1, 0, 1]
x2 = [1, 0.5, 1, -0.5, -1, -0.5]

plt.title("K-means clustering")
plt.scatter(x1, x2)
plt.xlabel('x1')
plt.ylabel('x2')
plt.xlim([-2, 2])
plt.ylim([-2, 2])
plt.show()

df = pd.read_csv('data_for_clustering.csv')
df