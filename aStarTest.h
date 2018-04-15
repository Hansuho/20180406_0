#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

//Ÿ�� ������
#define TILEWIDTH 32
#define TILEHEIGHT 32

//Ÿ���� ����
#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class aStarTest : public gameNode
{
private:
	//��ü Ÿ�� ���� ����
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� Ÿ���� ���� ����
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//�ִ� �Ÿ��� ����ִ� ����
	vector<tile*>			_vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//����Ÿ��
	tile* _endTile;			//����Ÿ��
	tile* _currentTile;		//����Ÿ��

	bool _start;
	int _count;
	
public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	void setTiles();
	vector<tile*> addOpenList(tile* currentTile);

	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();

};

