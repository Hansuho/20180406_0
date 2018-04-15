#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);
	
	//���߰�
	SCENEMANAGER->addScene("��ũ��", new aStarScene);
	SCENEMANAGER->changeScene("��ũ��");

	int test = 1;

	return S_OK;
}

void playGround::release()
{
	gameNode::release();

}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	
}

void playGround::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================================
	
	SCENEMANAGER->render();
	
	//==================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
