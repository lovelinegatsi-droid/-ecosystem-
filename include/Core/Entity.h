#pragma once 
#include "Structs.h" 
#include <SDL3/SDL.h> 
#include <memory> 
#include <random> 
#include <vector> 
namespace Ecosystem { 
namespace Core { 
// ÉNUMÉRATION DES TYPES D'ENTITÉS 
enum class EntityType { 
    HERBIVORE, 
    CARNIVORE, 
    PLANT 
}; 
class Entity { 
private: 
    // DONNÉES PRIVÉES - État interne protégé 
    float mEnergy; //est le niveau d'energie actuel des entites
    float mMaxEnergy; //qui est l'energie maximale que peut atteindre une entite
    int mAge; // age actuel (frame ou cycle ) de l'entite
    int mMaxAge; // temps de vie maximal
    bool mIsAlive; // est ce que l'entite est vivante
    Vector2D mVelocity; // vitesse definie par un vecteur pour la direction et la rapidite
    EntityType mType; // variable de choix de l'entite
    
    // Générateur aléatoire 
    mutable std::mt19937 mRandomGenerator; // choix ou comportement aleatoire de l'entite
public: 
    // DONNÉES PUBLIQUES - Accès direct sécurisé 
    Vector2D position; // position actuel de l'entite
    Color color; // couleur de l'entit selon le type
    float size; // taille de l'entite
    std::string name; // nom de l'entite
    
    // CONSTRUCTEURS 
    Entity(EntityType type, Vector2D pos, std::string entityName = "Unnamed"); 
    Entity(const Entity& other);  // Constructeur de copie 
    
    // DESTRUCTEUR 
    ~Entity(); 
    
    //MÉTHODES PUBLIQUES 
    void Update(float deltaTime); 
    void Move(float deltaTime); 
    void Eat(float energy); 
    bool CanReproduce() const; 
    std::unique_ptr<Entity> Reproduce(); 
    void ApplyForce(Vector2D force); 
    
    // GETTERS - Accès contrôlé aux données privées 
    float GetEnergy() const { return mEnergy; } 
    float GetEnergyPercentage() const { return mEnergy / mMaxEnergy; } 
    int GetAge() const { return mAge; } 
    bool IsAlive() const { return mIsAlive; } 
    EntityType GetType() const { return mType; } 
    Vector2D GetVelocity() const { return mVelocity; } 
    
    // MÉTHODES DE COMPORTEMENT 
    Vector2D SeekFood(const std::vector<Food>& foodSources, const std::vector<Entity>& mtype) const; 
    Vector2D AvoidPredators(const std::vector<Entity>& predators) const; 
    Vector2D StayInBounds(float worldWidth, float worldHeight); 
    
    // MÉTHODE DE RENDU 
    void Render(SDL_Renderer* renderer) const; 
private: 
    // MÉTHODES PRIVÉES - Logique interne 
    void ConsumeEnergy(float deltaTime); 
    void Age(float deltaTime); 
    void CheckVitality(); 
    Vector2D GenerateRandomDirection(); 
    Color CalculateColorBasedOnState() const; 
}; 
} // namespace Core 
} // namespace Ecosystem