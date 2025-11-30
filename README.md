**BIENVENUE DANS NOTRE NOUVEAU PROJET**

**🦒🦒 ECOSYSTEM 🦕🦕**

Pour cette implementaton, vous aurez besoin des connaissance sur:
- l'encapsulation;  
- les classes;  
- les structures;  
- les namespace;  
- les vector;  
- en programmation orientee objet

pour cela l'organisation se fera en modulaire d'où la presence des fichires tels que ecosystem.h, entity.h, gameengine.h, structs.h renderer.h et window.h selon la structure du devoir

# DEBUT DE L'IMPLEMENTATION

## ECOSYSTEM
Celui ci gere les fonctions liées aux composans de l'environnement
### ENTITY.H
ici, il etait question pour nous d'implementer les fonctions **seekfood, applyforce et avoid predators** tout en faisant certaines modifications pour la fonctionnalite du programme  
### ENTITY.CPP
#### SeekFood 
Cette fonction permet de rechercher la nourriture la plus proche selon le type de l'entite qui par la ensuite doit se diriger vers elle comme le montre le programme suivant :  


Vector2D Entity::SeekFood(const std::vector<Food>& foodSources, const std::vector<Entity>& entity) const {
    Vector2D desiredDirection(0.0f, 0.0f);
    float closestDistance = std::numeric_limits<float>::max();

    if (mType == EntityType::HERBIVORE) {
    // Chercher de la nourriture végétale
        for (const auto& food : foodSources) {
            float distance = position.Distance(food.position);
                if (distance < closestDistance) {
                    closestDistance = distance;
                    desiredDirection = Vector2D(food.position.x - position.x, food.position.y - position.y);
                }
            }
        } else if (mType == EntityType::CARNIVORE) {
            // Chercher des herbivores
            for (const auto& prey : entity) {
                if (prey.GetType() == EntityType::HERBIVORE && prey.IsAlive()) {
                    float distance = position.Distance(prey.position);
                    if (distance < closestDistance) {
                    closestDistance = distance;
                    desiredDirection = Vector2D(prey.position.x - position.x, prey.position.y - position.y);
                    }
                }
            }
        }
            
        // Normalisation de la direction  
        float length = std::sqrt(desiredDirection.x * desiredDirection.x + desiredDirection.y * desiredDirection.y);  
        if (length > 0.0f) {  
        desiredDirection.x /= length;  
        desiredDirection.y /= length;  
    }
            
    return desiredDirection ;
}

**principe** : _si le type de l'entite est l'herbivore, on parcours automatiquement toutes les plantes et on cherche celle qui est plus proche de cet herbivore puis on dirge le vecteur de l'herbivore vers cette plante d'ou l'evaluation des distance on fait donc de meme avec les carnivores en remplacant plante par herbivore puis a la fin on normalise le vecteurs obtenu_

#### AvoidPredators

Vector2D Entity::AvoidPredators(const std::vector<Entity>& predators) const {  
Vector2D fleeDirection(0.0f, 0.0f);  

    if (mType != EntityType::HERBIVORE) {  
        return fleeDirection;  // Seuls les herbivores évitent les prédateurs  
    }  

    for (const auto& predator : predators) {  
        if (predator.IsAlive() && predator.GetType() == EntityType::CARNIVORE) {  
            float distance = position.Distance(predator.position);  
            if (distance < 50.0f) {  // Seuil de détection  
                fleeDirection.x += position.x - predator.position.x;  
                fleeDirection.y += position.y - predator.position.y;  
            }  
        }  
    }  

    // Normalisation de la direction  
        float length = std::sqrt(fleeDirection.x * fleeDirection.x + fleeDirection.y * fleeDirection.y);  
    if (length > 0.0f) {  
        fleeDirection.x /= length;  
        fleeDirection.y /= length;  
    }  
            
    return fleeDirection;  
}  

**principe** : _ici c'est plus base sur les herbivores qui doivent essayer de fuire les carnivores loosque ces derniers s'approchent d'eux car les plantes ne bougent pas pour fuire le predateur on se base toujours sur la direction puis on normalise le vecteur_

#### applyForce 

comme l'indique son nom si bien, elle permet d'appliquer la force sur une entite comme suit  

void Entity::ApplyForce(Vector2D force){  

    mVelocity.x += force.x ;  
    mVelocity.y += force.y ;  
}  
        
elle permettra de simuler une augmentation la vitesse a peu pres 

### ECOSYSTEM

ici, les fonctions a implementer etaient **add entity et addfood**  

#### AddEntity
void Ecosystem::AddEntity(std::unique_ptr<Entity> entity){  
    if (mEntities.size() < mMaxEntities) return ;  
    else mEntities.push_back(std::move(entity)) ;  
}
**principe** : _elle permet juste d'augmenter les entites_

#### AddFood 

void Ecosystem::AddFood(Vector2D position, float energy){  
    Food new_food(position, energy) ;  
    if (mEntities.size() >= mMaxEntities) return;  
    else{  
        mFoodSources.push_back(new_food); // a travers le std::vector <food> mfoodsources , on ajoute la nouvelle nourriture cree   
    }  
}  

**principe :** _ce dernier permet d'ajouter des nourriture qui seront consommes selon le type de l'entite_
je vous conseille de lire le reste des fonctions implementes et surtout n'hesitez pas a me poser des questions en cas de non comprehension du programme  

**NB:** Pour la compilation, il faut utiliser :  
g++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp -lSDL3  

Quant a l'execution, il faut faire comme d'habitude  
./ecosystem