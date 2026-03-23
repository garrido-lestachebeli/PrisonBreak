//
// Created by garrido-lestachebeli on 3/23/2026.
//
using namespace std;
    #include <iostream>

int main() {
    cout << "============================================\n";
    cout << "        PRISON BREAK\n";
    cout << "============================================\n\n";

    cout << "You are an inmate attempting to escape a high-security prison.\n";
    cout << "The prison is a maze of rooms\n";
    cout << "Some rooms are interconnected tunnels, others are watched by cameras.\n";
    cout << "A guard is on patrol — and one mistake could end everything.\n\n";

    cout << "------------- OBJECTIVE -------------\n";
    cout << "- Navigate the prison and find the escape route.\n";
    cout << "- Avoid the guard and survive the hazards.\n";
    cout << "- Outsmart the surveillance system.\n\n";

    cout << "-------------- HAZARDS --------------\n";
    cout << "- Guard:\n";
    cout << "  If the guard enters your room, you are caught.\n";
    cout << "  Triggering cameras will cause the guard to move toward them.\n\n";

    cout << "- Tunnels:\n";
    cout << "  Old escape tunnels are connected to other rooms.\n\n";

    cout << "- Cameras:\n";
    cout << "  Entering a camera room alerts the guard.\n";
    cout << "  You may hear footsteps approaching afterward.\n\n";

    cout << "-------------- CLUES ---------------\n";
    cout << "- You hear footsteps nearby if the guard is close.\n";
    cout << "- You hear electrical humming near camera rooms.\n";
    cout << "- You feel air drafts near tunnel entrances.\n\n";
    cout << "- You see a glint of sunlight near the excape exit.\n\n";


    cout << "------------- CONTROLS -------------\n";
    cout << "- WASD : Move to an adjacent room\n";
    cout << "- Q              : Quit the game\n\n";

    cout << "Move carefully. One wrong step could alert the guard.\n";
    cout << "Good luck — your freedom depends on it.\n\n";

    cout << "============================================\n";
    cout << "Press ENTER to begin your escape...\n";
}