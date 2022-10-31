### vtkファイルから節点座標データ，要素の接続情報，要素タイプを抽出するコードです．

### 以下のライブラリに依存しています．
- boost(https://www.boost.org/)

コンパイルにはboostのincludeディレクトリとlibディレクトリをリンクしてください．

### 実行方法
実行ファイルに対照のvtkファイルをコマンドライン引数で与えてください．\
例　実行ファイルがa.outで対象とするvtkファイルがtest.vtkの時
```
./a.out test.vtk
```

### output
- node.dat（節点座標データ）
- element.dat（要素接続情報）
- elementMeshType.dat（要素タイプ）
- test.vtu（読み込んだ形状データのvtuファイル）

### surface process
境界条件を設定したい節点を取り出すことも可能\
境界条件を設定したい領域をply形式で与えてください（377行目のファイルパスを変更してからコンパイルすること）．

### exmpleの実行
```
./実行ファイル　all
```