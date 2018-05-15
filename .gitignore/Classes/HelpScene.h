#include "cocos2d.h"
#pragma execution_character_set("utf-8")

USING_NS_CC;

class HelpScene : public Layer {

public:

	void DrawGridWindow(const int interval, const Color4F& color);

	static Scene* createScene();

	void menuCallback(Ref* sender);
	
	virtual bool init();

	CREATE_FUNC(HelpScene);

};
