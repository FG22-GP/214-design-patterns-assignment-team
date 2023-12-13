#include "RespawningEnemy.h"
#include <cstdlib>
#include <ctime>

RespawningEnemy RespawningEnemy::instance; 

RespawningEnemy& RespawningEnemy::getInstance() {
    return instance;
}

RespawningEnemy::RespawningEnemy() {}

void RespawningEnemy::initializeObjectPool(int poolSize) {
    enemyPool.resize(poolSize);
    respawnAll(); 
}

void RespawningEnemy::respawnAll() {
    for (SDL_Rect& enemyRect : enemyPool) {
        respawn(enemyRect);
    }
}

void RespawningEnemy::respawn(SDL_Rect& enemyRect) {
    // Respawn at a random position
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int enemySize = 100;

    enemyRect.x = rand() % (screenWidth - enemySize);
    enemyRect.y = rand() % (screenHeight - enemySize);
    enemyRect.w = enemySize;
    enemyRect.h = enemySize;
}

bool RespawningEnemy::checkCollisionWithPlayer(SDL_Rect playerRect) {
    bool collisionDetected = false;

    for (SDL_Rect& enemyRect : enemyPool) {
        if (SDL_HasIntersection(&enemyRect, &playerRect)) {
            respawn(enemyRect);
            collisionDetected = true;
        }
    }

    return collisionDetected;
}