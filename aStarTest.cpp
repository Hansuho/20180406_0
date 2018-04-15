#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init() 
{
	setTiles();

	_start = _count = 0;

	return S_OK;
}

void aStarTest::setTiles()
{
	//���� Ÿ�� ����
	_startTile = new tile;
	_startTile->init(4, 12);
	_startTile->setAttribute("start");

	//�� Ÿ�� ����
	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");

	_currentTile = _startTile;


	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			//����Ÿ���̸�
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);

				continue;
			}

			//�� Ÿ���̸�
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}

			tile* node = new tile;
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}

}

vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tile* node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			//�����ִ� ���� ����
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//���� Ÿ�� ��� �������ش�
			node->setParentNode(_currentTile);

			//���� ���⺯���� bool�� �༭ üũ�ߴ��� ���� �Ǵ��� �ϱ�����
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�̹� �����ִ� ��� üũ �� �ִ�
				if (*_viOpenList == node)
				{
					//���꿡�� ���ش�
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			//�� �� �ִ� Ÿ���� �� ���¸���Ʈ�� ����ش�
			_vOpenList.push_back(node);
		}
	}

	//���� �ִ� Ÿ���� ���� ���¸���Ʈ ��ȯ
	return _vOpenList;
}


void aStarTest::pathFinder(tile* currentTile)
{
	//�ִ� ��θ� ã������ ������ ��κ��
	float tempTotalCost = 5000;
	tile* tempTile = NULL;

	//���¸���Ʈ ���� ������
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			(abs(_endTile->getIdY() - _vOpenList[i]->getIdY()))) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH ? 14 : 10);

		//F = G + H
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//��� ����� �� ���µ�, ���� ���� ��κ���� �����������
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;

		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);

	}

	//�����ߴ�!
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}

		return;
	}

	//����������, üũ�� �ִܰŸ��� Ŭ����Ϳ� ��´�
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;
	pathFinder(_currentTile);
}


void aStarTest::release()
{

}

void aStarTest::update() 
{


	if (KEYMANAGER->isOnceKeyDown('S'))pathFinder(_currentTile);
		/*
	if (KEYMANAGER->isOnceKeyDown('S')) _start = true;

	if (_start)
	{
		_count++;
		if (_count % 5 == 0)
		{
			pathFinder(_currentTile);

			_count = 0;
		}
	}
	*/

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(230, 140, 200));
				break;
			}
		}
	}
}

void aStarTest::render() 
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
	}
}
