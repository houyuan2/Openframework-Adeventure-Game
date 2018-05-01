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
    std::ifstream i("../bin/data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    Game test_game = j;
    REQUIRE(test_game.getStart_room() == "gate");
    REQUIRE(test_game.getEnd_room() == "final");
}

TEST_CASE("room monster test") {
    std::ifstream i("../bin/data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    Game test_game = j;
    Room start_room = test_game.getRooms().at(test_game.getStart_room());
    Room end_room = test_game.getRooms().at(test_game.getEnd_room());

    REQUIRE(start_room.getRoomMonsters().at(0) == "Werewolf");
    REQUIRE(end_room.getRoomMonsters().at(0) == "Voldemort");
}

TEST_CASE("room object test") {
    std::ifstream i("../bin/data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    Game test_game = j;
    Room test_room = test_game.getRooms().at("left_wing");

    REQUIRE(test_room.getRoomWeapons().at("sword").getAttackValue() == 50);
    REQUIRE(test_room.getRoomShields().at("iron_shield").getDefense_value() == 50);
    REQUIRE(test_room.getRoomDoors().at("right").getNextRoom() == "lobby");
}

TEST_CASE("monster test") {
    std::ifstream i("../bin/data/final_adventure.json");
    nlohmann::json j;
    i >> j;
    Game test_game = j;

    REQUIRE(test_game.getMonsters().at("Voldemort").getActualHealth() == 200);
    REQUIRE(test_game.getMonsters().at("Zombie").getAttackNum() == 55);
}
