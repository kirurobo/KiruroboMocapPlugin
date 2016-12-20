# KiruroboMocapPlugin
A plug-in for Unreal Engine 4 to receive real-time motion from MVN and Perception Neuron.

## ダウンロード
[Releases のページ](https://github.com/kirurobo/KiruroboMocapPlugin/releases) にビルド済のものを置いてあります。  
また、Kinect v2 でリアルタイム送信をするオマケも置いてあります。


---

## 動作例

[![Axis Neuron と MVN Studio からの同時受信](http://img.youtube.com/vi/Y94C3QmGjSY/0.jpg)](https://www.youtube.com/watch?v=Y94C3QmGjSY)  
[Axis Neuron と MVN Studio からの同時受信の例](https://www.youtube.com/watch?v=Y94C3QmGjSY)

[![Percption Neuron](https://v.cdn.vine.co/r/videos/5BA73197D81257013932804706304_40c8f698f87.0.2.7226271563668120992.mp4.jpg)](https://vine.co/v/eUY5z3Zi2VP)  
[Perception Neuron （Axis Neuron） の例](https://vine.co/v/eUY5z3Zi2VP)

[![MVN](https://v.cdn.vine.co/r/videos/782C361BD01240379906626600960_3073401bff2.4.4.10214175785165872773.mp4.jpg)](https://vine.co/v/eHt2K7ZtqDB)  
[MVN (MVN Studio 2.6） の例](https://vine.co/v/eHt2K7ZtqDB)

---

## 変更点

### v.1.1.0

+ UE4.11 以降に対応させました。
+ Axis Neuron Ver. 3.8.42.6503 およびその時点での old header に対応させました。
+ 受信ポートのデフォルトを 7002 にしました。
+ 鏡像モードのチェックボックスが MocapAnimInstance に追加されています。ただし仕様が定まっていないため、チェックしない方が良いです。

### v.1.0.1

+ NaNativeEvaluateAnimation() で TArray を作成することでメモリを大量に消費していた点を修正しました。
+ ガーベジコレクションでデータが削除されてしまっていたのを修正しました。

### v.1.0.0

+ 複数人分受信した際にユーザーIDで区別して動くようにしました。
+ Perception Neuron のユーザーの方がそのうち多くなりそうなので、デフォルトポートを7001としました。
