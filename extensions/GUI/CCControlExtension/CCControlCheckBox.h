#ifndef __CCCONTROL_CHECKBOX_H__
#define __CCCONTROL_CHECKBOX_H__

#include "cocos2d.h"
#include "CCControlExtensions.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocos2d {
    
    class CCControlCheckBox: public cocos2d::extension::CCControl
    {
        CC_SYNTHESIZE_READONLY(float, m_checked, IsChecked);
        virtual void setIsChecked(bool val);
        /* Define the button margin for Top/Bottom edge */
        CC_SYNTHESIZE_READONLY(int, m_marginV, VerticalMargin);
        /* Define the button margin for Left/Right edge */
        CC_SYNTHESIZE_READONLY(int, m_marginH, HorizontalOrigin);
        //set the margins at once (so we only have to do one call of needsLayout)
        virtual void setMargins(int marginH, int marginV);
        
        
    protected:
        CCSprite* m_checkedSprite, *m_uncheckedSprite;
        cocos2d::extension::CCScale9Sprite* m_backgroundSprite;
        CCLabelTTF* m_label;
        std::string m_settingKey;
        float uiScale, spriteScale;
        
        
    public:
        static CCControlCheckBox* create(CCSprite* checkedSprite, CCSprite* uncheckedSprite, cocos2d::extension::CCScale9Sprite* backgroundSprite, CCLabelTTF* label, std::string settingKey);
        static CCControlCheckBox* create(const char* checkedIcon, const char* uncheckedIcon, const char* backgroundFile, CCRect rect, const char* text, const char* fontName, float fontSize, std::string settingKey);
        
        virtual bool initWithSprites(CCSprite* checkedSprite, CCSprite* uncheckedSprite, cocos2d::extension::CCScale9Sprite* backgroundSprite, CCLabelTTF* label, std::string settingKey);
        virtual void saveValue();
        
        //touch events
        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
        
    protected:
        virtual void needsLayout();
    };
    
} /* namespace rabcocos */

#endif