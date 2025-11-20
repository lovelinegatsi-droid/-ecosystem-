#pragma once 
#include "../Graphics/Window.hpp" 
#include "Ecosystem.hpp" 
#include <chrono> 
namespace Ecosystem { 
namespace Core { 
class GameEngine { 
private: 
    // 
�
�
 ÉTAT DU MOTEUR 
    Graphics::Window mWindow; 
    Ecosystem mEcosystem; 
    bool mIsRunning; 
    bool mIsPaused; 
    float mTimeScale; 
     
    // ⏱ CHRONOMÉTRE 
    std::chrono::high_resolution_clock::time_point mLastUpdateTime; 
    float mAccumulatedTime; 
public: 
    // 🏗 CONSTRUCTEUR 
    GameEngine(const std::string& title, float width, float height); 
     
    // 
⚙
 MÉTHODES PRINCIPALES 
    bool Initialize(); 
    void Run(); 
    void Shutdown(); 
     
    // 
�
�
 GESTION D'ÉVÉNEMENTS 
    void HandleEvents(); 
    void HandleInput(SDL_Keycode key); 
private: 
    // 
�
�
 MÉTHODES INTERNES 
    void Update(float deltaTime); 
    void Render(); 
    void RenderUI(); 
}; 
} // namespace Core 
} // namespace Ecosystem 