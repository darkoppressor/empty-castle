/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "../game/game.h"

#include <game/game_manager.h>
#include <network/network_engine.h>
#include <network/network_server.h>
#include <engine.h>
#include <data/object_manager.h>
#include <options/options.h>
#include <ui/engine_input.h>

using namespace std;

void Game_Manager::handle_drag_and_drop (string file) {
    // Do something with file
}

void Game_Manager::prepare_for_input () {
    if (in_progress) {
        command_states.clear();

        display_scoreboard = false;

        Game::updateTextParserFocus();
    }
}

void Game_Manager::handle_command_states_multiplayer () {
    if (in_progress) {
        if (Network_Engine::status == "server") {
            Network_Server::prepare_server_input_states();

            for (size_t i = 0; i < Network_Engine::clients.size(); i++) {
                if (!paused) {
                    // Example multiplayer command state
                    /**if(Network_Engine::clients[i].game_command_state("some_command")){
                        // Deal with command state here
                       }*/
                }
            }
        }
    }
}

void Game_Manager::handle_game_commands_multiplayer () {
    if (in_progress) {
        if (Network_Engine::status == "server") {
            for (size_t i = 0; i < Network_Engine::clients.size(); i++) {
                for (size_t j = 0; j < Network_Engine::clients[i].command_buffer.size(); j++) {
                    string command_name = Network_Engine::clients[i].command_buffer[j];

                    if (!paused) {
                        // Example multiplayer command
                        /**if(command_name=="some_command"){
                            // Deal with command here
                           }*/
                    }
                }

                Network_Engine::clients[i].command_buffer.clear();
            }
        }
    }
}

void Game_Manager::handle_input_states_gui () {
    int mouse_x = 0;
    int mouse_y = 0;

    Engine::get_mouse_state(&mouse_x, &mouse_y);

    if (in_progress) {
        if (Object_Manager::game_command_state("scoreboard")) {
            display_scoreboard = true;
        }
    }
}

void Game_Manager::handle_input_states () {
    int mouse_x = 0;
    int mouse_y = 0;

    Engine::get_mouse_state(&mouse_x, &mouse_y);

    if (in_progress) {
        if (!paused) {
            // Example multiplayer command state
            /**if(Object_Manager::game_command_state("some_command")){
                command_states.push_back("some_command");
               }*/

            if (!Game::isTextParserOn()) {
                // Move the ship via directional keys
                if (Game::moveInputState("left")) {
                    Game::playerThrust("left");
                }

                if (Game::moveInputState("up")) {
                    Game::playerThrust("up");
                }

                if (Game::moveInputState("right")) {
                    Game::playerThrust("right");
                }

                if (Game::moveInputState("down")) {
                    Game::playerThrust("down");
                }

                if (Game::moveInputState("left") && Game::moveInputState("up")) {
                    Game::playerThrust("left_up");
                }

                if (Game::moveInputState("up") && Game::moveInputState("right")) {
                    Game::playerThrust("right_up");
                }

                if (Game::moveInputState("right") && Game::moveInputState("down")) {
                    Game::playerThrust("right_down");
                }

                if (Game::moveInputState("down") && Game::moveInputState("left")) {
                    Game::playerThrust("left_down");
                }

                if (Game::moveInputState("left") && Game::moveInputState("right")) {
                    Game::playerThrust("left");
                }

                if (Game::moveInputState("up") && Game::moveInputState("down")) {
                    Game::playerThrust("up");
                }

                if (Game::moveInputState("left") && Game::moveInputState("up") && Game::moveInputState("right")) {
                    Game::playerThrust("left_up");
                }

                if (Game::moveInputState("left") && Game::moveInputState("down") && Game::moveInputState("right")) {
                    Game::playerThrust("left_down");
                }

                if (Game::moveInputState("left") && Game::moveInputState("up") && Game::moveInputState("down")) {
                    Game::playerThrust("left_up");
                }

                if (Game::moveInputState("up") && Game::moveInputState("right") && Game::moveInputState("down")) {
                    Game::playerThrust("right_up");
                }

                if (Game::moveInputState("left") && Game::moveInputState("up") && Game::moveInputState("right") &&
                    Game::moveInputState("down")) {
                    Game::playerThrust("left_up");
                }

                if (!Game::moveInputState("left") && !Game::moveInputState("up") && !Game::moveInputState("right") &&
                    !Game::moveInputState("down")) {
                    Game::playerThrust("none");
                }
            } else {
                Game::handleTextParserInputStates();
                Game::handleTextDisplayInputStates();

                Game::playerThrust("none");
            }
        }
    }
}

bool Game_Manager::handle_game_command_gui (string command_name) {
    // Pause the game
    if (command_name == "pause") {
        toggle_pause();

        return true;
    }
    // Example multiplayer pause
    /**if(command_name=="pause"){
        if(Network_Engine::status=="server"){
            toggle_pause();

            Network_Server::send_paused();
        }

        return true;
       }*/
    // Toggle chat box
    else if (command_name == "chat") {
        Engine::chat.toggle_on();

        return true;
    }

    return false;
}

bool Game_Manager::handle_game_command (string command_name) {
    const uint8_t* keystates = SDL_GetKeyboardState(NULL);

    // DEV COMMANDS
    if (Options::dev && keystates[SDL_SCANCODE_F1]) {
        // Example dev command
        /**if(command_name=="some_dev_command"){
            // Dev command here.

            return true;
           }*/
    }

    // END OF DEV COMMANDS

    if (!paused) {
        if (command_name == "text_parser") {
            Game::toggleTextParser(true);

            return true;
        } else if (command_name == "text_parser_no_commit") {
            Game::toggleTextParser(false);

            return true;
        } else if (command_name == "text_display_up") {
            Game::scrollTextDisplay(true);

            return true;
        } else if (command_name == "text_display_down") {
            Game::scrollTextDisplay(false);

            return true;
        }

        // Example multiplayer command input
        /**if(command_name=="some_command"){
            Network_Engine::add_command(command_name);

            return true;
           }*/
    }

    return false;
}

bool Game_Manager::handle_input_events_gui () {
    bool event_consumed = false;

    if (in_progress) {
        const vector<Game_Command>& game_commands = Object_Manager::get_game_commands();

        for (size_t i = 0; i < game_commands.size() && !event_consumed; i++) {
            if ((Engine_Input::event.type == SDL_CONTROLLERBUTTONDOWN &&
                 game_commands[i].button == Engine_Input::event.cbutton.button) ||
                (Engine_Input::event.type == SDL_KEYDOWN && Engine_Input::event.key.repeat == 0 &&
                 game_commands[i].key == Engine_Input::event.key.keysym.scancode)) {
                event_consumed = handle_game_command_gui(game_commands[i].name);
            }
        }
    }

    return event_consumed;
}

bool Game_Manager::handle_input_events () {
    bool event_consumed = false;

    if (in_progress) {
        if (!event_consumed) {
            event_consumed = Game::handleTextParserInputEvents();
        }

        if (!event_consumed) {
            event_consumed = Game::handleTextDisplayInputEvents();
        }

        const vector<Game_Command>& game_commands = Object_Manager::get_game_commands();

        for (size_t i = 0; i < game_commands.size() && !event_consumed; i++) {
            if ((Engine_Input::event.type == SDL_CONTROLLERBUTTONDOWN &&
                 game_commands[i].button == Engine_Input::event.cbutton.button) ||
                (Engine_Input::event.type == SDL_KEYDOWN && Engine_Input::event.key.repeat == 0 &&
                 game_commands[i].key == Engine_Input::event.key.keysym.scancode)) {
                event_consumed = handle_game_command(game_commands[i].name);
            }
        }
    }

    return event_consumed;
}
