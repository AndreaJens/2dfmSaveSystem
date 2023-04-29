# 2D Fighter Maker 2002 - Persistent Save File
A convoluted hack to allow 2D Fighter Maker 2002 games to have persistent data between game sessions.
It works by DLL-hijacking the WSOCK32 DLL used by the engine and monitoring the memory to read and write the engine's System Variables A-O.

## How to use it
* Copy the DLL called WSOCK32.dll from the Releases into the folder with your game's .exe file;
* When in-game you set System Variable P to 1, the DLL will dump the value of all System Variables from A to O to a text file ("config_save.txt"), then set System Variable P to 0;
* When in-game you set System Variable P to 2, the DLL will load the value of all System Variables from A to O from the above text file (if it exists), then set System Variable P to 0;

In practice, this means that you can have persistent data for your game, in the shape of 15 System Variables. Notice that this "hack" doesn't work in Testplay mode. If everything is setup properly, you'll find a file called "config_gamelog.txt" in your game's folder.

## How to compile
Select Release, x86 and press the Compile button. Might require VS2019 or above, but I'm not sure if it can run with older releases of the IDE. This has obviously been tested only on Windows, as 2D Fighter Maker 2002 is not a native app on any other platform.

## Credits
* Yamda, because I would have never thought about this beautiful, revolting hack if it wasn't for his game
* Saturnyoshi for guiding me through the joys of x64dbg

## Known issues
The memory address where System Variable A resides shouldn't change between versions of 2D Fighter Maker 2002, but know that if that is not the case, you might need to find the address yourself and recompile the DLL

