# Pipe-Game
C++ Pipe Game uses SFML graphics

Debug/compile and run instructions:
All the configurations for this project is in the main cmake file.
All you have to do is to have SFML 2.5.1 version downloaded and located in
C directory (on windows) because that is where the cmake directs it
to find it.
You can download SFML from https://www.sfml-dev.org/download/sfml/2.5.1
while you have it you can open it in wisual studio - in which I wrote it, or any 
other code editor and debug/run as you wish.

OOP design review:

The main object in this game is Tile which is a base class for
the classes Pipe, Sink and Tap.
This class has the main methods needed for the game
which are setStream() - turn stream on/off, 
and getNeighborsOpenTowards() - return list of the neightbors that 
this tile open to. This allows to go over
the graph with some search algorithm.

From Tile class inherits the class sink which is concrete class
and RotatableTile which is another abstract base class
that has the method rotate() From this class inherit Sink and Pipe which are concrete classes.

The main game managing class is Stage class.
Stage class builds the current stage and initializes
all the start data (like the neighbors of every tile).
Stage class also has he main method of the game conectStream()
which goes over the graph in Depth First Search and conect stream
between tiles.

The other classes are:
OpenningScreen - show openning screen in the begining of the game.
StagesMenu - show stages menu and get user choise of stage to play.
ClicksCounter - show the user the number of clicks he used in the current stage so  far.
GameClock - show the user the time passed since the begining of the current stage.
Controller - maintain all the game proccess using all the classes above.
Resources - read all the images of the game and keeps it in textures.

