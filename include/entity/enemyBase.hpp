#pragma once
#include "entity.hpp"


struct EnemyStruct {
    int level = -1;
    float health = 0;
    float baseDamage = 0;
    float damageModifire = 0;
    float agression = 0;
    BaseEntity* target = nullptr;
};

class EnemyBase : public BaseEntity
{
public:
    EnemyBase();
    ~EnemyBase() = default;

    void init(int _level, float _health, float _baseDamage, float _damageModifire, float _agression);

    EnemyStruct getEnemyData();
    void setTarget(BaseEntity* _target);

    // this function should use some algorithm set an ordered array of locations (nodes) 
    void pathfind();
    // this function will move this enemy to the next node (location)
    void move();
private:
    EnemyStruct _enemyData;
};  

