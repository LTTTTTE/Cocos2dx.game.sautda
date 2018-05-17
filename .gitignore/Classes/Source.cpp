/*

Hogukstd.ttf

bool QQScene::init()
{
	if (!Layer::init())
		return false;


	Sprite* sp = Sprite::create("Obstacles\\meteorBrown_big3.png");
	sp->setPosition(Vec2(500, 500));
	sp->setScale(3.0f);
	this->addChild(sp, 0, "NameTag");

	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(QQScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);


	return true;
}

bool ::onTouchBegan(Touch * aa, Event *)
{
	if (((Sprite*)this->getChildByName("NameTag"))->getBoundingBox().containsPoint(aa->getLocation()))
	{
		_eventDispatcher->removeAllEventListeners();
		Director::getInstance()->replaceScene(GameScene::create());
	}
	return true;
}



#include "2d\CCDrawNode.h"


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

EventListenerKeyboard* listner = EventListenerKeyboard::create();
listner->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
listner->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);

virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);







*/

//cocococos
/*
enum class KeyCode
{
	KEY_NONE,
	KEY_PAUSE,
	KEY_SCROLL_LOCK,
	KEY_PRINT,
	KEY_SYSREQ,
	KEY_BREAK,
	KEY_ESCAPE,
	KEY_BACK = KEY_ESCAPE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_BACK_TAB,
	KEY_RETURN,
	KEY_CAPS_LOCK,
	KEY_SHIFT,
	KEY_LEFT_SHIFT = KEY_SHIFT,
	KEY_RIGHT_SHIFT,
	KEY_CTRL,
	KEY_LEFT_CTRL = KEY_CTRL,
	KEY_RIGHT_CTRL,
	KEY_ALT,
	KEY_LEFT_ALT = KEY_ALT,
	KEY_RIGHT_ALT,
	KEY_MENU,
	KEY_HYPER,
	KEY_INSERT,
	KEY_HOME,
	KEY_PG_UP,
	KEY_DELETE,
	KEY_END,
	KEY_PG_DOWN,
	KEY_LEFT_ARROW,
	KEY_RIGHT_ARROW,
	KEY_UP_ARROW,
	KEY_DOWN_ARROW,
	KEY_NUM_LOCK,
	KEY_KP_PLUS,
	KEY_KP_MINUS,
	KEY_KP_MULTIPLY,
	KEY_KP_DIVIDE,
	KEY_KP_ENTER,
	KEY_KP_HOME,
	KEY_KP_UP,
	KEY_KP_PG_UP,
	KEY_KP_LEFT,
	KEY_KP_FIVE,
	KEY_KP_RIGHT,
	KEY_KP_END,
	KEY_KP_DOWN,
	KEY_KP_PG_DOWN,
	KEY_KP_INSERT,
	KEY_KP_DELETE,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_SPACE,
	KEY_EXCLAM,
	KEY_QUOTE,
	KEY_NUMBER,
	KEY_DOLLAR,
	KEY_PERCENT,
	KEY_CIRCUMFLEX,
	KEY_AMPERSAND,
	KEY_APOSTROPHE,
	KEY_LEFT_PARENTHESIS,
	KEY_RIGHT_PARENTHESIS,
	KEY_ASTERISK,
	KEY_PLUS,
	KEY_COMMA,
	KEY_MINUS,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_COLON,
	KEY_SEMICOLON,
	KEY_LESS_THAN,
	KEY_EQUAL,
	KEY_GREATER_THAN,
	KEY_QUESTION,
	KEY_AT,
	KEY_CAPITAL_A,
	KEY_CAPITAL_B,
	KEY_CAPITAL_C,
	KEY_CAPITAL_D,
	KEY_CAPITAL_E,
	KEY_CAPITAL_F,
	KEY_CAPITAL_G,
	KEY_CAPITAL_H,
	KEY_CAPITAL_I,
	KEY_CAPITAL_J,
	KEY_CAPITAL_K,
	KEY_CAPITAL_L,
	KEY_CAPITAL_M,
	KEY_CAPITAL_N,
	KEY_CAPITAL_O,
	KEY_CAPITAL_P,
	KEY_CAPITAL_Q,
	KEY_CAPITAL_R,
	KEY_CAPITAL_S,
	KEY_CAPITAL_T,
	KEY_CAPITAL_U,
	KEY_CAPITAL_V,
	KEY_CAPITAL_W,
	KEY_CAPITAL_X,
	KEY_CAPITAL_Y,
	KEY_CAPITAL_Z,
	KEY_LEFT_BRACKET,
	KEY_BACK_SLASH,
	KEY_RIGHT_BRACKET,
	KEY_UNDERSCORE,
	KEY_GRAVE,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_LEFT_BRACE,
	KEY_BAR,
	KEY_RIGHT_BRACE,
	KEY_TILDE,
	KEY_EURO,
	KEY_POUND,
	KEY_YEN,
	KEY_MIDDLE_DOT,
	KEY_SEARCH,
	KEY_DPAD_LEFT,
	KEY_DPAD_RIGHT,
	KEY_DPAD_UP,
	KEY_DPAD_DOWN,
	KEY_DPAD_CENTER,
	KEY_ENTER,
	KEY_PLAY
};


#include "HelloWorldScene.h"
#include "GameScene.h"

Scene* GameScene::createScene() {

auto scene = Scene::create();

auto layer = GameScene::create();

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


void GameScene::onKeyPressed(EventKeyboard::KeyCode e, Event *){

Sprite* spr = (Sprite*)this->getChildByName("player");

if (e == EventKeyboard::KeyCode::KEY_LEFT_ARROW){

++toggle; vec = -3;
}
if (e == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){

++toggle; vec = 3;
}
if (e == EventKeyboard::KeyCode::KEY_SPACE){
Action* act_bounce = JumpBy::create(0.4, Point(0, 0), 50, 1);
spr->runAction(act_bounce);
}

}


void GameScene::onKeyReleased(EventKeyboard::KeyCode e, Event *){

Sprite* spr = (Sprite*)this->getChildByName("player");

if (e == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
--toggle; vec = 3;
}
if (e == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
--toggle; vec = -3;
}

}

bool GameScene::onTouchBegan(Touch* touch, Event* unusedEvent) {

CCLOG("MOUSE EVENTS");

Sprite* spr = (Sprite*)this->getChildByName("backScene");

if (spr->getBoundingBox().containsPoint(touch->getLocation())) {
Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
auto scene = TransitionFade::create(1, HelloWorld::createScene());
Director::getInstance()->replaceScene(scene);
}

std::random_device rd;
std::mt19937_64 rng(rd());
std::uniform_int_distribution<__int64>num(0, 200);

if ((Sprite*)this->getChildByName("backScene")->getBoundingBox().containsPoint(touch->getLocation())) {
Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
auto scene = TransitionFade::create(1, GameScene::createScene());
Director::getInstance()->replaceScene(scene);
}

if (((Sprite*)this->getChildByName("letUsSnowy"))->getBoundingBox().containsPoint(touch->getLocation())) {

Sprite* spr_Snow = Sprite::create("Winter_96px.png");
spr_Snow->setPosition(num(rng) * 5, num(rng) + 500);
spr_Snow->setScale(0.5);
this->addChild(spr_Snow, 1, "snow");
vec_snow.push_back(spr_Snow);
ccBezierConfig bez1;
bez1.controlPoint_1 = Point(num(rng) * 7 - 200, num(rng) + 300);
bez1.controlPoint_2 = Point(num(rng) * 7 - 200, num(rng) + 100);
bez1.endPosition = Point(num(rng) * 7 - 200, -100);

Action* act_Snowy = BezierTo::create(8, bez1);
spr_Snow->runAction(act_Snowy);
}
return true;
}

void GameScene::removeNode(Node * node){
if (node != nullptr)
this->removeChild(node);

}

////////////////////////////////////////////////////////////////////////////////////////////

void GameScene::update(float dt) {

CCLOG("%d , %d", toggle, vec);

Sprite* spr_player = (Sprite*)this->getChildByName("player");
//	Sprite* spr_snow = (Sprite*)this->getChildByName("snow");

if (toggle == 2) {
spr_player->setPosition(spr_player->getPosition().x + vec, spr_player->getPosition().y);
}
if (toggle == 1) {
spr_player->setPosition(spr_player->getPosition().x + vec, spr_player->getPosition().y);
}
for (int i = 0; i < vec_snow.size();) {//for문돌시 erase되는 조건문에서는 i++이되면안댐
if (vec_snow[i]->getBoundingBox().containsPoint(spr_player->getPosition())) {

auto ani_explosion = Animation::create();
ani_explosion->setDelayPerUnit(0.05);

Sprite* spr_explostion = Sprite::create("pixelExplosion00.png");
spr_explostion->setPosition(vec_snow[i]->getPosition());
this->addChild(spr_explostion, 0, "explosion");

for (int i = 0; i < 8; i++) {

ani_explosion->addSpriteFrameWithFile(StringUtils::format("pixelExplosion%02d.png", i));
}
auto ani_explosion_ani = Animate::create(ani_explosion);
auto act_explosion_ani = Sequence::create(ani_explosion_ani, CallFunc::create(CC_CALLBACK_0(GameScene::removeNode, this, spr_explostion)),nullptr );
spr_explostion->runAction(act_explosion_ani);

this->removeChild(vec_snow[i]);
vec_snow.erase(vec_snow.begin() + i);
point++;

}
else if (vec_snow[i]->getPosition().y < 0) {
this->removeChild(vec_snow[i]);
vec_snow.erase(vec_snow.begin() + i);

}
else i++;
}
auto label = (Label*)this->getChildByName("point");
label->setString(StringUtils::format("Point : %d", point));

}

///////////////////////////////////////////////////////////////////////////////////////////

bool GameScene::init() {

if (!Layer::init()) {


return false;
}

DrawGridWindow(50, Color4F(120, 120, 120, 120));

Sprite* spr_Pill = Sprite::create("Pill_96px.png");
spr_Pill->setPosition(100, 100);
this->addChild(spr_Pill, 0, "backScene");

Sprite* spr_IronMan = Sprite::create("Iron_Man_96px.png");
spr_IronMan->setPosition(500, 50);
spr_IronMan->setScale(0.7);
this->addChild(spr_IronMan, 0, "player");

Sprite* spr_Sleet = Sprite::create("Sleet_96px.png");
spr_Sleet->setPosition(100, 700);
this->addChild(spr_Sleet, 0, "letUsSnowy");

auto listener = EventListenerTouchOneByOne::create();
listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

EventListenerKeyboard* listner = EventListenerKeyboard::create();
listner->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
listner->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);

auto label_point = Label::createWithSystemFont("", "", 20);
label_point->setPosition(950, 700);
this->addChild(label_point, 5, "point");


this->scheduleUpdate();

return true;
}




void HelloWorld::doPause(Ref* pSender)

{

Director::getInstance()->getScheduler()->pauseTarget(this);

}



void HelloWorld::doResume(Ref* pSender)

{

Director::getInstance()->getScheduler()->resumeTarget(this);

}



*/