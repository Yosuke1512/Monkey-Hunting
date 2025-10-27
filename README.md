# Monkey-Hunting
## 説明
C++とSDL3の練習として、物理学でよく聞く「モンキーハンティング」のシミュレーションを行った。

## 実行例
### コンパイル
``` powershell
g++ -o bin\monkey-hunting src\main.cpp src\simulator.cpp src\object.cpp src\vector.cpp -L lib\SDL3\lib -I lib\SDL3\include -l SDL3
```
### 実行
``` powershell
./bin/monkey-hunting
```
### 衝突する場合
- 衝突する条件 (弾丸の初期速度ベクトルが, 猿の初期位置へ向いている) を満たす.
- 弾丸の初速に関係なく, 猿に命中する.

https://github.com/user-attachments/assets/45854450-1aec-46a8-9491-e7d6647b67fa

### 衝突しない場合
- 衝突する条件を満たさない.

https://github.com/user-attachments/assets/ca46c6f9-5dc8-4803-a70b-ac544ad57a4a

## 参考
- Sanjay Madhav, Game Programming in C++, 吉川邦夫 訳, 今給黎隆 監修, 翔泳社, 2018
