# Jetpack Map Documentation

### Overview

The game map is a grid-based layout composed of rows and columns of characters.  
It can have an **infinite size**, but **each row must have the same number of characters**.  
The client will automatically scale according to the height of the map — the taller the map, the smaller the player will appear.  



### Supported Characters

| Character |        Meaning        |
|:---------:|:---------------------:|
|    `c`    |  Coin (collectible)   |
|    `e`    | Zapper trap (danger)  |
|    `l`    |  Laser trap (danger)  |
|    `m`    | Missile trap (danger) |
|    `_`    |      Empty space      |

Any **other character is not supported** and will be interpreted as an empty space.



### Example

Here's an example map (`maps/basic.txt`):
```
________ccc___ccc___________l___________________________________________________
_______c___c_c___c__________l______cccccc___________m___________________________
_______c____c____c__________l_____ccccccc___________m____________eeeeeeeeeeee___
________c_______c___________l____cc_____________________________________________
_________c_____c____________l___cc______l_________________________cccc__________
__________c___c________________cc_______l_________________________cccc__________
___________c_c___________ccccccc________l_______________________________________
____________c____________cccccc_________l_________________eeeeeeeeeeeee_________
________________________________________l_______________________________________
________________________________________________________________________________
```

- The player can move around the grid.
- Coins (`c`) can be collected.
- Zappers (`e`) are dangerous and will kill the player.
- Lasers (`l`) are dangerous and will kill the player.
- Missiles (`m`) are dangerous and will kill the player.
- Empty spaces (`_`) are traversable tiles.