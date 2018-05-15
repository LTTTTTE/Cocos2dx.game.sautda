#include "cocos2d.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;

#define winsize Director::getInstance()->getWinSize()

class HelloWorld : public Layer {

public:

	void DrawGridWindow(const int interval, const Color4F& color);

	static Scene* createScene();
	void update(float dt);
	void menuCallback(Ref* sender);
	virtual bool init();
	void schelduleCallback(float delta);

	CREATE_FUNC(HelloWorld);


};

enum class TAG : int {

	tag_NULL,
	tag_play,
	tag_Option,
	tag_Help,
	tag_Quit

};