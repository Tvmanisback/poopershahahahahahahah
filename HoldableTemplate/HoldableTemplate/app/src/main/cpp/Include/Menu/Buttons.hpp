#pragma once
#include <BNMResolve.hpp>
#include <functional>
#include <string>
#include "ButtonInfo.hpp"
#include "Settings.hpp"
#include "Soundboard.hpp"
#include "../NotiLib/NotiLib.hpp"
#include "../ModInclude.hpp"

using namespace BNM;
using namespace BNM::IL2CPP;
using namespace BNM::Structures;

class Buttons {
public:
    static inline std::vector<std::vector<ButtonInfo>> buttons = {
            {//main stuff - 0
                    ButtonInfo {.buttonText = "Settings", .method = []() { Settings::setCurrentCategory(1); }, .isTogglable = false, .toolTip = "Opens the settings"},
                    ButtonInfo {.buttonText = "Movement", .method = []() { Settings::setCurrentCategory(2); }, .isTogglable = false, .toolTip = "Opens movement"},
                    ButtonInfo {.buttonText = "Player", .method = []() { Settings::setCurrentCategory(3); }, .isTogglable = false, .toolTip = "Opens player"},
                    ButtonInfo {.buttonText = "Visuals nothing in here yet", .method = []() { Settings::setCurrentCategory(4); }, .isTogglable = false, .toolTip = "Opens visuals"},
                    ButtonInfo {.buttonText = "Photon", .method = []() { Settings::setCurrentCategory(5); }, .isTogglable = false, .toolTip = "Opens photon"},
                    ButtonInfo {.buttonText = "Overpowered", .method = []() { Settings::setCurrentCategory(6); }, .isTogglable = false, .toolTip = "Opens overpowered"},
                    ButtonInfo {.buttonText = "Credits", .method = []() { Settings::setCurrentCategory(7); }, .isTogglable = false, .toolTip = "Opens the cedits"},
                    ButtonInfo {.buttonText = "Cool people", .method = []() { Settings::setCurrentCategory(8); }, .isTogglable = false, .toolTip = "Opens the cool people page"},
                    ButtonInfo {.buttonText = "Soundboard", .method = []() { Buttons::RefreshSoundboard(); Settings::setCurrentCategory(9); }, .isTogglable = false, .toolTip = "Open TvMenu Soundboard"},
            },
            {//Settings - 1
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Right hand menu", .enableMethod = []() { Settings::rightHanded = true; }, .disableMethod = []() { Settings::rightHanded = false; }, .toolTip = "Sets the menu to right hand"},
                    ButtonInfo {.buttonText = "Notifications", .enableMethod = []() { NotiLib::SetEnabled(true); }, .disableMethod = []() { NotiLib::SetEnabled(false); }, .enabled = true, .toolTip = "Toggles the notifications"},
                    ButtonInfo {.buttonText = "Disconnect button", .enableMethod = []() { Settings::disconnectButton = true; }, .disableMethod = []() { Settings::disconnectButton = false; }, .enabled = true, .toolTip = "Toggles the disconnect button"},
            },
            {//Movement - 2
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "PlatForms thicker", .method = []() { Movement::HeadFly(); }, .toolTip = "Head Fly"},
                    ButtonInfo {.buttonText = "PlatForms", .method = []() { Movement::platforms(); }, .toolTip = "Plats"},
                    ButtonInfo {.buttonText = "Fly", .method = []() { Movement::HandFly(); }, .toolTip = "Hand Fly"},
                    ButtonInfo {.buttonText = "Long Arms", .method = []() { Movement::Longarms(true); }, .toolTip = "Longer Arms"},
                    ButtonInfo {.buttonText = "Car", .method = []() { Movement::Car(); }, .toolTip = "Driving in my car right after a beer."},
                    ButtonInfo {.buttonText = "SlingshotFly", .method = []() { Movement::SlingshotFly(); }, .toolTip = "luanches yourself"},
                    },
            {//Player - 3
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Invis Name", .method = []() { PlayerMods::invis(); }, .toolTip = "invis name not might work"},
                    ButtonInfo {.buttonText = "NIGGER", .method = []() { PlayerMods::NIGGER(); }, .toolTip = "big name"},
                    ButtonInfo {.buttonText = "RAYVO RUNS TS", .method = []() { PlayerMods::rainbow(); }, .toolTip = "rainbow name not might work"},
                    ButtonInfo {.buttonText = "FUCK ALL YALL", .method = []() { PlayerMods::Error(); }, .toolTip = "invis name"},
            },
            {//Visuals - 4
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
            },
            {//Photon - 5
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Leave Lobby", .method = []() { PhotonMods::LeaveRoom(); }, .toolTip = "Leave Lobby"},
                    ButtonInfo {.buttonText = "Reconnect", .method = []() { OverpoweredMods::Reconnect(); }, .toolTip = "Reconnects to lobby if left"},
                    ButtonInfo {.buttonText = "Join Server", .method = []() { OverpoweredMods::JoinServer(); }, .toolTip = "Join Servers Might Work If Banned"},
                    ButtonInfo {.buttonText = "Nothing Here", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "Nothing Here", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "Nothing Here", .isTogglable = false, .toolTip = "Cool person :D"},
            },
            {//Overpowered - 6
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "CrashAll", .method = []() { OverpoweredMods::CrashAll(); }, .toolTip = "Crash All"},
                    ButtonInfo {.buttonText = "SetMaster", .method = []() { OverpoweredMods::SetMaster(); }, .toolTip = "Set Master"},

                    },
            {//Credits - 7
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Glitch", .isTogglable = false, .toolTip = "Ported the menu from iiDk's template and the dev of this menu"},
                    ButtonInfo {.buttonText = "Ossuary", .isTogglable = false, .toolTip = "Taught me how to mod :D"},
                    ButtonInfo {.buttonText = "Pubert", .isTogglable = false, .toolTip = "Helped me a lot with the code"},
                    ButtonInfo {.buttonText = "Notfishvr", .isTogglable = false, .toolTip = "Helped me a lot debugging"},
            },
            {//Cool people - 8
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Rayvo", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "JohnSon", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "Peak", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "ReagentC.exe", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "Benddd", .isTogglable = false, .toolTip = "Cool person :D"},
            },
            {//Soundboard - 9
                    ButtonInfo {.buttonText = "Refresh Sounds", .method = []() { Buttons::RefreshSoundboard(); }, .isTogglable = false, .toolTip = "Create folder and scan for audio"},
                    ButtonInfo {.buttonText = "Stop Sounds", .method = []() { Soundboard::Stop(); }, .isTogglable = false, .toolTip = "Stop current playback"},
                    ButtonInfo {.buttonText = "Back", .method = []() { Soundboard::Stop(); Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Back to main menu"},
            },
    };
    static void RefreshSoundboard() {
        auto& list = buttons[9];
        if (list.size() > 3) list.erase(list.begin()+3, list.end());
        auto files = Soundboard::Refresh(); size_t index=1;
        for (const auto& file : files) {
            std::string label=file.filename().string(); if(label.size()>20)label=label.substr(0,17)+"...";
            std::string name="Play "+std::to_string(index++)+": "+label; std::string path=file.string();
            list.push_back(ButtonInfo{.buttonText=name,.method=[path](){Soundboard::Play(path);},.isTogglable=false,.toolTip="Play immediately: "+file.filename().string()});
        }
        if(files.empty()) list.push_back(ButtonInfo{.buttonText="No sounds found",.isTogglable=false,.toolTip="Add MP3, WAV, OGG, M4A, AAC or 3GP files then Refresh Sounds"});
    }
};