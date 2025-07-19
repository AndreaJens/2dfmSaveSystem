# 2D Fighter Maker 2002 - Persistent Save File
A convoluted hack to allow 2D Fighter Maker 2002 games to have persistent data between game sessions and to select stage in Versus Mode.
It works by DLL-hijacking the WSOCK32 DLL used by the engine and monitoring the memory to read and write the engine's System Variables A-O.

## How to use it
* Copy the DLL called WSOCK32.dll from the Releases into the folder with your game's .exe file;
* When in-game you set System Variable P to 1, the DLL will dump the value of all System Variables from A to O to a text file ("config_save.txt"), then set System Variable P to 0;
* When in-game you set System Variable P to 2, the DLL will load the value of all System Variables from A to O from the above text file, then set System Variable P to 0;
* If, in your Character Selection screen, you set System Variable P to 3 or more, the DLL will write this value in memory to change the stage without having to manually do it from the in-game menu. P = 3 is the first stage, P = 4 the second, P = 5 the third and so on. **WARNING:** Selecting a stage that does not exist will crash the game!

In practice, this means that you can have persistent data for your game, in the shape of 15 System Variables. Notice that this "hack" doesn't work in Testplay mode. If everything is setup properly, you'll find a file called "config_gamelog.txt" in your game's folder, after starting it up for the first time, once the DLL is in place.

## How to compile
Open the .sln file in Visual Stuido, select Release, x86 and press the Compile button. Might require VS2019 or above, but I'm not sure if it can run with older releases of the IDE. This has obviously been tested only on Windows, as 2D Fighter Maker 2002 is not a native app on any other platform.

## Credits
* Yamda, because I would have never thought about this beautiful, revolting hack if it wasn't for his game (same goes for v2.0, btw)
* Saturnyoshi for guiding me through the joys of x64dbg
* Armonté for finding the memory address used by the stage selection process

## Known issues
The memory address where System Variable A and the stage select process resides shouldn't change between versions of 2D Fighter Maker 2002, but know that if that is not the case, you might need to find the address yourself and recompile the DLL.

