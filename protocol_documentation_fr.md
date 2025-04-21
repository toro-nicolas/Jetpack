# Jetpack Protocol Documentation

Chaque réponse du serveur suit le format suivant :
```
ID_cmd code_retour DATA
```
où :
- `ID_cmd` : identifiant de la commande envoyée, selon le std::to_string de l'enum suivante :
```cpp
    enum CmdID {
        CMD_ID_NOT_FOUND = -1,
        CMD_ID_ID = 0,
        CMD_MAP_ID = 1,
        CMD_PSEUDO_ID = 2,
        CMD_MOVE_ID = 3,
        CMD_CLIENTS_NB_ID = 4,
        CMD_CLIENTS_STATS_ID = 5,
        CMD_CLIENTS_POSITIONS_ID = 6,
    };
```

---

### 🗺️ GAME LOAD

> Chaque "donnée"  renvoyée par le serveur est séparée par un ' ' (espacement)

Cette catégorie de commandes est dédiée à charger la carte et les informations initiales du client.

| Commande envoyée par le client | Réponse du serveur                  |
|--------------------------------|-------------------------------------|
| `MAP`                          |                                     |
|                                | *(CMD_MAP_ID)*                      |
|                                | Code retour : `201` / `501`         |
|                                | DATA : `Données brutes de la carte` |
| `ID`                           |                                     |
|                                | *(CMD_ID_ID)*                       |
|                                | Code retour : `201` / `501`         |
|                                | DATA : `id` du client côté serveur  |

---

### 👥 CLIENTS INFORMATIONS

> Chaque "donnée"  renvoyée par le serveur est séparée par un ' ' (espacement)

Cette catégorie de commandes est dédiée à récupérer les informations sur TOUS les clients connectés au serveur.

| Commande envoyée par le client                                                              | Réponse du serveur                        |
|---------------------------------------------------------------------------------------------|-------------------------------------------|
| `CLIENTS_NB`                                                                                |                                           |
|                                                                                             | *(CMD_CLIENTS_NB_ID)*                     |
|                                                                                             | Code retour : `202` / `502`               |
|                                                                                             | DATA : `3` *(nombre de clients)*          |
| `CLIENTS_POSITIONS`                                                                         |                                           |
|                                                                                             | *(CMD_CLIENTS_POSITIONS_ID)*              |
|                                                                                             | Code retour : `202` / `502`               |
|                                                                                             | DATA : `id1:x,y\|id2:x,y\|...`            |
| `CLIENTS_STATS`                                                                             |                                           |
|                                                                                             | *(CMD_CLIENTS_STATUS_ID)*                 |
|                                                                                             | Code retour : `202` / `502`               |
| `pseudo` = pseudo du client <br>`bool` client vivant/mort <br> `size_t` score du client<br> | DATA : `id1:pseudo,0,34\|id2:status\|...` |

---

### 🎮 PERSONAL CLIENT CMD

> Chaque "donnée"  renvoyée par le serveur est séparée par un ' ' (espacement)

Cette catégorie de commandes est dédiée à envoyer des commandes au serveur, qui sont spécifiques à un client.

| Commande envoyée par le client                | Réponse du serveur                                          |
|-----------------------------------------------|-------------------------------------------------------------|
| `PSEUDO MonPseudo`                            |                                                             |
| `MonPseudo` étant le nouveau pseudo à choisir | *(CMD_PSEUDO_ID)*                                           |
|                                               | Code retour : `203` / `503`                                 |
|                                               | DATA : `MonPseudo` = nouveau pseudo enregistré côté serveur |
| `MOVE direction`                              |                                                             |
| `direction` étant seulement `UP` ou `DOWN`    | *(CMD_MOVE_ID)*                                             |
|                                               | Code retour : `203` / `503`                                 |
|                                               | DATA : `OK` ou message d’erreur                             |
