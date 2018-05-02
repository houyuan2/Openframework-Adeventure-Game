# Development Log

# cannot load image:
use absolute path of the image file instead

# cannot compile:
delete update()

# character can not move to the edge of the screen:
adjust distance of movement for each key pressed

# store data for rooms:
create GameRoom object, and parse it from json file

# need multiple monsters in room
change the Room class, make room_monsters a vector of string that contains the monsters name. Change the json serializer accordingly

# error when testing parser
need to let the parser ignore objects that are not included in the json file, pending fix
update: add an if statement to check whether the json object has the required field before parsing

# error when moving from room to room
change Room and Player from struct to class and add appropriate getter and setter

# collision detection is not sensitive enough
change the original collision detection to "rectangle collision" and implement the appropriate helper function

# error when eat apple, apple sound is played several time
fix a mistake in the if statement detecting whether the apple exit, change from && to ||

# duel name is not visible
change the color of string to black

# need two buttons in the duel mode
import ofxDatGui library, which contains button functions

# monster attack sound is not played
add a while loop to halt the program until the player attack sound is finished

# background music is too loud
change the volume of bgm to 50%

# magic numbers
replace all magic numbers with constants
