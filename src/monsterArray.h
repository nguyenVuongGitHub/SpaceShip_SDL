#pragma once
#include "monster.h"
#include "global.h"
#include "linkedListForMonster.h"
const int Num_of_MonsterArray1=5;
const int Num_of_MonsterArray2=4;
const int Num_of_MonsterArray3=2;
const int Num_of_MonsterArray4=1;
const int Num_of_MonsterArray5=3;
const int Num_of_MonsterArray6=1;

void initArrayMonster();
void monsterType_1();
void monsterType_2();
void monsterType_3();
void monsterType_4();
void monsterType_5();
void monsterType_6();
void GenerateMonster();
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
        monster1->y_pos = 25*i;
        loadMonster(monster1);
        node* newNode = createNode(*monster1);
        push_back(l,newNode);
    }
    for(int i = 0; i < Num_of_MonsterArray1; i++)
    {
        monster *monster2 = (monster*)malloc(sizeof(monster));
        initMonster(monster2);
        monster2->hp = 2;
        monster2->type = 1;
        monster2->x_pos = displayMode.w/2-(monster2->Width)/2+100*(i-2);
        monster2->y_pos = 25*i;
        loadMonster(monster2);
        node* newNode = createNode(*monster2);
        push_back(l,newNode);
    }
}
void monsterType_2()
{
    for(int i = 0; i < Num_of_MonsterArray2; i++)
    {
        monster *monster1 = (monster*)malloc(sizeof(monster));
        initMonster(monster1);
        
        monster1->hp = 3;
        monster1->type = 2;
        monster1->x_pos = 10;
        monster1->y_pos = displayMode.w/3-(monster1->height)/2+100*(i-1.5);
        loadMonster(monster1);
        node* newNode = createNode(*monster1);
        push_back(l,newNode);
    }
    for(int i = 0; i < Num_of_MonsterArray2; i++)
    {
        monster *monster2 = (monster*)malloc(sizeof(monster));
        initMonster(monster2);
        
        monster2->hp = 3;
        monster2->type = 2;
        monster2->x_pos = displayMode.w/2;
        monster2->y_pos = displayMode.w/3-(monster2->height)/2+100*(i-1.5);
        loadMonster(monster2);
        node* newNode = createNode(*monster2);
        push_back(l,newNode);
    }
}
void monsterType_3()
{
    for(int i=0;i<Num_of_MonsterArray3;i++)
    {
        monster *monster1 = (monster*)malloc(sizeof(monster));
        initMonster(monster1);
        
        monster1->hp = 3;
        monster1->type = 3 ;
        // monster1->height = 64;
        // monster1->Width = 64;
        monster1->x_pos = (displayMode.w/2-(monster1->Width)/2+200*(i-0.5));
        monster1->y_pos = 30;
        loadMonster(monster1);
        node* newNode = createNode(*monster1);
        push_back(l,newNode);
    }
}
void monsterType_4()
{
     for(int i=0;i<Num_of_MonsterArray4;i++)
    {
        monster *monster_ = (monster*)malloc(sizeof(monster));
        initMonster(monster_);
        monster_->hp = 1;
        monster_->type = 4;
        monster_->x_pos = (rand()%(650-monster_->Width-150+1)+150);
        monster_->y_pos = 85;
        loadMonster(monster_);
        node* newNode = createNode(*monster_);
        push_back(l,newNode);
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
            monster_->y_pos = 85*i ;
            loadMonster(monster_);
            node* newNode = createNode(*monster_);
            push_back(l,newNode);
        }
    }
}
void monsterType_6()
{
   for(int i=0;i<4;i++)
    {
        monster *monster_ = (monster*)malloc(sizeof(monster));
        initMonster(monster_);
        monster_->type = 6;
        monster_->hp = 6;
        if(i%2==0)
        {
            monster_->x_pos = (displayMode.w/2-(monster_->Width)/2+100*(i-1));
            monster_->y_pos = (-monster_->height);
        }
        else
        {
            monster_->x_pos = (displayMode.w/2-(monster_->Width)/2);
            monster_->y_pos = (-monster_->height+100*(i-2));
        }
        loadMonster(monster_);
        node* newNode = createNode(*monster_);
        push_back(l,newNode);
    }
}

void GenerateMonster(monsterList *l)
{
    
    if(l->size <= 0)
    {
        
        wave+=1;
        if(wave%10!=0)
        {
            int random=8;
            printf("radom = %d\n",random);
            if(random==1)
            {
                monsterType_1();
            }
            else if(random==2)
            {
                monsterType_2();
            }
            else if(random==3)
            {
                monsterType_2();
                monsterType_3();
            }
            else if(random==4)
            {
                monsterType_2();
                monsterType_4();
            }
            else if(random==5)
            {
                monsterType_5();
            }
            else if(random==6)
            {
                monsterType_2();
                monsterType_5();
            }
            else if(random==7)
            {
                monsterType_6();
                monsterType_2();
            }
            else if(random==8)
            {
                monsterType_2();
                monsterType_1();
            }
        }
        // else
        // {
        //     EnemyBoss();
        // }

    }
}