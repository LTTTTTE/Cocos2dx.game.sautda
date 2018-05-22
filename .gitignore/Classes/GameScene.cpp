#include "GameScene.h"
#include "HelloWorldScene.h"

User* User::user_1 = nullptr;
Computer* Computer::com_1 = nullptr;
int arr_card[21];

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

		CCLOG("but_check");

		if (User::getInstance()->myTurn) {

			User::getInstance()->reset_Bev();
			User::getInstance()->isCheck = true;

			CCLOG(" check ! ");
			
			User::getInstance()->myTurn = false;
			Computer::getInstance()->myTurn = true;
		}
		break;
	}

	case static_cast<int>(TAG_MENU::tag_half) : {

		CCLOG("but_half");

		if (User::getInstance()->myTurn) {

			User::getInstance()->reset_Bev();
			User::getInstance()->isHalf = true;
			throwMoney();

			double a = (double)(roundMoney / 2.0);
			User::getInstance()->subMoney(a);
			roundMoney += (double)a;
			callMoney = (double)(a - callMoney);
			halfCount++;
			CCLOG(" HALF ! ");
			User::getInstance()->myTurn = false;
			Computer::getInstance()->myTurn = true;
		}
		break;

	}

	case static_cast<int>(TAG_MENU::tag_call) : {

		CCLOG("but_call");

		if (User::getInstance()->myTurn && Computer::getInstance()->isHalf) {

			User::getInstance()->reset_Bev();
			User::getInstance()->isCall = true;

			User::getInstance()->subMoney(callMoney);
			roundMoney += callMoney;
			throwMoney();
			CCLOG(" CALL !  : %lf",callMoney);
			User::getInstance()->myTurn = false;
			Computer::getInstance()->myTurn = false;

		}

		break;
	}

	case static_cast<int>(TAG_MENU::tag_die) : {

		CCLOG("but_die");

		if (User::getInstance()->myTurn) {

			User::getInstance()->reset_Bev();
			User::getInstance()->isDie = true;

			CCLOG(" DIE ! ");
			User::getInstance()->myTurn = false;
			Computer::getInstance()->myTurn = false;

		}

		break;
	}

	}

}

bool GameScene::onTouchBegan(Touch * aa, Event *) {

	CCLOG("Touch");

	if(!roundStart)
	if (((Sprite*)this->getChildByName("spr_pill_start"))->getBoundingBox().containsPoint(aa->getLocation())&&!roundStart){

		CCLOG("roundStart = true");
		roundStart = true;
		roundMoney = (double)100.0;
		callMoney = 0.0;
		halfCount = 0;
		User::getInstance()->subMoney(roundMoney / 2.0);
		User::getInstance()->myTurn = true;

		this->removeChildByName("spr_pill_start");

		User::getInstance()->setCard();
		Computer::getInstance()->setCard();

		this->schedule(schedule_selector(GameScene::ui_Update), 0.5);
		this->schedule(schedule_selector(GameScene::ui_card_Update), 0.5);
		this->schedule(schedule_selector(GameScene::game_director), 2);
		splitCard();

	}
	if (roundStart)
	if (((Sprite*)this->getChildByName("spr_restart"))->getBoundingBox().containsPoint(aa->getLocation())) {
		
		CCLOG("roundRestart");

		this->removeChildByName("spr_card_1_user");
		this->removeChildByName("spr_card_1_com");
		this->removeChildByName("spr_card_1_user_2");
		this->removeChildByName("spr_card_1_com_2");
		auto label_user = (Label*)this->getChildByName("label_user_power");
		auto label_com = (Label*)this->getChildByName("label_com_power");
		label_user->setString("");
		label_com->setString("");
		phase2 = false;
		User::getInstance()->reset_Bev();
		Computer::getInstance()->reset_Bev();
		User::getInstance()->setUp();
		Computer::getInstance()->setUp();
		User::getInstance()->setCard();
		Computer::getInstance()->setCard();
		roundMoney = (double)100.0;
		callMoney = 0.0;
		halfCount = 0;
		

		User::getInstance()->subMoney(roundMoney / 2.0);
		User::getInstance()->myTurn = true;
		((Sprite*)this->getChildByName("spr_restart"))->setPosition(winsize.width * 2, winsize.height * 2);

		
		

		splitCard();

	}
	return true;
}

void GameScene::removeNode(Node * node){

	if (node != nullptr)
		this->removeChild(node);

}

void GameScene::splitCard() {

	if (!phase2) {

		for (int i = 0; i < 3; i++)CCLOG("player card %d = %d", i, User::getInstance()->arr_player_card[i]);
		for (int i = 0; i < 3; i++)CCLOG("computer card %d = %d", i, Computer::getInstance()->arr_player_card[i]);

		auto spr_card_1_user = Sprite::create(StringUtils::format("card\\%d.png", User::getInstance()->arr_player_card[0]));
		spr_card_1_user->setPosition(winsize.width / 10, winsize.height / 2);
		spr_card_1_user->setScale(0.7);

		auto spr_card_1_com = Sprite::create(StringUtils::format("card\\%d.png", Computer::getInstance()->arr_player_card[0]));
		spr_card_1_com->setPosition(winsize.width / 10, winsize.height / 2);
		spr_card_1_com->setScale(0.7);

		auto spr_card_back = Sprite::create("card\\card_back.PNG");
		spr_card_back->setPosition(winsize.width / 10, winsize.height / 2);
		spr_card_back->setScale(0.7);

		auto delay_card_throw = DelayTime::create(0.45);

		auto act_card_throw_to_user = MoveTo::create(0.5, Point(winsize.width / 2 - 80, winsize.height / 7));
		auto act_card_throw_spin = RotateBy::create(0.5, 360);
		auto act_card_throw_to_user_spawn = Spawn::create(act_card_throw_to_user, act_card_throw_spin, NULL);
		auto act_card_throw_to_user_spawn_seq = Sequence::create(delay_card_throw, act_card_throw_to_user_spawn, NULL);
		spr_card_1_user->runAction(act_card_throw_to_user_spawn_seq);

		auto act_card_throw_to_com = MoveTo::create(0.5, Point(winsize.width / 2 - 480, winsize.height / 7));
		auto act_card_throw_spin_1 = RotateBy::create(0.5, 360);
		auto act_card_throw_to_com_spawn = Spawn::create(act_card_throw_to_com, act_card_throw_spin_1, NULL);
		spr_card_1_com->runAction(act_card_throw_to_com_spawn);

		this->addChild(spr_card_1_user, 2, "spr_card_1_user");
		this->addChild(spr_card_1_com, 2, "spr_card_1_com");
		this->addChild(spr_card_back,10);
	}
	else {

		auto spr_card_1_user_2 = Sprite::create(StringUtils::format("%d.png", User::getInstance()->arr_player_card[1]));
		spr_card_1_user_2->setPosition(winsize.width / 10, winsize.height / 2);
		spr_card_1_user_2->setScale(0.7);

		auto spr_card_1_com_2 = Sprite::create(StringUtils::format("%d.png", Computer::getInstance()->arr_player_card[1]));
		spr_card_1_com_2->setPosition(winsize.width / 10, winsize.height / 2);
		spr_card_1_com_2->setScale(0.7);

		auto delay_card_throw = DelayTime::create(0.45);

		auto act_card_throw_to_user_2 = MoveTo::create(0.5, Point(winsize.width / 2 +20, winsize.height / 7));
		auto act_card_throw_spin_2 = RotateBy::create(0.5, 360);
		auto act_card_throw_to_user_spawn_2 = Spawn::create(act_card_throw_to_user_2, act_card_throw_spin_2, NULL);
		auto act_card_throw_to_user_spawn_seq = Sequence::create(delay_card_throw, delay_card_throw, delay_card_throw, act_card_throw_to_user_spawn_2, NULL);
		spr_card_1_user_2->runAction(act_card_throw_to_user_spawn_seq);

		auto act_card_throw_to_com_2 = MoveTo::create(0.5, Point(winsize.width / 2 - 380, winsize.height / 7));
		auto act_card_throw_spin_1_2 = RotateBy::create(0.5, 360);
		auto act_card_throw_to_com_spawn_2 = Spawn::create(act_card_throw_to_com_2, act_card_throw_spin_1_2, NULL);
		auto act_card_throw_to_com_spawn_2_seq = Sequence::create(delay_card_throw, delay_card_throw, act_card_throw_to_com_spawn_2, NULL);
		spr_card_1_com_2->runAction(act_card_throw_to_com_spawn_2_seq);

		this->addChild(spr_card_1_user_2, 2, "spr_card_1_user_2");
		this->addChild(spr_card_1_com_2, 2, "spr_card_1_com_2");

	}
}

void GameScene::throwMoney() {

	CCLOG("throwMoney");
	
	for (int i = 0; i < 4; i++) {

		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_int_distribution<__int64>num(-100, 100);

		int num_spr_money;
		if (halfCount < 3)num_spr_money = 1;
		else if (halfCount < 6)num_spr_money = 2;
		else if (halfCount < 9)num_spr_money = 3;
		else if (halfCount < 12)num_spr_money = 4;
		else if (halfCount < 15)num_spr_money = 5;
		else num_spr_money = 6;
		
		Sprite* spr_money = Sprite::create(StringUtils::format(("money\\money_%d.png"), num_spr_money));

		if (User::getInstance()->myTurn) spr_money->setPosition(winsize.width / 2 + 20, winsize.height / 7);
		else spr_money->setPosition(winsize.width / 2 - 380, winsize.height / 7);
		spr_money->setScale(1);

	    auto act_throw_money = MoveTo::create(0.7, Point(winsize.height / 2 + num(rng) * 3.5, winsize.height*0.75 + num(rng)*1.2));
		auto act_throw_money_1 = EaseOut::create(act_throw_money, 4);
		spr_money->runAction(act_throw_money_1);
		this->addChild(spr_money, 1);

		vec_spr_money.push_back(spr_money);
		
	}
}

void GameScene::throwLabel(){

	auto label = (Label*)this->getChildByName("label_com_bev");

	     if (Computer::getInstance()->isCheck)label->setString("眉农 ! ");
	else if (Computer::getInstance()->isHalf) label->setString("窍橇 ! ");
	else if (Computer::getInstance()->isCall) label->setString("妮 ! ");
	else if (Computer::getInstance()->isDie)  label->setString("促捞 ! ");
	
	auto act_fade_in = FadeIn::create(0.01);
	auto act_fade_out = FadeOut::create(1.5);
	auto act_fade_out_Easein = EaseIn::create(act_fade_out, 1.5);
	auto act_seq = Sequence::create(act_fade_in, act_fade_out_Easein, NULL);
	label->runAction(act_seq);

}

void GameScene::ui_Update(float d) {
	
	//CCLOG("ui_update %f", d);

	double a = User::getInstance()->showMoney();

	auto label = (Label*)this->getChildByName("user_money");
	label->setString(StringUtils::format("儡绊 : %.1lf 盔", a));

	auto label_2 = (Label*)this->getChildByName("round_money");
	label_2->setString(StringUtils::format("魄捣 : %.1lf 盔", roundMoney));

	if (User::getInstance()->isDie || Computer::getInstance()->isDie || phase2 && (User::getInstance()->isCall || Computer::getInstance()->isCall || User::getInstance()->isDie) && (!Computer::getInstance()->myTurn && !User::getInstance()->myTurn)) {

		if (User::getInstance()->showCardPower() > Computer::getInstance()->showCardPower()) {

			for (int i = 0; i < vec_spr_money.size(); i++) {
				auto act_money_to_winner = MoveTo::create(0.2, Point(winsize.width / 2 - 80, winsize.height / 7));
				auto act_delete = Sequence::create(act_money_to_winner, CallFunc::create(CC_CALLBACK_0(GameScene::removeNode, this, vec_spr_money[i])), nullptr);
				vec_spr_money[i]->runAction(act_delete);

				this->removeChild(vec_spr_money[i]);
				vec_spr_money.erase(vec_spr_money.begin() + i);
			}

			User::getInstance()->addMoney(roundMoney);
			roundMoney = 0;
		}
		else if (User::getInstance()->showCardPower() < Computer::getInstance()->showCardPower()) {

			for (int i = 0; i < vec_spr_money.size(); i++) {
				auto act_money_to_winner = MoveTo::create(0.2, Point(winsize.width / 2 - 480, winsize.height / 7));
				auto act_delete = Sequence::create(act_money_to_winner, CallFunc::create(CC_CALLBACK_0(GameScene::removeNode, this, vec_spr_money[i])), nullptr);
				vec_spr_money[i]->runAction(act_delete);

				this->removeChild(vec_spr_money[i]);
				vec_spr_money.erase(vec_spr_money.begin() + i);
			}

			Computer::getInstance()->addMoney(roundMoney);
			roundMoney = 0;
		}

	}
}

void GameScene::ui_card_Update(float d) {

	//CCLOG("ui_card_update %f", d);
	//for (int i = 0; i < 21; i++) CCLOG("card %d = %d", i, arr_card[i]);
	//for (int i = 0; i < 3; i++)CCLOG("player card %d = %d", i, User::getInstance()->arr_player_card[i]);
	//for (int i = 0; i < 3; i++)CCLOG("computer card %d = %d", i, Computer::getInstance()->arr_player_card[i]);
}

void GameScene::game_director(float d) { 
	
	///////////////////////////////////////
	if (Computer::getInstance()->myTurn) {
		
		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_int_distribution<__int64>num(1, 100);

		if (User::getInstance()->isCheck) {
			 
			if (num(rng) > 20) {
				
				Computer::getInstance()->reset_Bev();
				Computer::getInstance()->isHalf = true;
				
				double a = (double)(roundMoney / 2.0);
				//Computer::getInstance()->subMoney(a);
				roundMoney += (double)a;
				callMoney = (double)(a - callMoney);
				halfCount++;
				throwMoney();
				throwLabel();
				CCLOG(" COM : HALF ! ");
				Computer::getInstance()->myTurn = false;
				User::getInstance()->myTurn = true;

			}
			else {
				
				Computer::getInstance()->reset_Bev();
				Computer::getInstance()->isCall = true;

				//Computer::getInstance()->subMoney(callMoney);
				roundMoney += callMoney;
				throwMoney();
				throwLabel();
				CCLOG(" COM :  CALL ! : %lf", callMoney);

				Computer::getInstance()->myTurn = false;
				User::getInstance()->myTurn = false;

			}

		}
		else if (User::getInstance()->isHalf) {

			if (num(rng) <= 30) {
				
				Computer::getInstance()->reset_Bev();
				Computer::getInstance()->isCall = true;

				//Computer::getInstance()->subMoney(callMoney);
				roundMoney += callMoney;
				throwMoney();
				throwLabel();
				CCLOG(" COM :  CALL ! : %lf", callMoney);

				Computer::getInstance()->myTurn = false;
				User::getInstance()->myTurn = false;

			}
			else if (num(rng) < 90) {
				
				Computer::getInstance()->reset_Bev();
				Computer::getInstance()->isHalf = true;
				throwMoney();
				throwLabel();
				double a = (double)(roundMoney / 2.0);
				//Computer::getInstance()->subMoney(a);
				roundMoney += (double)a;
				callMoney = (double)(a - callMoney);
				halfCount++;
				CCLOG(" COM : HALF ! ");
				Computer::getInstance()->myTurn = false;
				User::getInstance()->myTurn = true;

			}
			else if (phase2 || num(rng) > 95) {
				
				Computer::getInstance()->reset_Bev();
				Computer::getInstance()->isDie = true;
				throwLabel();
				CCLOG(" COM : DIE ! ");
				Computer::getInstance()->myTurn = false;
				User::getInstance()->myTurn = false;

			}
		}
	}

	if (!phase2 && (User::getInstance()->isCall || Computer::getInstance()->isCall) && (!Computer::getInstance()->myTurn && !User::getInstance()->myTurn)) {

		CCLOG("PHASE 2 ! ");
		phase2 = true;
		auto delay = CCDelayTime::create(3.0);
		splitCard();
		CCLOG("PHASE 2 ! %d", phase2);
		callMoney = 0.0; 

		User::getInstance()->myTurn = true;
	}

	if (User::getInstance()->isDie || Computer::getInstance()->isDie || phase2 && (User::getInstance()->isCall || Computer::getInstance()->isCall || User::getInstance()->isDie) && (!Computer::getInstance()->myTurn && !User::getInstance()->myTurn)) {
		
		CCLOG(" END PHASE ! ");
		User::getInstance()->CardCheckAlGo();
		Computer::getInstance()->CardCheckAlGo();
		
		CCLOG("User : %d", User::getInstance()->showCardPower());
		CCLOG("Com  : %d", Computer::getInstance()->showCardPower());
		
		CheckWhatYouGot();
		auto spr = (Sprite*)this->getChildByName("spr_restart");
		spr->setPosition(winsize.width / 2, winsize.height / 2);
	}


	///////////////////////////////////////
}

void GameScene::CheckWhatYouGot() {

	int power = User::getInstance()->showCardPower();
	auto label_user = (Label*)this->getChildByName("label_user_power");
	

	for (int i = 0; i < 2; i++) {


		switch (power) {

		case 10000: {
			label_user->setString("伙迫堡动");
			break;
		}
		case 8000: {
			label_user->setString("堡动");
			break;
		}
		case 1000: {
			label_user->setString("厘动");
			break;
		}
		case 900: {
			label_user->setString("备动");
			break;
		}
		case 800: {
			label_user->setString("迫动");
			break;
		}
		case 700: {
			label_user->setString("磨动");
			break;
		}
		case 600: {
			label_user->setString("腊动");
			break;
		}
		case 500: {
			label_user->setString("坷动");
			break;
		}
		case 400: {
			label_user->setString("荤动");
			break;
		}
		case 300: {
			label_user->setString("伙动");
			break;
		}
		case 200: {
			label_user->setString("捞动");
			break;
		}
		case 100: {
			label_user->setString("老动");
			break;
		}
		case 80: {
			label_user->setString("舅府");
			break;
		}
		case 70: {
			label_user->setString("刀荤");
			break;
		}
		case 60: {
			label_user->setString("备绘");
			break;
		}
		case 50: {
			label_user->setString("厘绘");
			break;
		}
		case 40: {
			label_user->setString("厘荤");
			break;
		}
		case 30: {
			label_user->setString("技氟");
			break;
		}
		case 20: {
			label_user->setString("癌坷");
			break;
		}
		case 8: {
			label_user->setString("咯袋场");
			break;
		}
		case 7: {
			label_user->setString("老蚌场");
			break;
		}
		case 6: {
			label_user->setString("咯几场");
			break;
		}
		case 5: {
			label_user->setString("促几场");
			break;
		}
		case 4: {
			label_user->setString("匙场");
			break;
		}
		case 3: {
			label_user->setString("技场");
			break;
		}
		case 2: {
			label_user->setString("滴场");
			break;
		}
		case 1: {
			label_user->setString("茄场");
			break;
		}
		case 0: {
			label_user->setString("噶烹 ばば");
			break;
		}


		}

	power = Computer::getInstance()->showCardPower();
	label_user = (Label*)this->getChildByName("label_com_power");
	}


}

void Player::CardCheckAlGo() {

	int a = arr_player_card[0];
	int b = arr_player_card[1];

	for (int i = 0; i < 2; i++) {

		if (a == 3 && b == 8) setCardPower(10000); //3.8堡动
		else if (a == 1 && (b == 3 || b == 8))setCardPower(8000); //1.8 , 1.3 堡动
		else if (a + 10 == b) setCardPower(a * 100); // 1动 ~ 厘动 100 ~ 1000
		else if ((a == 1 || a == 11) && (b == 2 || b == 12))setCardPower(80); //舅府
		else if ((a == 1 || a == 11) && (b == 4 || b == 14))setCardPower(70); //刀荤
		else if ((a == 1 || a == 11) && (b == 9 || b == 19))setCardPower(60); //备绘
		else if ((a == 1 || a == 11) && (b == 10 || b == 20))setCardPower(50); //厘绘
		else if ((a == 4 || a == 14) && (b == 10 || b == 20))setCardPower(40); //厘荤
		else if ((a == 4 || a == 14) && (b == 6 || b == 16))setCardPower(30); //技氟
		else if (a + b == 9 || a + b == 19 || a + b == 29)setCardPower(20); //癌坷

//		else if ((a == 3 || a == 13) && (b == 7 || b == 17))setCardPower(999);		//动棱捞
//		else if (a == 4 && b == 9)setCardPower(1001);					   			//港胖备府备荤
//		else if (a == 4 && b == 7)setCardPower(9001);								//鞠青绢荤
//		else if ((a == 4 || a == 14) && (b == 9 || b == 19))setCardPower(81);		//备荤

		else setCardPower((a + b) % 10); // 棱菩
		a ^= b ^= a ^= b;
	}
}

bool GameScene::init() {

	if (!Layer::init())
	{
		return false;
	}
	//DrawGridWindow(50, Color4F(120, 120, 120, 120));

	auto menu_item_1 = MenuItemLabel::create(
		Label::createWithTTF("唱啊扁", "fonts\\Hogukstd.ttf", 34), CC_CALLBACK_1(GameScene::menuCallback, this));
	menu_item_1->setTag(static_cast<int>(TAG_MENU::tag_goback));

	auto menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(winsize.width / 10, winsize.height / 9);
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu, 1);

	auto label_user_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 27);
	label_user_money->setPosition(winsize.width - winsize.width / 7, winsize.width / 5);
	this->addChild(label_user_money, 5, "user_money");

	auto label_com_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 27);
	label_com_money->setPosition(winsize.width / 7, winsize.width - winsize.width / 8);
	this->addChild(label_com_money, 5, "com_money");

	auto label_round_money = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 30);
	label_round_money->setPosition(winsize.height / 2, winsize.height - 27);
	this->addChild(label_round_money, 5, "round_money");

	auto label_com_bev = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 47);
	label_com_bev->setPosition(winsize.width / 2 - 380, winsize.height / 4);
	this->addChild(label_com_bev, 6, "label_com_bev");

	auto label_user_power = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 34);
	label_user_power->setPosition(winsize.width / 2 - 80, winsize.height / 4);
	this->addChild(label_user_power, 10, "label_user_power");

	auto label_com_power = Label::createWithTTF("", "fonts\\Hogukstd.ttf", 34);
	label_com_power->setPosition(winsize.width / 2 - 480, winsize.height / 4);
	this->addChild(label_com_power, 10, "label_com_power");

	auto label_card_power = Label::createWithTTF(
		"伙迫堡动  堡动  厘动  9动  8动  7动  6动  5动  4动  3动  2动  1动  舅府  刀荤  备绘  厘绘  厘荤  技氟  癌坷   酒醛场 咯袋场 老蚌场 咯几场 促几场  匙场  技场  滴场  茄场  噶烹",
		"fonts\\Hogukstd.ttf", 30, Size(450, 450), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label_card_power->setPosition(winsize.height + (winsize.width - winsize.height) / 2, winsize.height / 2);
	label_card_power->setLineSpacing(20);
	this->addChild(label_card_power);

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
	menu_bev->setPosition(winsize.width - (winsize.width - winsize.height) / 2, winsize.height / 6);
	menu_bev->alignItemsHorizontallyWithPadding(25);
	this->addChild(menu_bev);

	auto spr_pill_start = Sprite::create("Pill_96px.png");
	spr_pill_start->setPosition(winsize.width / 2, winsize.height / 2);
	this->addChild(spr_pill_start, 10, "spr_pill_start");
	
	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);

	auto spr_background_1 = Sprite::create("gamescene_backGround_1.PNG");
	spr_background_1->setPosition(winsize.height / 2, winsize.height / 2);
	spr_background_1->setScale(1.34);
	this->addChild(spr_background_1,-100);

	auto spr_background_2 = Sprite::create("gamescene_backGround_2.PNG");
	spr_background_2->setPosition(winsize.width - (winsize.width - winsize.height) / 2, winsize.height / 2);
	spr_background_2->setScale(1.34);
	this->addChild(spr_background_2,-100);

	auto spr_restart = Sprite::create("Pikachu_Pokemon_48px.png");
	spr_restart->setPosition(winsize.width * 2, winsize.height * 2);
	spr_restart->setName("spr_restart");
	this->addChild(spr_restart);
	

	for (int i = 0; i < 21;i++) CCLOG("card %d = %d", i, arr_card[i]);
	for (int i = 0; i < 3; i++)CCLOG("player card %d = %d", i, User::getInstance()->arr_player_card[i]);

	return true;

}

void Player::setCard() {

	while (arr_player_card[0] == 0 || arr_player_card[1] == 0) {

		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_int_distribution<__int64>num(1, 20);

		int num_1 = num(rng);
		if (arr_card[num_1] != 1 && arr_player_card[0] == 0) {
			arr_player_card[0] = num_1;
			arr_card[num_1] = 1;
		}

		int num_2 = num(rng);
		if (arr_card[num_2] != 1 && arr_player_card[1] == 0) {
			arr_player_card[1] = num_2;
			arr_card[num_2] = 1;
		}

	}

}

void Player::setUp() {

	 isCheck = false;
	 isHalf = false;
	 isCall = false;
	 isDie = false;
	 myTurn = false;
	 cardPower = 0;
	 for (int i = 0; i < 3; i++)arr_player_card[i] = 0;
	
}

void Player::reset_Bev() {

	isCheck = false;
	isHalf = false;
	isCall = false;
	isDie = false;

}

User* User::getInstance() {

	if (user_1 == nullptr)
		user_1 = new User;

	return user_1;
}

Computer* Computer::getInstance() {

	if (com_1 == nullptr)
		com_1 = new Computer;

	return com_1;
}
