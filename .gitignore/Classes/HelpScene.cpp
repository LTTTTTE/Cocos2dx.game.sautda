#include "HelpScene.h"
#include "HelloWorldScene.h"

Scene* HelpScene::createScene()
{
	Scene* scene = Scene::create();

	HelpScene* layer = HelpScene::create();

	scene->addChild(layer);

	return scene;
}
void HelpScene::DrawGridWindow(const int interval, const Color4F& color)
{
	const int WIN_WIDTH = Director::getInstance()->getWinSize().width;
	const int WIN_HEIGHT = Director::getInstance()->getWinSize().height;

	DrawNode* node = DrawNode::create();
	for (int i = interval; i < WIN_HEIGHT; i += interval)
		node->drawLine(Vec2(0, i), Vec2(WIN_WIDTH, i), color);
	for (int i = interval; i < WIN_WIDTH; i += interval)
		node->drawLine(Vec2(i, 0), Vec2(i, WIN_HEIGHT), color);

	this->addChild(node);
}

void HelpScene::menuCallback(Ref* sender) {
	Director::getInstance()->popScene();
	
}

bool HelpScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	auto menu_item_1 = MenuItemLabel::create(
		Label::createWithTTF("뒤로가기", "fonts\\Hogukstd.ttf", 34), CC_CALLBACK_1(HelpScene::menuCallback, this));
	auto menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(winsize.width / 9, winsize.height / 8);
	menu->alignItemsVerticallyWithPadding(20);

	this->addChild(menu);

	return true;
}