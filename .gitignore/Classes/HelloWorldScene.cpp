#include "HelloWorldScene.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "HelpScene.h"


Scene* HelloWorld::createScene()
{
	Scene* scene = Scene::create();

	HelloWorld* layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

void HelloWorld::DrawGridWindow(const int interval, const Color4F& color)
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

void HelloWorld::menuCallback(Ref* sender) {

	auto temp = (MenuItem*)sender;

	switch (temp->getTag()) {

	case static_cast<int>(TAG::tag_play) : {

		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
		break;
	}
	case static_cast<int>(TAG::tag_Option) : {

		auto scene = TransitionFade::create(1, OptionScene::createScene());
		Director::getInstance()->pushScene(scene);
		break;
	}
	case static_cast<int>(TAG::tag_Help) : {

		auto scene = TransitionFade::create(1, HelpScene::createScene());
		Director::getInstance()->pushScene(scene);
		break;
	}
	case static_cast<int>(TAG::tag_Quit) : {
		Director::getInstance()->end();
	}
	default:break;

	}

}

void HelloWorld::schelduleCallback(float d) {

	CCLOG("%.3f", d);

	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(-100, 100);
	std::uniform_int_distribution<__int64>num2(0, 100);
	std::uniform_int_distribution<__int64>num3(1, 4);
	auto spr_sakura_1 = Sprite::create(StringUtils::format("sakura_%d.png", num3(rng)));
	spr_sakura_1->setPosition(num2(rng) * 15, 750 + num2(rng) * 2);
	spr_sakura_1->setScale(0.08);
	this->addChild(spr_sakura_1);

	ccBezierConfig bez1;
	bez1.controlPoint_1 = Point(num2(rng) * 19 - 200, num2(rng) + 600);
	bez1.controlPoint_2 = Point(num2(rng) * 19 - 200, num2(rng) + 300);
	bez1.endPosition = Point(num2(rng) * 19 - 200, -100);
	auto act_flow = BezierTo::create(16, bez1);
	auto act_rotate = RotateBy::create(5, 90);
	auto act_flow_rotate = Spawn::create(act_flow, act_rotate, NULL);
	auto act_flow_rep = RepeatForever::create(act_flow_rotate);

	spr_sakura_1->runAction(act_flow_rep);
}


void HelloWorld::update(float dt) {

	

}


bool HelloWorld::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

//	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	auto spr_Background = Sprite::create("sutdaBackground.png");
	spr_Background->setPosition(winsize.width / 2, winsize.height / 2);
	this->addChild(spr_Background,-100);

	auto label_1 = Label::createWithTTF("게임시작", "fonts\\Hogukstd.ttf", 34); label_1->enableOutline(Color4B::BLACK, 2);
	auto label_2 = Label::createWithTTF("옵션",     "fonts\\Hogukstd.ttf", 34); label_2->enableOutline(Color4B::BLACK, 2);
	auto label_3 = Label::createWithTTF("도움말",   "fonts\\Hogukstd.ttf", 34); label_3->enableOutline(Color4B::BLACK, 2);
	auto label_4 = Label::createWithTTF("종료",     "fonts\\Hogukstd.ttf", 34); label_4->enableOutline(Color4B::BLACK, 2);

	auto menu_item_1 = MenuItemLabel::create(
		label_1, CC_CALLBACK_1(HelloWorld::menuCallback, this));	menu_item_1->setTag(static_cast<int>(TAG::tag_play));
	auto menu_item_2 = MenuItemLabel::create(
		label_2, CC_CALLBACK_1(HelloWorld::menuCallback, this));	menu_item_2->setTag(static_cast<int>(TAG::tag_Option));
	auto menu_item_3 = MenuItemLabel::create(
		label_3, CC_CALLBACK_1(HelloWorld::menuCallback, this));	menu_item_3->setTag(static_cast<int>(TAG::tag_Help));
	auto menu_item_4 = MenuItemLabel::create(
		label_4, CC_CALLBACK_1(HelloWorld::menuCallback, this));	menu_item_4->setTag(static_cast<int>(TAG::tag_Quit));

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(winsize.width - winsize.width / 7, winsize.height / 5);

	this->addChild(menu);


	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(-100, 100);
	std::uniform_int_distribution<__int64>num2(0, 100);
	std::uniform_int_distribution<__int64>num3(1, 4);
	auto spr_sakura_1 = Sprite::create(StringUtils::format("sakura_%d.png",num3(rng)));
	spr_sakura_1->setPosition(num2(rng)*15, winsize.height - winsize.height / 6);
	spr_sakura_1->setScale(0.08);
	this->addChild(spr_sakura_1);

	ccBezierConfig bez1;
	bez1.controlPoint_1 = Point(num(rng), -num2(rng));
	bez1.controlPoint_2 = Point(num(rng), -num2(rng) + -num2(rng));
	bez1.endPosition = Point(num(rng), -num2(rng) + -num2(rng) + -num2(rng));
	auto act_flow = BezierBy::create(4, bez1);
	auto act_rotate = RotateBy::create(5, 90);
	auto act_flow_rotate = Spawn::create(act_flow, act_rotate, NULL);
	auto act_flow_rep = RepeatForever::create(act_flow_rotate);

	spr_sakura_1->runAction(act_flow_rep);

	//this->schedule(schedule_selector(HelloWorld::schelduleCallback),1.0);
	this->schedule(schedule_selector(HelloWorld::schelduleCallback),1);
	return true;
}
