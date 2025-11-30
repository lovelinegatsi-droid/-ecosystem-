** BIENVENUE DANS NOTRE NOUVEAU PROJET **

** 🦒🦒 ECOSYSTEM 🦕🦕 **

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
### ECOSYSTEM.H
ici, il etait question pour nous d'implementer les fonctions **seekfood, applyforce et avoid predators ** tout en faisant certaines modifications pour la fonctionnalite du programme  
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

