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

	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto scene = TransitionFade::create(1, HelloWorld::createScene());
	Director::getInstance()->replaceScene(scene);

}

void GameScene::ui_Update(float d) {

	int a = User::getInstance()->showMoney();
	auto label = (Label*)this->getChildByName("user_money");
	label->setString(StringUtils::format("현금 : %d 원", a));

	if (User::getInstance()->myTurn) {
		

	}

}

void GameScene::ui_card_Update(float d) {

	auto spr_card_1_user = Sprite::create(StringUtils::format("%d.png", User::getInstance()->arr_player_card[0]));//
	spr_card_1_user->setPosition(winsize.width / 10, winsize.height / 2);
	spr_card_1_user->setScale(0.7);
	auto act_card_throw_to_user = MoveTo::create(1.5, Point(winsize.width / 2 - 80, winsize.height / 5));
	auto act_card_throw_spin = RotateBy::create(1.5, 360);
	auto act_card_throw_to_user_spawn = Spawn::create(act_card_throw_to_user, act_card_throw_spin, NULL);
	spr_card_1_user->runAction(act_card_throw_to_user_spawn);
	this->addChild(spr_card_1_user);
	Director::getInstance()->getScheduler()->pauseTarget(this);
}

void GameScene::game_director(float d) {

	roundMoney = 1000;
	User::getInstance()->myTurn = true;

}

bool GameScene::init() {

	if (!Layer::init())
	{
		return false;
	}
	DrawGridWindow(50, Color4F(120, 120, 120, 120));

	for (int i : arr_card) arr_card[i] = { 1 };

	auto menu_item_1 = MenuItemLabel::create(
		Label::createWithTTF("나가기", "fonts\\Hogukstd.ttf", 34), CC_CALLBACK_1(GameScene::menuCallback, this));
	auto menu = Menu::create(menu_item_1, NULL);

	menu->setPosition(winsize.width / 10, winsize.height / 9);
	menu->alignItemsVerticallyWithPadding(20);

	this->addChild(menu);

	auto label_user_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 20);
	label_user_money->setPosition(winsize.width - winsize.width / 8, winsize.width / 7);
	this->addChild(label_user_money, 5, "user_money");

	auto label_com_money = Label::createWithSystemFont("", "", 20);
	label_com_money->setPosition(winsize.width / 7, winsize.width - winsize.width / 8);
	this->addChild(label_com_money, 5, "com_money");

	auto spr_but_check = Sprite::create("");
	auto spr_but_half = Sprite::create("");
	auto spr_but_call = Sprite::create("");
	auto spr_but_die = Sprite::create("");
	
	

	this->schedule(schedule_selector(GameScene::ui_Update), 0.5);
	this->schedule(schedule_selector(GameScene::ui_card_Update), 0.5);

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

