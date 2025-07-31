# Sorcery - CS247 Final Project

A text-based collectible card game implementation inspired by Hearthstone and Magic: The Gathering, built in C++ with modern object-oriented design patterns.

## 🎮 Game Overview

Sorcery is a two-player card game where players compete to reduce their opponent's life to zero. Players use magic as a resource to play cards, summon minions, cast spells, and activate abilities. The game features a rich interaction system with triggered abilities, enchantments, and rituals.

### Key Features

- **4 Card Types**: Minions, Spells, Enchantments, and Rituals
- **Complex Abilities**: Triggered and activated abilities with targeting
- **Enchantment System**: Stackable modifications using the Decorator pattern
- **Event-Driven Triggers**: Observer pattern for automatic ability activation
- **APNAP Order**: Proper sequencing of simultaneous effects
- **Testing Mode**: Debug features for development and demonstration

## 🚀 Getting Started

### Prerequisites

- C++14 compatible compiler (GCC, Clang, or MSVC)
- Make build system
- Unix-like environment (Linux, macOS, WSL)

### Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd Sorcery

# Build the project
make clean
make

# Run the game
./sorcery
```

### Running with Custom Options

```bash
# Use custom deck files
./sorcery -deck1 player1.deck -deck2 player2.deck

# Initialize game with commands from file
./sorcery -init init.txt

# Enable testing mode (bypass costs, enable debug commands)
./sorcery -testing

# Combine options
./sorcery -deck1 custom.deck -init test.txt -testing
```

## 🎯 Gameplay

### Basic Rules

- **Starting State**: 20 life, 3 magic, 5 cards in hand
- **Turn Structure**: Gain 1 magic, draw 1 card, take actions, end turn
- **Victory**: Reduce opponent's life to 0 or below
- **Board Limit**: Maximum 5 minions per player
- **Hand Limit**: Maximum 5 cards in hand

### Card Types

#### Minions

- **Stats**: Attack/Defence (e.g., 2/3 means 2 attack, 3 defence)
- **Actions**: 1 action per turn, used for attacking or abilities
- **Abilities**: Can have triggered (automatic) or activated (manual) abilities
- **Death**: When defence ≤ 0, minion dies and goes to graveyard

#### Spells

- **One-time effects**: Cast and immediately removed from game
- **Targeting**: Most require specific targets (minions, rituals, players)

#### Enchantments

- **Modify minions**: Change stats, abilities, or grant new effects
- **Stacking**: Multiple enchantments apply in oldest-to-newest order
- **Removal**: Lost when minion leaves board

#### Rituals

- **Persistent effects**: Remain in play until replaced or destroyed
- **Charges**: Limited uses, cost charges to activate
- **One per player**: Playing new ritual replaces the old one

### Commands

| Command        | Description                                       | Example                    |
| -------------- | ------------------------------------------------- | -------------------------- |
| `help`         | Show available commands                           | `help`                     |
| `hand`         | Display your hand                                 | `hand`                     |
| `board`        | Show game board                                   | `board`                    |
| `play i [p t]` | Play card i (optionally target player p's card t) | `play 1` or `play 1 2 3`   |
| `attack i [j]` | Minion i attacks opponent (or minion j)           | `attack 1` or `attack 1 2` |
| `use i [p t]`  | Use minion i's ability (optionally target)        | `use 1` or `use 1 2 3`     |
| `inspect i`    | Show minion i's details                           | `inspect 1`                |
| `end`          | End your turn                                     | `end`                      |
| `quit`         | Exit game                                         | `quit`                     |

### Testing Commands (with `-testing` flag)

| Command     | Description              | Example     |
| ----------- | ------------------------ | ----------- |
| `draw`      | Draw a card              | `draw`      |
| `discard i` | Discard card i from hand | `discard 1` |

## 🔧 Development Features

### Testing Mode (`-testing`)

- Bypass magic costs (sets magic to 0)
- Enable `draw` and `discard` commands
- Disable deck shuffling for reproducible games
- Useful for debugging and demonstration

### Initialization Files (`-init`)

Create setup files to automate game initialization:

```
Alice
Bob
play 1
play 1
end
```

This would:

1. Set player names to Alice and Bob
2. Have Alice play her first two cards
3. End Alice's turn
4. Continue with normal gameplay

### Custom Decks (`-deck1`, `-deck2`)

Create custom deck files with card names (one per line):

```
Air Elemental
Earth Elemental
Bone Golem
Novice Pyromancer
Banish
```

## 🏛️ Design Highlights

### Extensibility

- **New Cards**: Add to `CardFactory` with lambda functions
- **New Abilities**: Implement `TriggeredAbility` or `AbilityCommand`
- **New Enchantments**: Extend `EnchantmentDecorator`
- **New Events**: Add to `TriggerManager` notification system

### Memory Safety

- **Smart Pointers**: `std::unique_ptr` throughout prevents memory leaks
- **RAII**: Automatic resource management
- **Exception Safety**: Proper cleanup on errors

### Code Quality

- **Separation of Concerns**: Clear module boundaries
- **Polymorphism**: Clean interfaces for different card types
- **Error Handling**: Comprehensive validation and user feedback
