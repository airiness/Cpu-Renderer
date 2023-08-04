### GPU使わずにソフトウエアレンダラー
 * 描画知識を深い理解と練習としてCpuRendererを作っています。
![ss](https://github.com/airiness/Cpu-Renderer/blob/main/ss/ss01.gif)

### 依存ライブラリー
 * [SDL](https://github.com/libsdl-org/SDL)(バッファーをウインドウへ描画)
 * [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)(行列、ベクトル計算)
### 実装したもの
 * 点描画
 * 線描画
 * 重心座標ラスタライズ
 * カメラビューマトリックス計算
 * 透視投影計算
 * デプスバッファ
 * 重心座標色補間
 * 裏面非表示
 * ワイヤーフレーム描画
#### これから実装かもしれないもの
 * テクスチャ
 * c++ shader
 * モデル読み込みと描画
 * Phong-blinn
 * pbr
   ... ...
### 参考資料&ブックマーク
 * [ssloy tinyrenderer](https://github.com/ssloy/tinyrenderer) [wiki](https://github.com/ssloy/tinyrenderer/wiki)
 * [zauonlok renderer](https://github.com/zauonlok/renderer)
 * [Angelo1211 SoftwareRenderer](https://github.com/Angelo1211/SoftwareRenderer) [wiki](https://github.com/Angelo1211/SoftwareRenderer/wiki/Rendering-References)
 * [Games101](https://sites.cs.ucsb.edu/~lingqi/teaching/games101.html)
 * [view matrix](http://www.songho.ca/opengl/gl_camera.html)
 * [barycentric coordinate](https://blackpawn.com/texts/pointinpoly/)
 * [backface culling](https://registry.khronos.org/OpenGL/specs/gl/glspec41.core.pdf)Page168 3.6.1
 * [OpenGL Transform](http://www.songho.ca/opengl/gl_transform.html)
 * [Projection Matrix](http://www.songho.ca/opengl/gl_projectionmatrix.html)
