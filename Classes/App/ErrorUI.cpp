#include "WkCocosApp/ErrorUI.h"

#include "WkCocosApp/HelloWorldScene.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

const std::string ErrorUI::id = "error";

ErrorUI::ErrorUI()
	: Interface()
{
	//filepath is the id for the preload memory ( not used here )
	m_filepath = id;

	//building UI hierarchy
	m_widget = ui::Layout::create();

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// position the label on the center of the screen

	auto label = LabelTTF::create("ERROR", "Arial", 48);
	label->setPosition(Vec2(
		visibleSize.width / 2,
		(visibleSize.height + label->getContentSize().height) / 2));
	m_widget->addChild(label);

	auto refreshButton = MenuItemImage::create(
		"RefreshNormal.png",
		"RefreshSelected.png",
		CC_CALLBACK_1(ErrorUI::refreshCallback, this));
	refreshButton->setPosition(Vec2(
		visibleSize.width / 2,
		(visibleSize.height - refreshButton->getContentSize().height) / 2));
	m_widget->addChild(refreshButton);
		
	if (m_widget)
	{
		m_widget->retain(); //we need to retain it in memory ( or cocos will drop it )
		widget_cache.insert(std::pair<std::string, cocos2d::ui::Widget*>(id, m_widget));
	}

}

ErrorUI::~ErrorUI()
{}

void ErrorUI::refreshCallback(Ref* pSender)
{}