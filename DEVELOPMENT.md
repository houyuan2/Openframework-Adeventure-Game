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
