#pragma once
#include <d3dx9.h>
#include <unordered_map>


//textures database of game
class Textures {
	static Textures *instance;
	std::unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	Textures();
	void Add(int id, LPCSTR path, D3DCOLOR transparentColor);
	bool HasContained(int id);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	static Textures *GetInstance();
};