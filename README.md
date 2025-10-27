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


## 参考
- Sanjay Madhav, Game Programming in C++, 吉川邦夫 訳, 今給黎隆 監修, 翔泳社, 2018
