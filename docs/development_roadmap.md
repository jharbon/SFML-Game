# Development Roadmap

**Legend**:

- ✅ Completed  
- 📌 Planned

## Phase 1: Rendering and Player Mechanics 

- [✅] Render a basic window and shape to test the SFML setup
- [✅] Design and render a basic player character sprite
- [📌] Design and render a basic tile-based level for testing
- [📌] Axis-Aligned Bounding Box (AABB) collision detection
- [📌] Receive and configure input from keyboard and joystick controller 
- [📌] Basic movements (run, jump and climb) and collision detections with floors, walls and ladders 
- [📌] Side-scrolling camera  
- [📌] Melee attack hitbox  
- [📌] Render projectile sprite and implement its dynamics 
- [📌] Ranged attack using projectiles
- [📌] Dash and wall-jump
- [📌] Render charged projectile and implement charged ranged attack
- [📌] Config file to store constants relevant to game physics and player mechanics

## Phase 2: Enemy Mechanics and AI

- [📌] Design and render an enemy sprite 
- [📌] Enemy melee and ranged attacks 
- [📌] Collision detections for player-enemy melee and ranged attacks
- [📌] Enemy behaviour states: idle, static with ranged attack, patrol with melee
and/or ranged attack, and chase with melee and/or ranged attack
- [📌] Hierarchical Finite State Machine (HFSM) and transitions between behaviour states

## Phase 3: Progression System and Meters

- [📌] Render player score text in the bottom left of the window
- [📌] Render coin sprites in fixed positions and implement player-coin collision detection for collection  
- [📌] Increase player score whenever enemies are destroyed or fixed-position coins are collected
- [📌] Render player health meter in the bottom left of the window and render each enemy health meter above the corresponding sprite. Health decreases when hit by a melee or ranged attack. Fully depleted health results in game over for the player and destruction for an enemy respectively
- [📌] Render player armour meter in the bottom left of the window. Armour decreases when hit by a ranged attack. The presence of armour decreases the amount of health the player loses from each ranged attack
- [📌] Render player charge meter in the bottom left of the window. Charge increases each time the player hits an enemy with a melee or ranged attack. A full charge meter allows the player to use one charged ranged attack and then the meter resets to empty  