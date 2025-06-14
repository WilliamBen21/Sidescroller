# mySideScroll - Unreal Engine Character Selection System

A comprehensive side-scrolling game built in Unreal Engine 5.6 with an advanced character selection menu system.

## 🎮 Features

### Character Selection System
- **Pre-game character selection menu** with 3D character previews
- **Mouse and controller support** for navigation
- **Three unique character types:**
  - **Side-Scrolling Character** - Basic platforming with wall jumping
  - **Platforming Character** - Enhanced movement with dashing mechanics  
  - **Combat Character** - Full combat system with enemies and combos

### Gameplay Variants
- **Side-Scrolling Mode** - Classic 2.5D platforming experience
- **Platforming Mode** - Advanced movement mechanics with dash abilities
- **Combat Mode** - Action-packed combat with enemy AI and damage systems

## 🛠️ Technical Implementation

### C++ Classes Created
- `CharacterSelectionWidget` - Main UI widget for character selection
- `MenuGameMode` - Handles menu screen and game transitions
- `CharacterPreviewActor` - 3D character preview system
- Enhanced `SideScrollingGameMode` - Supports character type spawning

### Key Features
- **Seamless character switching** based on menu selection
- **3D character previews** that rotate and display in the menu
- **Input system** supporting both keyboard/mouse and gamepad
- **Modular architecture** allowing easy addition of new character types

## 🚀 Getting Started

### Prerequisites
- Unreal Engine 5.6
- Visual Studio 2022
- Windows 10/11

### Building the Project
1. Clone this repository
2. Right-click on `mySideScroll.uproject` and select "Generate Visual Studio project files"
3. Open `mySideScroll.sln` in Visual Studio
4. Build the solution (F7)
5. Launch the project from Visual Studio (F5) or open the .uproject file

### Project Structure
```
Source/mySideScroll/
├── CharacterSelectionWidget.h/.cpp     # Character selection UI
├── MenuGameMode.h/.cpp                  # Menu game mode
├── CharacterPreviewActor.h/.cpp         # 3D character previews
├── Variant_SideScrolling/               # Side-scrolling character variant
├── Variant_Platforming/                 # Platforming character variant
└── Variant_Combat/                      # Combat character variant
```

## 🎯 How to Use

1. **Start the game** - The character selection menu appears first
2. **Navigate characters** using arrow keys, WASD, or controller D-pad
3. **Select character** with Enter, Space, or controller A button
4. **Game starts** with your chosen character type

## 🔧 Customization

### Adding New Characters
1. Create new character class inheriting from base character
2. Add character type to `ECharacterType` enum
3. Update `CharacterSelectionWidget` to include new character
4. Set up character preview mesh in `CharacterPreviewActor`

### Modifying UI
- Character selection UI is built with UMG widgets
- Customize appearance in Unreal Editor's Widget Blueprint system
- C++ classes provide the underlying functionality

## 📝 Development Notes

- **Character selection system** is fully implemented in C++
- **UI elements** can be customized through Unreal's Blueprint system
- **Game modes** automatically spawn the correct character type
- **Input handling** supports multiple input devices simultaneously

## 🤝 Contributing

Feel free to fork this project and submit pull requests for improvements!

## 📄 License

This project is open source and available under the MIT License.

---

**Built with ❤️ using Unreal Engine 5.6** 