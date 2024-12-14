// Written by Juno Suwanduan

#ifndef NPC_INTERACTION_SYSTEM_H
#define NPC_INTERACTION_SYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>

class NPC {
public:
    NPC(const std::string& name, const std::string& dialogue);
    std::string GetName() const;
    std::string GetDialogue() const;
    void SetDialogue(const std::string& newDialogue);

private:
    std::string name;
    std::string dialogue;
};

class NPCInteractionSystem {
public:
    void AddNPC(const NPC& npc);
    void InteractWithNPC(const std::string& npcName) const;
    void DisplayAllNPCs() const;

private:
    std::unordered_map<std::string, NPC> npcs;
};

#endif