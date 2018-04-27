//
// Created by Houyuan Sha on 2018/4/21.
//
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/json.hpp"
#include "../src/Items.hpp"
#include "../src/Game.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>


TEST_CASE("basic parsing test") {
    std::ifstream i("../bin/final_adventure.json");
    nlohmann::json j;
    i >> j;
    Game myGame = j;
    REQUIRE(myGame.getStart_room() == "gate");
}

TEST_CASE("room_monsters") {
    std::ifstream i("../bin/final_adventure.json");
    nlohmann::json j;
    i >> j;
    Game myGame = j;
    REQUIRE(myGame.getRooms().at(myGame.getStart_room()).room_monsters.at(0) == "Werewolf");
}
