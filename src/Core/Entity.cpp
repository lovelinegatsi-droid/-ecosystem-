#include "Core/Entity.h" 
#include <cmath> 
#include <iostream> 
#include <algorithm> 
//#include "Structs.h"
namespace Ecosystem { 
namespace Core { 
// 🏗 CONSTRUCTEUR PRINCIPAL 
Entity::Entity(EntityType type, Vector2D pos, std::string entityName) 
    : mType(type), position(pos), name(entityName),  
      mRandomGenerator(std::random_device{}())  // Initialisation du générateur aléatoire
{ 
    //INITIALISATION SELON LE TYPE 
    //
    switch(mType) { 
        case EntityType::HERBIVORE: 
            mEnergy = 80.0f; 
            mMaxEnergy = 150.0f; 
            mMaxAge = 200; 
            color = Color::Blue(); 
            size = 8.0f; 
            break; 
        case EntityType::CARNIVORE: 
            mEnergy = 100.0f; 
            mMaxEnergy = 200.0f; 
            mMaxAge = 150; 
            color = Color::Red(); 
            size = 12.0f; 
            break; 
        case EntityType::PLANT: 
            mEnergy = 50.0f; 
            mMaxEnergy = 100.0f; 
            mMaxAge = 300; 
            color = Color::Green(); 
            size = 6.0f; 
            break; 
    }
    mAge = 0; 
    mIsAlive = true; 
    mVelocity = GenerateRandomDirection(); 
    std::cout << "🌱 Entité créée: " << name << " à (" << position.x << ", " << position.y << ")";
} 

// 🏗 CONSTRUCTEUR DE COPIE 
Entity::Entity(const Entity& other) 
    : mType(other.mType), position(other.position), name(other.name + "_copy"), 
      mEnergy(other.mEnergy * 0.7f),  // Enfant a moins d'énergie 
      mMaxEnergy(other.mMaxEnergy), 
      mAge(0),  // Nouvelle entité, âge remis à 0 
      mMaxAge(other.mMaxAge), 
      mIsAlive(true), 
      mVelocity(other.mVelocity), 
      color(other.color), 
      size(other.size * 0.8f),  // Enfant plus petit 
      mRandomGenerator(std::random_device{}()) 
    { 
 
    std::cout << " 👶 Copie d'entité créée: " << name << std::endl; 
}
// 🗑 DESTRUCTEUR 
Entity::~Entity() { 
    std::cout << "💀Entité détruite: " << name << " (Âge: " << mAge << ")" << std::endl;
 } 

 //MISE À JOUR PRINCIPALE 
void Entity::Update(float deltaTime) { 
    if (!mIsAlive) return; 
    
    //PROCESSUS DE VIE 
    ApplyForce(SeekFood(positi)) ;   
    ConsumeEnergy(deltaTime); 
    Age(deltaTime); 
    Move(deltaTime); 
    CheckVitality(); 
} 

//MOUVEMENT 
void Entity::Move(float deltaTime) { 
    const std::vector<Food> mfoodsource;
    Vector2D rapproche = Entity::SeekFood(mfoodsource);
    if (mType == EntityType::PLANT) return;  // Les plantes ne bougent pas 

    //Comportement aléatoire occasionnel 
    std::uniform_real_distribution<float> chance(0.0f, 1.0f); 
    if (chance(mRandomGenerator) < 0.02f) { 
        mVelocity = GenerateRandomDirection(); 
    }

    //Application du mouvement
    StayInBounds(1200, 600) ;

    if(mEnergy < 60){
        position = position + rapproche * deltaTime * 0.50f ; // on multiplie pas 0.5 pour diminuer la gravite et les faire avance de maniere fluide lorsqu'ils voient la proie
        if(position.x <= rapproche.x && position.y <= rapproche.y) {
            Eat(mEnergy) ;
        }
    }
    
    position = position + mVelocity * deltaTime * 20.0f; 
    
    // Consommation d'énergie due au mouvement 
    mEnergy -= mVelocity.Distance(Vector2D(0, 0)) * deltaTime * 0.1f; 
} 

//retourner l'entite vers la proie ou la nourriture la plus proche 
Vector2D Entity::SeekFood(const std::vector<Food>& foodSources) const {

    const float To_eat = 10.0f ;
    Vector2D Near_Of_Food ; // qui est pour localiser la proie la plus proche de son devoreur
    Vector2D direction(0,0) ; // qui est le vecteur que retournera la fonction
    // on initialise d'abord la distance minimale a la plus grande distance qu'il peut avoir entre l'entite et sa proie

    float dist_minimale = std::numeric_limits<float>::max();
    for(const auto& etre : foodSources){
        float d = position.Distance(etre.position); // on calcule la distance entre le devoreur et la proie
        if (d <= dist_minimale){
            dist_minimale = d ; // on remet la distance minimale a celle encore plus petite qu'elle afin de trouver la proie la plus proche
            Near_Of_Food = etre.position ; // on affecte a la proie la plus proche la nouvelle position
        }

        direction.x = Near_Of_Food.x - position.x;
        direction.y = Near_Of_Food.y - position.y ;
    }

    return direction;
}

// 🍽 MANGER
void Entity::Eat(float energy) { 
    mEnergy += energy; 
    if (mEnergy > mMaxEnergy) { 
        mEnergy = mMaxEnergy; 
    } 
    std::cout << "🍽 " << name << " mange et gagne " << energy << " énergie" << std::endl;
}

// implementation de la fonction permettant d'eviter les predateurs
Vector2D Entity::AvoidPredators(const std::vector<Entity>& predators) const {
    
    Vector2D change_direction ;
    float dist;
    const float dist_H = 30.0f;
    switch(mType){
        case EntityType::HERBIVORE:
        for(const auto& danger : predators){
            dist = position.Distance(danger.position) ;
            if(dist < dist_H) {
                change_direction.x = -mVelocity.x ;
                change_direction.y = -mVelocity.y;
            }
        }
    }
    return change_direction ;
}

// implementation de celle permettant d'appliquer une force
void Entity::ApplyForce(Vector2D force){

    mVelocity.x += force.x ;
    mVelocity.y += force.y ;
}
 
//CONSOMMATION D'ÉNERGIE 
void Entity::ConsumeEnergy(float deltaTime) { 
    float baseConsumption = 0.0f; 
    switch(mType) { 
        case EntityType::HERBIVORE: 
            baseConsumption = 1.5f; 
            break; 
        case EntityType::CARNIVORE: 
            baseConsumption = 2.0f; 
            break; 
        case EntityType::PLANT: 
            baseConsumption = -0.5f;  // Les plantes génèrent de l'énergie ! 
            break; 
    }
    mEnergy -= baseConsumption * deltaTime; 
} 

// VIEILLISSEMENT 
void Entity::Age(float deltaTime) { 
    mAge += static_cast<int>(deltaTime * 10.0f);  // Accéléré pour la simulation 
} 

// ❤VÉRIFICATION DE LA SANTÉ 
void Entity::CheckVitality() { 
    if (mEnergy <= 0.0f || mAge >= mMaxAge) { 
        mIsAlive = false; 
        std::cout << "💀 " << name << " meurt - "; 
        if (mEnergy <= 0) std::cout << "Faim"; 
        else std::cout << "Vieillesse"; 
        std::cout << std::endl; 
    }
 } 

 // REPRODUCTION 
bool Entity::CanReproduce() const { 
    return mIsAlive && mEnergy > mMaxEnergy * 0.8f && mAge > 20; 
} 
std::unique_ptr<Entity> Entity::Reproduce() { 
    if (!CanReproduce()) return nullptr; 
    
    // Chance de reproduction 
    std::uniform_real_distribution<float> chance(0.0f, 1.0f); 
    if (chance(mRandomGenerator) < 0.3f) { 
    }
        mEnergy *= 0.6f;  // Coût énergétique de la reproduction 
        return std::make_unique<Entity>(*this);  // Utilise le constructeur de copi
    return nullptr; 
} 

// GÉNÉRATION DE DIRECTION ALÉATOIRE 
Vector2D Entity::GenerateRandomDirection() { 
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f); 
    return Vector2D(dist(mRandomGenerator), dist(mRandomGenerator)); 
} 

// CALCUL DE LA COULEUR BASÉE SUR L'ÉTAT 
Color Entity::CalculateColorBasedOnState() const { 
    float energyRatio = GetEnergyPercentage(); 
    Color baseColor = color; 
    
    // Rouge si faible énergie 
    if (energyRatio < 0.3f) { 
        baseColor.r = 255; 
        baseColor.g = static_cast<uint8_t>(baseColor.g * energyRatio); 
        baseColor.b = static_cast<uint8_t>(baseColor.b * energyRatio); 
    }
    return baseColor; 
} 

// RENDU GRAPHIQUE 
void Entity::Render(SDL_Renderer* renderer) const { 
    if (!mIsAlive) return; 
    Color renderColor = CalculateColorBasedOnState(); 
    SDL_FRect rect = { 
        position.x - size / 2.0f, 
        position.y - size / 2.0f, 
        size, 
        size 
    }; 
    SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(renderer, &rect); 
    
    // Indicateur d'énergie (barre de vie) 
    if (mType != EntityType::PLANT) { 
        float energyBarWidth = size * GetEnergyPercentage(); 
        SDL_FRect energyBar = { 
            position.x - size / 2.0f, 
            position.y - size / 2.0f - 3.0f, 
            energyBarWidth, 
            2.0f 
        };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &energyBar); 
    }
} 

// Implementation de la fonction permettant de rester dans les environs
Vector2D Entity::StayInBounds(float worldWidth, float worldHeight) {
    switch (mType){
    case EntityType::HERBIVORE:
        if(position.x < 0) position.x = 0 ;
        if(position.y < 0) position.y = 0 ;
        if(position.x > worldWidth) position.x = worldWidth ;
        if(position.y > worldHeight) position.y = worldHeight ;
    break;
    case EntityType::CARNIVORE :
        if(position.x < 0) position.x = 0 ;
        if(position.y < 0) position.y = 0 ;
        if(position.x > worldWidth ) position.x = worldWidth;
        if(position.y > worldHeight) position.y = worldHeight;
    break; 
    }

    return position ;
};

} // namespace Core 
} // namespace Ecosystem