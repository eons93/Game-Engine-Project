#pragma once
#include <string>
#include "Enemy.h"

std::string StringConvert(float value);

float BitConvert64(float input);

void EnemyDamage(EnemyObject &enemy, float damage);