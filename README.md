# B-V_SCAN
磁場-電圧特性(B-V特性)のデータファイルから 「+ → -」磁場掃引データと「- → +」磁場掃引データを分け，その分けた地点のデータをtxtファイルと
csvファイルで出力する（複数データ入力可能）

※なおソースファイルはC言語になります。

### ちなみに 
UWSCというソフトを併用して使えるようにしているため，B-V_SCANによってできた「CSV_BV.csv」を使うことで
「B-V_autop32.UWS」をUWSCで実行させれば自動で.pl3形式のグラフデータを書き出してくれる。  
（ただし，線色は設定できないため人力で設定が必要）  

#### ソースファイルで欲しい方へ  
「B-V_SCAN.c」というファイルを選んで適宜ダウンロードやコピーなどを行ってください    

#### よくわからないという方へ  
Windows上で動くexe形式のアプリケーションを作成しましたので，もし欲しい方はお声がけください。  
Twitter:@oukamirry

#### 動作確認用にdataファイルが欲しい方へ
オンライン上にアップロードをしないことを厳守できるのであれば，いくつかデータをお渡しします。
Twitter:@oukamirry

## 使い方を以下に記述

-------------------------------------------------
このプログラムはVisual Studio 2017で開発されたものです。  
### 手順  
1. 「dats」フォルダに所望のdataファイル群を入れる(datsフォルダと実行ファイルは同じディレクトリになることを想定)  
2. exeファイルまたは実行ファイルを起動する  
3. 各種パラメータを設定する  
4. 続けて実行する場合は1.または2.から始めても良いが  
　 最終的に書き出される「.data」形式のデータやcsvファイルは上書きされるようになっているので，  
　 新しく書き出したいときは削除するか名前を変えること  


### 仕様  
・パラメータ設定の仕方  
例：「Ryo.05-35_1-2_B-V_0.2mA.dat」「Ryo.05-35_1-2_B-V_0.3mA.dat」をdatsフォルダに入れている場合  

#### 実行画面にて
ファイル先頭部の共通名部分を入力してください(First name):Ryo.05-35_1-2_B-V_

ファイル後半部の数値部分を入力してください(Last name)  ※ .dat は含まない　例:0.35mA
※単位込み 0.35mA_R なども可, 最大10個まで(間は空白をあけて，10個未満の時は代わりに 0 を入力してください)  
0.2mA 0.3mA 0 0 0 0 0 0 0 0

### 注意  
・出力結果からグラフを作成してもきれいに見えない時は人力で修正すること　　
・実行結果をすぐ消さずに見たい場合は「コマンドプロンプト」で起動する  

-------------------------------------------------
