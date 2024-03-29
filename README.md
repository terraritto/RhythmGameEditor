# MusicEditor
![DxLib 2019_08_05 23_55_31](https://user-images.githubusercontent.com/28126083/62473908-b6daee00-b7dc-11e9-8bcd-14084261d470.png)


## Music Editorとは？

個人的に作成しているリズムゲームの譜面を作成するために作ったツールです。  
なので、私が作っている譜面向けになっております。ご了承ください。  
まだ現段階では仮で作っただけです、デバック甘々です。  
なので、なんかエラーが出たぞ～とかあったら教えてもらえるとありがたいです。  
特に基本的にはデータは随時保存するなどして、そのデータを見せてくれると特定がしやすくなります。  

作成に利用したのはDXライブラリです。なのでWindowsじゃないと使えません。

## 操作方法
Up key    上レーンに移行  
Down key  下レーンに移行  
Left key  BPMのレーンを左にずらす  
Right key BPMのレーンを右にずらす  
1 key     Touch Notes に変更,下レーンでのみ可能  
2 key     Long Notes に変更,下レーンでのみ可能  
3 key     Wall Notes(下)に変更,下レーンでのみ可能  
4 key     Wall Notes(上)に変更,上レーンでのみ可能  
5 key     TraceNotesに変更,上レーンでのみ可能  
r key     ColorをRedに変更  
g key     ColorをGreenに変更  
b key     ColorをBlueに変更  
Escape key プログラムを終了

譜面のグリッド   
左クリックすることで配置可能  
TouchNotesは単体  
Long,Wall Notesは二点を選ぶことで配置可能  
TraceNotesはすべてを選んだあと、Alt keyを押しながらクリックで配置可能  
右クリックで削除  

Button  
Start 音楽を読み込んでいる場合、曲を流す  
Stop 音楽が流れているとき、止める  
Load Music 新規で音楽を読み込みたいとき用。  
Musicフォルダに入ってる曲を.wav,.mp3などの拡張子まで指定して入力することで読み込む  
New Save ファイル名を.csvまで指定することでTextフォルダに書き込む  
Save ファイルがある場合、フォルダに書き込む  
FileLoad Textフォルダにあるファイルを.csvまで指定することで読み込む  
BPM 数字で指定する  
LPB 数字で指定する  

## フォルダについて
Musicフォルダに利用したい音楽を入れてください.  　
ここで、音楽ファイルでは.ogg .wavを使うのが好ましいです。  
理由は.mp3では読み込む際にラグが発生することが確認されております。  
何かしら解決法が見つかれば修正いたしますが、それを見つけるまでは許してください

## ダウンロード先
[ダウンロード](https://www.amazon.co.jp/clouddrive/share/SVdQDmULyGnoGjBfcSkNkrlcbCXbsyWqrfzxpfJtJfk)

## version
ver.1.1に変わりました。  
変更点は version.txt につけておいたのでそのファイルを見て確認して頂けるとありがたいです。
