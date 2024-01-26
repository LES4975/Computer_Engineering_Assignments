from sklearn.preprocessing import MinMaxScaler
import pandas as pd


DF = pd.read_csv('과제1.csv')
print("원본 데이터프레임▼ ")
print(DF)
df = pd.DataFrame(DF)
# 데이터 처리를 위하여 문자열로 이루어진 컬럼 제거
df_NoVars = df.drop(['Wheat Varieties'], axis=1)
# print(df_NoVars)
df_NoVars['X1 kernel_area'] = df['X1 kernel_area'].astype(float)
df_NoVars['X2 kernel_length'] = df['X2 kernel_length'].astype(float)


# -----------------------------------
# MinMaxScaler : 특징값 스케일링으로 정규화
scaler = MinMaxScaler()
scaler.fit(df_NoVars)
scaled_df = pd.DataFrame(scaler.transform(df_NoVars), columns=df_NoVars.columns)

df_OnlyVars = df.drop(['X1 kernel_area', 'X2 kernel_length'], axis=1)

print("\n\n특징값 스케일링으로 정규화 ▼ ")
print(pd.concat([scaled_df, df_OnlyVars], axis=1))