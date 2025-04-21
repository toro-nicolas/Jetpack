# Jetpack Map Documentation

### Overview

The game map is a grid-based layout composed of rows and columns of characters.  
It can have an **infinite size**, but **each row must have the same number of characters**.  
The client will automatically scale according to the height of the map — the taller the map, the smaller the player will appear.  



### Supported Characters

| Character | Meaning            |
|-----------|--------------------|
| `c`       | Coin (collectible) |
| `e`       | Trap (danger)      |
| `_`       | Empty space        |

Any **other character is not supported** and will be interpreted as an empty space.



### Example

Here's an example map (`maps/basic.txt`):

```
_______c____________________e__________________________________________________________________
_______c____________________e______cccccc______________________________________________________
____________________________e_____ccccccc________________________eeeeeeeeeeee__________________
____________________________e____cc____________________________________________________________
____________________________e___cc______e_________________________cccc_________________________
_______________________________cc_______e_________________________cccc_________________________
_________________________ccccccc________e______________________________________________________
_________________________cccccc_________e_________________eeeeeeeeeeeee________________________
________________________________________e______________________________________________________
_______________________________________________________________________________________________
```

- The player can move around the grid.
- Coins (`c`) can be collected.
- Traps (`e`) should be avoided.
- Empty spaces (`_`) are traversable tiles.