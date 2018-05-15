#include "GameScene.h"
#include "HelloWorldScene.h"

Scene* GameScene::createScene()
{
	Scene* scene = Scene::create();

	GameScene* layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

void GameScene::DrawGridWindow(const int interval, const Color4F& color)
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

void GameScene::menuCallback(Ref* sender) {

	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = TransitionFade::create(1, HelloWorld::createScene());
	Director::getInstance()->replaceScene(scene);

}

bool GameScene::init(){

	if (!Layer::init())
	{
		return false;
	}

	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	auto menu_item_1 = MenuItemLabel::create(
		Label::createWithTTF("³ª°¡±â", "fonts\\Hogukstd.ttf", 34), CC_CALLBACK_1(GameScene::menuCallback, this));
	auto menu = Menu::create(menu_item_1, NULL);

	menu->setPosition(winsize.width / 10, winsize.height / 9);
	menu->alignItemsVerticallyWithPadding(20);

	this->addChild(menu);

	return true;
}