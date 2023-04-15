#pragma once
#include "monster.h"
#include "global.h"
#include "linkedListForMonster.h"
// #include <time.h>
const short Num_of_MonsterArray1=5;
const short Num_of_MonsterArray2=5;
const short Num_of_MonsterArray3=2;
const short Num_of_MonsterArray4=1;
const short Num_of_MonsterArray5=3;
const short Num_of_MonsterArray6=4;

void initArrayMonster();
void monsterType_1();
void monsterType_2();
void monsterType_3();
void monsterType_4();
void monsterType_5();
void monsterType_6();
void boss();
void GenerateMonster(monsterList *l);
//=========================================================================
void monsterType_1()
{
    for(int i = 0; i < Num_of_MonsterArray1; i++)
    {
        monster *monster1 = (monster*)malloc(sizeof(monster));
        initMonster(monster1);
        monster1->hp = 2;
        monster1->type = 1;
        monster1->x_pos = displayMode.w/2-(monster1->Width)/2+100*(i-2);
        monster1->y_pos = (-85*2-25*i);
        monster1->y_limit = 10;
        monster1->speed = 5;
        monster1->score = 100;
        loadMonster(monster1);
        node_M* newNode = createNode(*monster1);
        push_back(lm,newNode);
    }
    for(int i = 0; i < Num_of_MonsterArray1; i++)
    {
        monster *monster2 = (monster*)malloc(sizeof(monster));
        initMonster(monster2);
        monster2->hp = 4;
        monster2->type = 1;
        monster2->x_pos = displayMode.w/2-(monster2->Width)/2+100*(i-2);
        monster2->y_pos = (-85-25*i);
        monster2->y_limit = 350;
        monster2->speed = 4;
        monster2->score = 100;
        loadMonster(monster2);
        node_M* newNode = createNode(*monster2);
        push_back(lm,newNode);
    }
}
void monsterType_2()
{
    for(int i = 0; i < Num_of_MonsterArray2; i++)
    {
        monster *monster1 = (monster*)malloc(sizeof(monster));
        initMonster(monster1);
        
        monster1->hp = 2;
        monster1->type = 2;
        monster1->x_pos = -85;
        monster1->y_pos = displayMode.w/5-(monster1->height)/2+100*(i-1.5);
        monster1->y_limit = 300;
        monster1->x_limit = 200;
        monster1->speed = 2;
        monster1->score = 150;
        loadMonster(monster1);
        node_M* newNode = createNode(*monster1);
        push_back(lm,newNode);
    }
    for(int i = 0; i < Num_of_MonsterArray2; i++)
    {
        monster *monster2 = (monster*)malloc(sizeof(monster));
        initMonster(monster2);
        monster2->hp = 2;
        monster2->type = 7;
        monster2->x_pos = displayMode.w+85;
        monster2->y_pos = displayMode.w/5-(monster2->height)/2+100*(i-1.5);
        monster2->y_limit = 300;
        monster2->x_limit = 200;
        monster2->speed = 2;
        monster2->score = 150;
        loadMonster(monster2);
        node_M* newNode = createNode(*monster2);
        push_back(lm,newNode);
    }
}
void monsterType_3()
{
    for(int i=0;i<Num_of_MonsterArray3;i++)
    {
        monster *monster1 = (monster*)malloc(sizeof(monster));
        initMonster(monster1);
        
        monster1->hp = 5;
        monster1->type = 3 ;
        monster1->x_pos = (displayMode.w/2-(monster1->Width)/2+200*(i-0.5));
        monster1->y_pos = -85;
        monster1->speed = 1;
        monster1->y_limit = 150;
        monster1->score = 200;
        loadMonster(monster1);
        node_M* newNode = createNode(*monster1);
        push_back(lm,newNode);
    }
}
void monsterType_4()
{
     for(int i=0;i<Num_of_MonsterArray4;i++)
    {
        monster *monster_ = (monster*)malloc(sizeof(monster));
        initMonster(monster_);
        monster_->hp = 30;
        monster_->type = 4;
        monster_->x_pos = (displayMode.w/2-monster_->Width/2-10+i*3)+10;
        monster_->y_pos = -85;
        monster_->Width = 91;
        monster_->height = 116;
        monster_->y_limit = 100;
        monster_->speed = 7;
        monster_->score = 300;
        loadMonster(monster_);
        node_M* newNode = createNode(*monster_);
        push_back(lm,newNode);
    }
}
void monsterType_5()
{
    for(double i=0;i<Num_of_MonsterArray5;i++)
    {
        for(double j=0;j<Num_of_MonsterArray5-i;j++)
        {
            monster *monster_ = (monster*)malloc(sizeof(monster));
            initMonster(monster_);
            monster_->hp = 3;
            monster_->type = 5;
            monster_->x_pos = (displayMode.w/2-(monster_->Width)/2+200*(j-(3-i)/2+0.5));
            monster_->y_pos = (-85*3+85*i);
            monster_->speed = 2;
            monster_->y_limit = (100+100*i);
            monster_->score = 280;
            loadMonster(monster_);
            node_M* newNode = createNode(*monster_);
            push_back(lm,newNode);
        }
    }
}
void monsterType_6()
{
    for(int j = 0; j < 2; j++)
    {
        for(int i=0;i<Num_of_MonsterArray6;i++)
        {
            
            monster *monster_ = (monster*)malloc(sizeof(monster));
            initMonster(monster_);
            monster_->type = 6;
            monster_->hp = 6;
            monster_->score = 210;
            if(i%2==0)
            {
                monster_->x_pos = (displayMode.w/2-(monster_->Width)/2+100*(i-1)+400*(j-0.5));
                monster_->y_pos = (-monster_->height);
                monster_->y_limit = 200;
                monster_->speed = 2;
            }
            else
            {
                monster_->x_pos = (displayMode.w/2-(monster_->Width)/2+400*(j-0.5));
                monster_->y_pos = (-monster_->height+100*(i-2));
                monster_->y_limit = 0+100*i;
                monster_->speed = 2;
            }
            loadMonster(monster_);
            node_M* newNode = createNode(*monster_);
            push_back(lm,newNode);
        }
    }
}
void boss()
{
// ===================== danh cho boss ======================
    monster *boss_ = (monster*)malloc(sizeof(monster));
    initMonster(boss_);
    boss_->type = 10;
    boss_->hp = 500;
    boss_->height = 300;
    boss_->Width = 300;
    boss_->y_pos = - boss_->Width;
    boss_->x_pos = (displayMode.w / 2 - (boss_->Width/2));
    boss_->y_limit = 50;
    boss_->speed = 2;
    boss_->score = 10000;
    loadMonster(boss_);
    node_M* newNode = createNode(*boss_);
    push_back(lm,newNode); 
}
void GenerateMonster(monsterList *l)
{
    
    if(l->size <= 0)
    {
        
        wave+=1;
        if(wave%10!=0)
        {
            srand(time(0));
            short random=rand() % 9 +1;
            if(random==1)
            {
                monsterType_2();
            }
            else if(random==2)
            {
                monsterType_6();
            }
            else if(random==3)
            {
                monsterType_2();
                monsterType_3();
            }
            else if(random==4)
            {
                monsterType_4();
            }
            else if(random==5)
            {
                monsterType_1();
                monsterType_5();
            }
            else if(random==6)
            {
                monsterType_2();
                monsterType_5();
            }
            else if(random==7)
            {
                monsterType_1();
            }
            else if(random==8)
            {
                monsterType_1();
                monsterType_6();
            }else if(random == 9)
            {
                monsterType_3();
                monsterType_1();
            }
        }
        else
        {
            boss();
        }

    }
}