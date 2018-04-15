#pragma once
#include "tileNode.h"
#include "gameNode.h"

class tankMap : public gameNode
{
private:
	tagTile			_tiles[TILEX * TILEY];
	DWORD			_attribute[TILEX * TILEY];	//�Ӽ� 

	int _pos[2];


public:
	tankMap();
	~tankMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(void);

	virtual void load();

	//Ÿ�Ͽ� ���� ������
	tagTile* getTile() { return _tiles; }

	//Ÿ�� �Ӽ��� ���� ������
	DWORD* getTileAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

