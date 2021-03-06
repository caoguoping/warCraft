//
//  SGBattleRoundPromptLayer.cpp
//  GameSanGuo
//
//  Created by wenlong w on 13-4-25.
//
//

#include "SGBattleRoundPromptLayer.h"
#include "SGHelpLayer.h"
#include "SGBattleManager.h"
#include "SGGuideManager.h"
#include "SGCCLabelTTF.h"
#include "SGPlayerInfo.h"
#include "ResourceManager.h"
#include "SGAIManager.h"
#include "SGStringConfig.h"
#include "SGMainManager.h"
#define ROUND_PROMPT_W 410
#define ROUND_PROMPT_H 250


SGBattleRoundPromptLayer::SGBattleRoundPromptLayer()
:_target(NULL)
,_round(0)
,size(CCSizeMake(530, 340))
{
    ;
}


SGBattleRoundPromptLayer::~SGBattleRoundPromptLayer()
{
    ResourceManager::sharedInstance()->unBindLayerTexture(sg_box_battleRoundPrompt);
}

SGBattleRoundPromptLayer* SGBattleRoundPromptLayer::create(SGBoxDelegate *target, int round)
{
    SGBattleRoundPromptLayer *roundPromptLayer = new SGBattleRoundPromptLayer();
    
    roundPromptLayer->_target = target;
    roundPromptLayer->_round = round;
    if(roundPromptLayer && roundPromptLayer->SGBaseBox::init(target, box_battleRoundPromptLayer, roundPromptLayer->size))
    {
        roundPromptLayer->autorelease();
        return roundPromptLayer;
    }
    
    CC_SAFE_DELETE(roundPromptLayer);
    return NULL;
}


void SGBattleRoundPromptLayer::initMsg()
{
    
    SGBattleManager::sharedBattle()->setCanTouchAutoBattleBtn(false);

    int w = this->getContentSize().width;
    int h = this->getContentSize().height;
    CCPoint center = ccpAdd(SGLayout::getPoint(kMiddleCenter), ccp(0, 50));
    
//    CCSprite *title_Text = CCSprite::createWithSpriteFrameName("round_prompt.png");
    SGCCLabelTTF* title_Text = SGCCLabelTTF::create(str_BattleRoundPromptLayer_str1, FONT_PANGWA, 40 , ccWHITE , ccc3(143, 87, 0));
    //modify by:zyc  merge into create.
    //title_Text->setOutSideColor(ccc3(143,87,0));
    this->addChild(title_Text, 1);
    
    title_Text->setPosition(ccpAdd(center, ccp(0, 360*.5f - 105)));
    
    CCString *text = CCString::createWithFormat(str_BattleRoundPromptLayer_str2, _round);
    SGCCLabelTTF *label = SGCCLabelTTF::create(text->getCString(), FONT_BOXINFO, 30, CCSizeMake(530*.75f, 260*.35f), kCCTextAlignmentLeft);
    label->setPosition(ccpAdd(center, ccp(0, -30)));
    this->addChild(label, 5);
    
    label = SGCCLabelTTF::create(str_BattleRoundPromptLayer_str3, FONT_BOXINFO, 24, CCSizeMake(530*.85f, 260*.35f) , ccYELLOW);
    label->setPosition(ccpAdd(center, ccp(3, -110)));
    //modify by:zyc. merge into create.
    //label->setColor(ccYELLOW);
    this->addChild(label, 5);
    
    SGButton *end = SGButton::create("box_btn_newbg.png", "round_prompt_button.png", this, menu_selector(SGBattleRoundPromptLayer::buttonEnd), CCPointZero, false, true);
    
//    //投降按钮
//    SGButton *surrender = SGButton::create("box_btn_newbg.png", "round_prompt_button1.png", this, menu_selector(SGBattleRoundPromptLayer::buttonSurrender), CCPointZero, false, true);
    
    SGButton *close = SGButton::create("box_btn_newbg.png", "public_font_qixiao.png", this, menu_selector(SGBattleRoundPromptLayer::buttonClose),CCPointZero,false,true);
    
//    int story = SGPlayerInfo::sharePlayerInfo()->getCurrentStoryId();
//    int scene = SGPlayerInfo::sharePlayerInfo()->getCurrentSceneId();
//    if (SGGuideManager::shareManager()->isGuide || (story==1 && scene==2))
//        surrender->setEnabled(false);
    
    end->setTag(101);
    
  //  this->addBtn(surrender);
    this->addBtn(end);
    this->addBtn(close);
    
    end->setPosition(ccp( w * 0.5f - size.width * 0.5 + end->getContentSize().width * 0.7, h * 0.5 - size.height * 0.5 + end->getContentSize().height * 0.9));
   // surrender->setPosition(ccp( w * 0.5f, h * 0.5 - size.height * 0.5 + surrender->getContentSize().height * 0.9));
    close->setPosition(ccp( w * 0.5f + size.width * 0.5 - close->getContentSize().width * 0.7, h * 0.5 - size.height * 0.5 + close->getContentSize().height * 0.9 ));
    
    
}

void SGBattleRoundPromptLayer::buttonClose()
{
    EFFECT_PLAY(MUSIC_BTN);
    this->boxClose();
    SGBattleManager::sharedBattle()->setCanTouchAutoBattleBtn(true);
}

void SGBattleRoundPromptLayer::buttonEnd()
{
    //点击行动力 结束回合 发消息
    if( SGGuideManager::shareManager()->isGuide )
    {
        SGMainManager::preProcessDataInFightSceneForSend(1);
    }

    EFFECT_PLAY(MUSIC_BTN);
    this->boxClose();
    SGBattleManager::sharedBattle()->setCanTouchAutoBattleBtn(true);
    ((SGHeroLayer*)_target)->endRound();
}

void SGBattleRoundPromptLayer::buttonSurrender()
{
    EFFECT_PLAY(MUSIC_BTN);
//    SGStoryReward* SGStoryReward::create(int rate, int exp, int coin, int jun, CCArray *data)
    
//    ((SGHelpLayer*)_target)->runAwayRequest();
    
    this->boxClose();
    SGBattleManager::sharedBattle()->setCanTouchAutoBattleBtn(true);
    ((SGHeroLayer*)_target)->endRoundUpdataTime();
    SGAIManager::shareManager()->isBattleOver = false;
    SGBattleManager::sharedBattle()->runAwayRequest();
}



 



