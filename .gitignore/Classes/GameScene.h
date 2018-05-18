#include "cocos2d.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;
class Player {

private:

	int money;
	int cardPower;
	//static Player* player;

public:

	int arr_player_card[3];

	bool isCheck;
	bool isHalf;
	bool isCall;
	bool isDie;
	bool myTurn;

	void setMoney() { money = 10000; }
	void setMoney(int a) { money = a; }
	void addMoney(int a) { money += a; }
	void subMoney(int a) { money -= a; }
	int showMoney() { return money; }
	void setCardPower(int a) { cardPower = a; }
	
	void setUp();
	void setCard();

};


class User : public Player {
public:
	static User* user_1;
	static User* getInstance();
	User() {
				setMoney();
				setCard();
				setUp();
	}


};

class Computer : public Player {
public:
	Computer() {
		//		setMoney();
		//		setCard();
		//		setUp();
	}


};

class GameScene : public LayerColor {

public:

	void DrawGridWindow(const int interval, const Color4F& color);

	static Scene* createScene();
	std::vector<Sprite*>vec_spr_money;
	int roundMoney;

	void menuCallback(Ref* sender);
	bool onTouchBegan(Touch * aa, Event *);
	void gameAlgo() {};
	bool threeCard = false;
	
	bool roundStart = false;
	
	void splitCard();
	void throwMoney();
	void ui_Update(float d);
	void ui_card_Update(float d);

	void game_director(float d);
	virtual bool init();

	CREATE_FUNC(GameScene);

};




enum class Card : int {

	c1_0 = 100,
	c1_1,
	c2_0,
	c2_1,
	c3_0,
	c3_1,
	c4_0,
	c4_1,
	c5_0,
	c5_1,
	c6_0,
	c6_1,
	c7_0,
	c7_1,
	c8_0,
	c8_1,
	c9_0,
	c9_1,
	cA_0,
	cA_1
};

enum class TAG_MENU : int {
	
	tag_goback = 10 ,
	tag_check,
	tag_half,
	tag_call,
	tag_die

};