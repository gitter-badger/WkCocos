#include "WkCocos/Utils/CocosAppender.h"

//#include "cocos/ui/UILayout.h"
#include "cocos/ui/UITextBMFont.h"
#include "cocos/ui/UIListView.h"

namespace WkCocos
{

	CocosLogAppender::CocosLogAppender(cocos2d::Node* root, const std::string& fontName, const CheckBoxRes& res)
		: _log(nullptr)
		, _model(nullptr)
		, _logSize(_MAX_LINE)
	{
		// make model
		_model = cocos2d::ui::TextBMFont::create("", fontName);
		_model->setTouchEnabled(false);

		// make tree hierarchy
		cocos2d::ui::Layout* bg = cocos2d::ui::Layout::create();
		_log = cocos2d::ui::ListView::create();
		cocos2d::ui::CheckBox* toggle = cocos2d::ui::CheckBox::create();
		
		// setup bg
		bg->setTouchEnabled(false);
		bg->setContentSize(root->getContentSize());
		bg->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
		bg->setBackGroundColor(cocos2d::Color3B(20, 20, 20));
		bg->setBackGroundColorOpacity(70);
		bg->setLocalZOrder(9999);
		bg->addChild(_log);
		bg->addChild(toggle);

		// setup log
		_log->setTouchEnabled(false);
		_log->setItemModel(_model);
		_log->pushBackDefaultItem();
		_log->setContentSize(root->getContentSize());
		_log->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
		_log->setBackGroundColor(cocos2d::Color3B(20, 20, 20));
		_log->setBackGroundColorOpacity(70);

		// check
		toggle->setTouchEnabled(true);
		toggle->setContentSize(cocos2d::Size(200, 200));
		if (!res.m_textureName[CheckBoxRes::BG].empty())
		{
			toggle->loadTextureBackGround(res.m_textureName[CheckBoxRes::BG], res.m_textureType[CheckBoxRes::BG]);
		}
		if (!res.m_textureName[CheckBoxRes::BG_DIS].empty())
		{
			toggle->loadTextureBackGroundDisabled(res.m_textureName[CheckBoxRes::BG_DIS], res.m_textureType[CheckBoxRes::BG_DIS]);
		}
		if (!res.m_textureName[CheckBoxRes::BG_SEL].empty())
		{
			toggle->loadTextureBackGroundSelected(res.m_textureName[CheckBoxRes::BG_SEL], res.m_textureType[CheckBoxRes::BG_SEL]);
		}
		if (!res.m_textureName[CheckBoxRes::MARK].empty())
		{
			toggle->loadTextureFrontCross(res.m_textureName[CheckBoxRes::MARK], res.m_textureType[CheckBoxRes::MARK]);
		}
		if (!res.m_textureName[CheckBoxRes::CROSS].empty())
		{
			toggle->loadTextureFrontCrossDisabled(res.m_textureName[CheckBoxRes::CROSS], res.m_textureType[CheckBoxRes::CROSS]);
		}
		toggle->addEventListener(std::bind(&CocosLogAppender::toggleScroll, this, std::placeholders::_1, std::placeholders::_2));


		root->addChild(bg);
	}
	
	CocosLogAppender::~CocosLogAppender()
	{}

	LogAppender& CocosLogAppender::operator << (const LogStreamBuf & msg)
	{	
		std::stringstream str;
		str << msg;
		
		std::string output = str.str();

		if (_log->getItems().size() >= _logSize)
		{
			_log->removeItem(0);
		}

		_log->pushBackDefaultItem();
		cocos2d::ui::TextBMFont* line = static_cast<cocos2d::ui::TextBMFont*>(_log->getItem(_log->getItems().size() - 1));
		line->setString(output);

		_log->jumpToBottom();

		return *this;
	}

	void CocosLogAppender::toggleScroll(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType event)
	{
		switch (event)
		{
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			_log->setTouchEnabled(true);
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			_log->setTouchEnabled(false);
			break;
		}
	}

	CCocosLogAppender::CCocosLogAppender()
	{}
	
	CCocosLogAppender::~CCocosLogAppender()
	{}
	
	LogAppender& CCocosLogAppender::operator << (const LogStreamBuf & msg)
	{
		CCLOG("%s", msg.str().c_str());

		return *this;
	}

}//namespace WkCocos
