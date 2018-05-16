#include "GameScene.h"
#include "HelloWorldScene.h"

User* User::user_1 = nullptr;

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

int arr_card[21];

void GameScene::gameAlgo() {
	

}

void GameScene::ui_Update(float d) {

	int a = User::getInstance()->showMoney();
	auto label = (Label*)this->getChildByName("user_money");
	label->setString(StringUtils::format("Money : %d 원",a));
	
}

bool GameScene::init(){

	if (!Layer::init())
	{
		return false;
	}

	DrawGridWindow(50, Color4F(120, 120, 120, 120));
	
//	User* user_1 = new User;
//	Computer* com_1 = new Computer;
	
	for (int i : arr_card) arr_card[i] = { 1 };
	this->schedule(schedule_selector(GameScene::ui_Update), 0.5);

	auto menu_item_1 = MenuItemLabel::create(
		Label::createWithTTF("나가기", "fonts\\Hogukstd.ttf", 34), CC_CALLBACK_1(GameScene::menuCallback, this));
	auto menu = Menu::create(menu_item_1, NULL);

	menu->setPosition(winsize.width / 10, winsize.height / 9);
	menu->alignItemsVerticallyWithPadding(20);

	this->addChild(menu);

	auto label_user_money = Label::createWithSystemFont("", "", 20);
	label_user_money->setPosition(winsize.width - winsize.width / 8, winsize.width / 7);
	this->addChild(label_user_money, 5, "user_money");

	auto label_com_money = Label::createWithSystemFont("", "", 20);
	label_com_money->setPosition(winsize.width / 7, winsize.width - winsize.width / 8);
	this->addChild(label_com_money, 5, "com_money");


	auto spr_card_1_user = Sprite::create(StringUtils::format("%2d", User::getInstance()->arr_player_card[0]));
	
	return true;
}

void GameScene::update(float d) {

	CCLOG("%f", d);
	
}

void Player::setCard() {

	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64>num(1, 20);
	int num_1 = num(rng);
	if (arr_card[num(rng)] == 1) {
		arr_player_card[0] = num_1;
		arr_card[num(rng)] = 0;
	}
	int num_2 = num(rng);
	if (arr_card[num(rng)] == 1) {
		arr_player_card[0] = num_2;
		arr_card[num(rng)] = 0;
	}

}
User * User::getInstance()
{
	CCASSERT(user_1 != nullptr, "ERROR");
	return user_1;
}
