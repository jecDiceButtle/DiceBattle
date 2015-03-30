
//**************************************************************************
//テクスチャ管理クラス
//基本型　：　なし
//派生型　：　なし
//**************************************************************************

#pragma once


#include "dx_texture.h"

//テクスチャ管理クラス
class TextureManager
{
	private:
		//デバイスアドレス
		LPDIRECT3DDEVICE9 dev;

		//登録テクスチャ郡
		vector<DxTexture*> tex_data;
		//登録テクスチャ数
		short tex_val;

	public:
		//コンストラクタ
		TextureManager(LPDIRECT3DDEVICE9 dev);
		//デストラクタ
		~TextureManager();

		//イメージファイルからDxTextureをロード　　（簡易版）
		LPDIRECT3DTEXTURE9 LoadTextureFromFile(char *fName,char *path);
		//イメージファイルからDxTextureをロード　　（詳細版）
		DxTexture* LoadTextureFromFileEx(char *fName,char *path);

	private:
		//イメージファイルからDxTextureをロード　　（簡易版）
		HRESULT LoadTextureFromFile(DxTexture* tex,char *fName,char *path);
		//イメージファイルからDxTextureをロード　　（詳細版）
		HRESULT LoadTextureFromFileEx(DxTexture* tex,char *fName,char *path);

		//テクスチャデータの開放
		void ReleaseTexture(DxTexture *tex);

		//登録済みテクスチャデータのファイル名をチェックし重複ロードを防止する
		DxTexture* CheckFileName(char *fName);
};

