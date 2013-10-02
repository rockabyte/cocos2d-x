

#include "CCControlCheckBox.h"

using namespace cocos2d;
using namespace std;

CCControlCheckBox* CCControlCheckBox::create(CCSprite* checkedSprite, CCSprite* uncheckedSprite, CCScale9Sprite* backgroundSprite, CCLabelTTF* label, string settingKey)
{
	CCControlCheckBox *pRet = new CCControlCheckBox();
	pRet->initWithSprites(checkedSprite, uncheckedSprite, backgroundSprite, label, settingKey);
	pRet->autorelease();
	return pRet;
}


CCControlCheckBox* CCControlCheckBox::create(const char* checkedIcon, const char* uncheckedIcon, const char* backgroundFile, CCRect rect, const char* text, const char* fontName, float fontSize, string settingKey)
{
	CCSprite *checkedSprite      = CCSprite::create(checkedIcon);
    CCSprite *uncheckedSprite        = CCSprite::create(uncheckedIcon);
	CCLabelTTF* label = CCLabelTTF::create(text, fontName, fontSize);
	CCScale9Sprite* backgroundSprite=CCScale9Sprite::create(backgroundFile, rect);
	return create(checkedSprite, uncheckedSprite, backgroundSprite, label, settingKey);
}

bool CCControlCheckBox::initWithSprites(CCSprite* checkedSprite, CCSprite* uncheckedSprite, CCScale9Sprite* backgroundSprite, CCLabelTTF* label, string settingKey)
{
    /*
	if (!CCControl::init())
		return false;
     */
	m_checkedSprite=checkedSprite;
	m_uncheckedSprite=uncheckedSprite;
	m_backgroundSprite=backgroundSprite;
	m_label=label;
	m_settingKey=settingKey;
	m_label->setColor(ccBLACK);
	this->addChild(m_checkedSprite, 1);
	this->addChild(m_uncheckedSprite, 1);
	this->addChild(m_label, 2);
    this->addChild(m_backgroundSprite, 0);

	// Set the default anchor point
    
	//setIsRelativeAnchorPoint(true); //????
	setAnchorPoint(ccp(0.5f, 0.5f));

    /* ???
	uiScale=GameState::sharedGameState()->getUIScale();
	spriteScale=GameState::sharedGameState()->getSpriteScale();
    */

	m_checkedSprite->setScale(spriteScale);
	m_uncheckedSprite->setScale(spriteScale);

	//default margins
	m_marginH=16*uiScale;	
	m_marginV=12*uiScale;
	setTouchEnabled(true);

	setIsChecked(CCUserDefault::sharedUserDefault()->getBoolForKey(m_settingKey.c_str(), true));
	needsLayout();
	return true;
}

void CCControlCheckBox::setIsChecked(bool val)
{
	m_checked=val;
	if (m_checked)
	{
		m_checkedSprite->setVisible(true);
		m_uncheckedSprite->setVisible(false);
	}
	else
	{
        m_checkedSprite->setVisible(false);
		m_uncheckedSprite->setVisible(true);
	}
	sendActionsForControlEvents(CCControlEventValueChanged);        

}

void CCControlCheckBox::saveValue()
{
	//CCUserDefault::sharedUserDefault()->setBoolForKey(m_settingKey.c_str(), m_checked);
}



void CCControlCheckBox::setMargins(int marginH, int marginV)
{
	m_marginV=marginV;
	m_marginH=marginH;
	needsLayout();
}


void CCControlCheckBox::needsLayout()
{
	float padding=10;
	float width=m_marginH+m_checkedSprite->getContentSize().width*spriteScale+padding+m_label->getContentSize().width+m_marginH;
	float height=m_marginV+max(m_checkedSprite->getContentSize().height*spriteScale, m_label->getContentSize().height)+m_marginV;
	CCSize size=CCSizeMake(width, height);
	setContentSize(size);
    m_backgroundSprite->setContentSize(size);

	m_backgroundSprite->setPosition(width/2.0f, height/2.0f);
	m_checkedSprite->setPosition(ccp(m_marginH+m_checkedSprite->getContentSize().width*spriteScale/2.0f, height/2.0f));
	m_uncheckedSprite->setPosition(ccp(m_marginH+m_checkedSprite->getContentSize().width*spriteScale/2.0f, height/2.0f));
	m_label->setPosition(ccp(width-m_marginH-m_label->getContentSize().width/2.0f, height/2.0f));
}

bool CCControlCheckBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !isEnabled())
    {
		return false;
	}
    	
	sendActionsForControlEvents(CCControlEventTouchDown);
    return true;
}

void CCControlCheckBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{    
    if (isTouchInside(pTouch))
    {
		setIsChecked(!m_checked);
    }
}

