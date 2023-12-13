#pragma once
#include <SDL.h>
#include <vector>

class RespawningEnemy {
private:
    RespawningEnemy(); // Private constructor

    static RespawningEnemy instance; // Singleton instance
    std::vector<SDL_Rect> enemyPool; // Object pool for respawning enemies

    public:
    static RespawningEnemy& getInstance();
    void initializeObjectPool(int poolSize);
    void respawnAll();
    void respawn(SDL_Rect& enemyRect);
    bool checkCollisionWithPlayer(SDL_Rect playerRect);

    const std::vector<SDL_Rect>& getObjectPool() const {
        return enemyPool;
    }
};