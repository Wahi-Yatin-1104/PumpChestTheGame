// Written by Juno Suwanduan

#include "NPCInteractionSystem.h"
#include <iostream>

NPC::NPC(const std::string& name, const std::string& dialogue)
    : name(name), dialogue(dialogue) {}

std::string NPC::GetName() const {
    return name;
}

std::string NPC::GetDialogue() const {
    return dialogue;
}

void NPC::SetDialogue(const std::string& newDialogue) {
    dialogue = newDialogue;
}

void NPCInteractionSystem::AddNPC(const NPC& npc) {
    npcs[npc.GetName()] = npc;
}

void NPCInteractionSystem::InteractWithNPC(const std::string& npcName) const {
    auto it = npcs.find(npcName);
    if (it != npcs.end()) {
        std::cout << it->second.GetName() << " says: " << it->second.GetDialogue() << "\n";
    } else {
        std::cout << "NPC not found: " << npcName << "\n";
    }
}

void NPCInteractionSystem::DisplayAllNPCs() const {
    for (const auto& pair : npcs) {
        std::cout << "NPC: " << pair.second.GetName() 
                  << "\nDialogue: " << pair.second.GetDialogue() << "\n\n";
    }
}