# Jetpack  Protocol Documentation

Each server response follows this format:
```
ID_cmd return_code DATA
```
Where:
- `ID_cmd`: Command identifier sent by the client, as defined by the `std::to_string` of the following enum:
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

> Each piece of server data is separated by a space character `' '`

This category includes commands for loading the game map and the client’s initial information.

| Command sent by client | Server response                           |
|------------------------|-------------------------------------------|
| `MAP`                  |                                           |
|                        | *(CMD_MAP_ID)*                            |
|                        | Return code: `201` / `501`                |
|                        | DATA: Raw map data                        |
| `ID`                   |                                           |
|                        | *(CMD_ID_ID)*                             |
|                        | Return code: `201` / `501`                |
|                        | DATA: Client ID assigned by the server    |

---

### 👥 CLIENT INFORMATION

> Each piece of server data is separated by a space character `' '`

This category includes commands to retrieve information about **all clients connected** to the server.

| Command sent by client | Server response                                         |
|------------------------|---------------------------------------------------------|
| `CLIENTS_NB`           | *(CMD_CLIENTS_NB_ID)*                                   |
|                        | Return code: `202` / `502`                              |
|                        | DATA: `3` *(number of clients)*                         |
| `CLIENTS_POSITIONS`    | *(CMD_CLIENTS_POSITIONS_ID)*                            |
|                        | Return code: `202` / `502`                              |
|                        | DATA: `id1:x,y\|id2:x,y\|...`                           |
| `CLIENTS_STATS`        | *(CMD_CLIENTS_STATS_ID)*                                |
|                        | Return code: `202` / `502`                              |
|                        | DATA: `id1:pseudo,0,34\|id2:pseudo,1,12\|...`           |
|                        | *(pseudo = username, 0/1 = dead/alive, score = size_t)* |

---

### 🎮 PERSONAL CLIENT COMMANDS

> Each piece of server data is separated by a space character `' '`

This category includes commands sent to the server that are **specific to a single client**.

| Command sent by client             | Server response                                        |
|------------------------------------|--------------------------------------------------------|
| `PSEUDO MyPseudo`                  | *(CMD_PSEUDO_ID)*                                      |
| `MyPseudo` is the chosen name      | Return code: `203` / `503`                             |
|                                    | DATA: `MyPseudo` = new pseudo registered on the server |
| `MOVE direction`                   | *(CMD_MOVE_ID)*                                        |
| `direction` must be `UP` or `DOWN` | Return code: `203` / `503`                             |
|                                    | DATA: `OK` or error message                            |
