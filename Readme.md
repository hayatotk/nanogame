
# nanogame

最小限のプラットフォーマー用ゲームエンジン。

## ビルド
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

'build'フォルダ内で、cmakeでゲームビルドを実行するには、`cd ..`で移動し、`build/test-Z.Z-XXX_YYY-release-platform`を実行します。

レベルファイルとフォントファイルがリポジトリのルートにあるためです（TODOのようなもの - レベルフォーマットとフォントソースを変更する）。ご不便をおかけして申し訳ございません。

## 依存
SDL, libc

## OSS used
- SDL
- libc
- フォント: Northrup (test.ttf)
