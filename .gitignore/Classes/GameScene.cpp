#include "GameScene.h"
#include "HelloWorldScene.h"

User* User::user_1 = nullptr;
int arr_card[21] = { 0 };

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

	auto item = (MenuItem*)sender;

	switch (item->getTag()) {

	case static_cast<int>(TAG_MENU::tag_goback): {
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(1, HelloWorld::createScene());
		Director::getInstance()->replaceScene(scene);
		break;
	}

	case static_cast<int>(TAG_MENU::tag_check) : {
		if (User::getInstance()->myTurn) {
			User::getInstance()->isCheck = true;

		}
		break;
	}

	case static_cast<int>(TAG_MENU::tag_half) : {

		CCLOG("but_half");

		if (User::getInstance()->myTurn) {
			//User::getInstance()->isHalf = true;
			throwMoney();

			int a = roundMoney / 2;
			User::getInstance()->subMoney(a);
			roundMoney += a;
			CCLOG("moneymoney");

		}
		break;

	}

	case static_cast<int>(TAG_MENU::tag_call) : {

		break;
	}

	case static_cast<int>(TAG_MENU::tag_die) : {

		break;
	}

	}

}

bool GameScene::onTouchBegan(Touch * aa, Event *) {

	CCLOG("Touch");

	if (((Sprite*)this->getChildByName("spr_pill_start"))->getBoundingBox().containsPoint(aa->getLocation())&&!roundStart){
		CCLOG("roundStart = true");
		roundStart = true;
		roundMoney = 1000;
		this->removeChildByName("spr_pill_start");
		this->schedule(schedule_selector(GameScene::ui_Update), 0.5);
		this->schedule(schedule_selector(GameScene::ui_card_Update), 0.5);
		splitCard();

	}

	return true;
}

void GameScene::splitCard() {

	auto spr_card_1_user = Sprite::create(StringUtils::format("%d.png", User::getInstance()->arr_player_card[0]));
	spr_card_1_user->setPosition(winsize.width / 10, winsize.height / 2);
	spr_card_1_user->setScale(0.7);

	auto act_card_throw_to_user = MoveTo::create(0.5, Point(winsize.width / 2 - 80, winsize.height / 9));
	auto act_card_throw_spin = RotateBy::create(0.5, 360);
	auto act_card_throw_to_user_spawn = Spawn::create(act_card_throw_to_user, act_card_throw_spin, NULL);
	spr_card_1_user->runAction(act_card_throw_to_user_spawn);

	this->addChild(spr_card_1_user);
}

void GameScene::throwMoney() {

	CCLOG("throwMoney");

	Sprite* spr_money = Sprite::create("Paper_Money_96px.png");
	spr_money->setPosition(winsize.width - winsize.width / 8, winsize.width / 7);
	spr_money->setScale(1);
	
	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(1, 200);

	auto act_throw_money = MoveTo::create(0.7, Point(600 + num(rng) * 2, 400 + num(rng)));
	auto act_throw_money_1 = EaseOut::create(act_throw_money, 2);
	spr_money->runAction(act_throw_money_1);
	this->addChild(spr_money, 1);
	vec_spr_money.push_back(spr_money);
}

void GameScene::ui_Update(float d) {
	
	CCLOG("ui_update %f", d);
	int a = User::getInstance()->showMoney();
	auto label = (Label*)this->getChildByName("user_money");
	label->setString(StringUtils::format("현금 : %d 원", a));

	auto label_2 = (Label*)this->getChildByName("round_money");
	label_2->setString(StringUtils::format("판돈 : %d 원", roundMoney));

	if (User::getInstance()->showMoney() < roundMoney / 2) {
		
	}


	if (User::getInstance()->myTurn) {
		

	}

}

void GameScene::ui_card_Update(float d) {

	CCLOG("ui_card_update %f", d);
	
}

void GameScene::game_director(float d) { 

	roundMoney = 1000;
	while (1) {
		User::getInstance()->myTurn = true;
		
	}
}

bool GameScene::init() {

	if (!LayerColor::initWithColor(Color4B(0,255,100,40)))
	{
		return false;
	}
	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	for (int i : arr_card) arr_card[i] = { 1 };

	auto menu_item_1 = MenuItemLabel::create(
		Label::createWithTTF("나가기", "fonts\\Hogukstd.ttf", 34), CC_CALLBACK_1(GameScene::menuCallback, this));
	menu_item_1->setTag(static_cast<int>(TAG_MENU::tag_goback));

	auto menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(winsize.width / 10, winsize.height / 9);
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu, 1);

	auto label_user_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 27);
	label_user_money->setPosition(winsize.width - winsize.width / 8, winsize.width / 7);
	this->addChild(label_user_money, 5, "user_money");

	auto label_com_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 27);
	label_com_money->setPosition(winsize.width / 7, winsize.width - winsize.width / 8);
	this->addChild(label_com_money, 5, "com_money");

	auto label_round_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 30);
	label_round_money->setPosition(winsize.width - winsize.width / 5, winsize.height / 2);
	this->addChild(label_round_money, 5, "round_money");

	auto spr_but_check_0 = Sprite::create("spr_check_0.png");	auto spr_but_check_1 = Sprite::create("spr_check_1.png");
	auto spr_but_half_0 = Sprite::create("spr_half_0.png");		auto spr_but_half_1  = Sprite::create("spr_half_1.png");
	auto spr_but_call_0 = Sprite::create("spr_call_0.png");		auto spr_but_call_1  = Sprite::create("spr_call_1.png");
	auto spr_but_die_0 = Sprite::create("spr_die_0.png");		auto spr_but_die_1   = Sprite::create("spr_die_1.png");

	auto menu_spr_but_check = MenuItemSprite::create(
		spr_but_check_0, spr_but_check_1, CC_CALLBACK_1(GameScene::menuCallback, this));	menu_spr_but_check->setTag(static_cast<int>(TAG_MENU::tag_check));
	menu_spr_but_check->setScale(0.5);
	auto menu_spr_but_half = MenuItemSprite::create(
		spr_but_half_0, spr_but_half_1, CC_CALLBACK_1(GameScene::menuCallback, this));		menu_spr_but_half->setTag(static_cast<int>(TAG_MENU::tag_half));
	menu_spr_but_half->setScale(0.5);
	auto menu_spr_but_call = MenuItemSprite::create(
		spr_but_call_0, spr_but_call_1, CC_CALLBACK_1(GameScene::menuCallback, this));		menu_spr_but_call->setTag(static_cast<int>(TAG_MENU::tag_call));
	menu_spr_but_call->setScale(0.5);
	auto menu_spr_but_die = MenuItemSprite::create(
		spr_but_die_0, spr_but_die_1, CC_CALLBACK_1(GameScene::menuCallback, this));		menu_spr_but_die->setTag(static_cast<int>(TAG_MENU::tag_die));
	menu_spr_but_die->setScale(0.5);

	auto menu_bev = Menu::create(menu_spr_but_check, menu_spr_but_half, menu_spr_but_call, menu_spr_but_die, NULL);
	menu_bev->setPosition(winsize.width / 2, winsize.height / 4.5);
	menu_bev->alignItemsHorizontallyWithPadding(20);
	this->addChild(menu_bev);

	auto spr_pill_start = Sprite::create("Pill_96px.png");
	spr_pill_start->setPosition(winsize.width / 2, winsize.height / 2);
	this->addChild(spr_pill_start, 10, "spr_pill_start");
	
	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);

	
	

	return true;
}



void Player::setCard() {

	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(1, 20);
	int num_1 = num(rng);
	arr_player_card[0] = num_1;
	/*if (arr_card[num(rng)] != 0) {
		
		arr_card[num(rng)] = 0;
	}
	int num_2 = num(rng);
	if (arr_card[num(rng)] != 0) {
		arr_player_card[1] = num_2;
		arr_card[num(rng)] = 0;
	}*/

}

void Player::setUp() {
	bool isCheck = false;
	bool isHalf = false;
	bool isCall = false;
	bool isDie = false;
	bool myTurn = false;
}

User * User::getInstance() {

	if (user_1 == nullptr)
		user_1 = new User;

	return user_1;
}

