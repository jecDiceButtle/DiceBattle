α版用に3D表示のバグを修正
今後はこれを使って作業してください。
現在Gitの対応は未定


メモ：

「3D描画の方法」
①ロード
　メインのOnCreate関数内に3Dオブジェクトのロードを行ってる場所があります。
　通常は
　meshManage->loadMesh("ｵﾌﾞｼﾞｪｸﾄ名", "ﾌｧｲﾙ名", "res/x/(場所)", DX3DMESHMANAGER::MESHTYPE::MESH);
　と記述してください。
　これでロードが出来ました。

②描画
　現在はboadとdiceで3D描画が可能です。
　描画したいクラスのrender()に記述してください。
　通常は
　meshManage->drawAnimMesh(位置(vec3f型), "ｵﾌﾞｼﾞｪｸﾄ名", 角度(vec3f型), ARGB(255, 255, 255, 255), 拡大率(vec3f型));
　と記述してください。
　※render内のDraw_2DClear()とDraw_2DRefresh()の間は2D描画をする場所です。
　　2つの関数の外で描画してください。
　※現在、魔法使いをdice.cppで描画しています。
　　不用意な場合は該当箇所を削除してください。