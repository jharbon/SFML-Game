# Game Outline

## Technical Overview

- **Language**: C++
- **Rendering Engine**: SFML
- **Unit-Test Framework**: Google Test
- **Platforms**: Linux and Windows

## Mechanics

- **Player**
    - **Moves**: horizontal run, vertical jump, and climb
    - **Special Moves**: dash and wall-jump
    - **Attack Types**: melee and ranged
    - **Attack Directions**: horizontal and vertical
    - **Special Attacks**: charged ranged shot 
    - **Meters**: health, armour, and charge 
    - **Health Loss**: melee, ranged, trap, and fall into gap

- **Enemy**
    - **Behaviour States**: idle, static with ranged attack, patrol with melee
      and/or ranged attack, and chase with melee and/or ranged attack
    - **Attack Types**: melee and ranged
    - **Attack Directions**: horizontal and vertical
    - **AI**: Hierarchical Finite State Machine (HFSM)
    - **Meters**: health

- **Level**
    - **Design**: tile-based 
    - **Hazards**: cacti, gaps, and moving platforms   
    - **Pickup Items**: armour, coins, and health 

- **Camera**
    - **Perspective**: 2D side-scroller 
    - **Lock Trigger**: player position in special areas for combat and/or
      platforming challenges

## Progression

- **Win Condition**: Reach the end of the level
- **Game Over Condition**: Health fully depleted
- **Scoring**: destroy enemies and collect fixed-position coins