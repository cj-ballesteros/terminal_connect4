// Connect 4
// Repurposed from CS 302.
// Made by Charles Ballesteros.
/* New additions include modifiable board size,
 * two new gamemodes, and colors to more easily
 * distinguish pieces.
 * */

#include <iostream>
#include "LL.h"

/*
Game States:
0 = Ongoing
1 = Player win
2 = Tie
3 = Exit
*/

int main() {
    // Declaring all the variables.
    int boardSize = 7; // Column size
    int rowSize = 6;
    int gamemode = 0;

    std::cout << "\nWelcome to Terminal Connect 4. o/\n";

    // While loop that asks player for gamemode and board size.
    do {
        if (gamemode < 0 || gamemode > 3 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "\nInvalid input";
        }

        std::cout << "\nWhat game mode would you like to play?\n";
        std::cout << "\nGamemodes: \n(0)Classic \n(1)Connect Five \n(2)PopOut";
        std::cout << "\n(3)More Info\n";

        std::cout << "\nEnter the number corresponding to the gamemode: ";
        std::cin >> gamemode;

        if (gamemode == 0 || gamemode == 2) {
            std::cout << "\nChoose the size of the board.\n";
            std::cout << "Rows default = 7, Columns default = 6\n";

            std::cout << "\nEnter rows > 4: ";
            std::cin >> rowSize;

            while (rowSize  <= 3 || std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "\nInvalid Input";
                std::cout << "\nEnter rows > 4: ";
                std::cin >> rowSize;
            }

            std::cout << "Enter columns > 3: ";
            std::cin >> boardSize;

            while (boardSize <= 4 || std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "\nInvalid Input";
                std::cout << "\nEnter columns > 3: ";
                std::cin >> boardSize;
            }
        }

        if (gamemode == 1) {
            std::cout << "\nChoose the size of the board.\n";
            std::cout << "Rows default = 6, Columns default = 9\n";

            std::cout << "Enter columns > 5: ";
            std::cin >> boardSize;

            std::cout << "\nEnter rows > 6: ";
            std::cin >> rowSize;

            while (rowSize <= 3 || std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "\nInvalid Input";
                std::cout << "\nEnter rows > 5: ";
                std::cin >> rowSize;
            }

            while (boardSize <= 4 || std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "\nInvalid Input";
                std::cout << "Enter columns > 6: ";
                std::cin >> boardSize;
            }
        }

        if (gamemode == 3){
            std::cout << "\nClassic: The original game rules where one" <<
                         "\ntries to place four of their colored pieces, " <<
                         "\nin a row, whether that's horizontally, " <<
                         "\nvertically, or diagonally\n";
            std::cout << "\nConnect-Five: Same rules as classic, but you" <<
                         "\nneed five in a row to win.\n";
            std::cout << "\nPopOut: Four-in-a-row rules, but on your turn" <<
                         "\nyou get the opportunity to remove your " <<
                         "\ncolored piece from the bottom. (But only" <<
                         "\na piece of your color!)\n";
        }

    } while (gamemode < 0 || gamemode > 2 || std::cin.fail());

    std::cout << "\n Lets Play.";

    LL<bool> board[boardSize];
    int gameWin = 0;
    int count;
    bool turn = true; // True = Red, False = Blue
    bool dropSuccess; // Checks for valid input
    char rowSelect; // Stores user input.
    int characterValue; // Stores the row value from the user input
    unsigned int rowCheck;
    int connectNumber = 4;

    if (gamemode == 1) {
        connectNumber = 5;
    }

    std::cout << "\n";

    // Loop that continues until game state is changed.
    while (gameWin == 0)
    {
        /*
        Algorithm that prints the board.

        Basically, it takes a linked list i, goes to the n (count) element,
        then if there's nothing there, output a '-'. If there is, then
        true for Red, false for Blue.

        Then, i + 1, then do it again until all the linked lists have been
        gone through.

        After that, n gets decremented. Now, the algorithm goes through all
        the linked lists again, but instead of going to the n element, it 
        goes to n - 1.

        Continue until count = 0.

        This was done to print the board from the bottom up.
        */
        count = rowSize - 1;
        while(count >= 0) {
            for (int i = 0; i < boardSize; i++){
                auto it = board[i].begin();
                for (int j = 0; j < count; j++)
                    it++;

                if (it == board[i].end() || count > board[i].size()) 
                    std::cout << " - ";
                else if (!*it)
                    std::cout << "\033[1;36m X \033[0m";
                else if (*it)
                    std::cout << "\033[1;31m O \033[0m";
                else 
                    std::cout << "\nThis is NOT what the founding" <<
                    "fathers intended!\n";
            }
            std::cout << "\n";
            count--;
        }

        std::cout << "\n ";
        // Prints the letters for the board
        for (int i = 0; i < boardSize; i++) {
            std:: cout << char(65 + i) << "  ";
        }

        std::cout << "\n\n";
        dropSuccess = true; // If user input is valid, this will be true.
                            // The opposite follows
        count = rowSize - 1;
        do
        {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(100, '\n');
            }

            // 0 = ASCII value 48
            if (gamemode == 2) std::cout << "\nType '0' to activate PopOut mode\n";
            if (turn)
                std::cout << "Red Player select a row: ";
            else 
                std::cout << "Blue Player Select a row: ";

            std::cin >> rowSelect;
            std::cout << "\n"; // Takes a user input and makes it lowercase
            characterValue = (int)(tolower(rowSelect));

            // Lets you leave the program without closing
            // the terminal.
            if (characterValue == 57) {
                std::cout << "\nMaster Exit\n";
                gameWin = 3;
                break;
            }


            // If PopOut is the gamemode, allows for
            // popouts to occur
            if (characterValue == 48 && gamemode == 2) {
                std::cout << "\nPopOut Activated, ";
                std::cout << "choose a token you own to pop out\n";
                std::cout << "Enter '0' to exit PopOut mode.\n";
                std::cout << "Selection: ";
                std::cin >> rowSelect;
                std::cout << "\n"; // Takes a user input and makes it lowercase
                characterValue = (int)(tolower(rowSelect));

                if (characterValue == 48) {
                    dropSuccess = false;
                    std::cout << "Exiting PopOut Mode.\n";
                }
                else { // If invalid pop, returns to default state.
                    characterValue -= 97;
                    auto it = board[characterValue].begin();
                    if (*it != turn) {
                        std::cout << "\nInvalid Pop!";
                        dropSuccess = false;
                    }
                    else { //If valid pop, removes piece from board.
                        board[characterValue].headRemove();
                        dropSuccess = true;
                    }
                }
            } else if (characterValue < 97 || characterValue > 97 + boardSize - 1){
                dropSuccess = false;
                std::cout << "Invalid Column\n";
            } // If value is invalid, makes flag false.
            else {
                characterValue -= 97;
                if (board[characterValue].size() > count){
                    dropSuccess = false;
                    std::cout << "Invalid Move\n";
                } // Checks if the column is full.
                else {
                    board[characterValue].tailInsert(turn);
                    dropSuccess = true;
                } // If everything is fine, drops token on the board
            }

        } while (!dropSuccess || std::cin.fail());

        // Master exit conditional.
        if (gameWin == 3) {
            break;
        }

        turn = !turn;

        //vertical check

        rowCheck = 0;
        /*
            Checks if a linked list has consecutive of a certain element.
            If a certain element is not found, sets counter to 0.
            If counter is 4, then connect 4 has occurred, and someone
            has won the game and we may exit the program.
        */
        for (auto it = board[characterValue].begin(); 
            it != board[characterValue].end(); it++){
            *it;
            if (*it == !turn)
                rowCheck++;
            else
                rowCheck = 0;

            if (rowCheck >= connectNumber)
                break;
        }

        // Exits the program.
        if (rowCheck == connectNumber){
            gameWin = 1;
            break;
        }

        //Bottom Left Diagonal Check

        /*
            Similar to the board algorithm, checks every
            diagonal from bottom left to top right. 

            If we're looking for a blue win and a blue 
            chip is found, then the (element + 1) in the 
            next linked list gets examined
        */

        rowCheck = 0;
        count = 0;
        auto it = board[0].begin();
        while (count < rowSize - 1)
        {
            for (int i = 0; i < boardSize; i++){
                auto it = board[i].begin();
                for (int j = 0; j < count; j++)
                    it++;

                if (rowCheck > 0) {
                    for (int h = 0; h < rowCheck; h++)
                        it++;
                }   

                if (it != board[i].end() && count + rowCheck < board[i].size()
                    && *it == !turn)
                    rowCheck++;
                else 
                    rowCheck = 0;

                if (rowCheck >= connectNumber)
                    break;
            }
            if (rowCheck >= connectNumber)
                break;
            rowCheck = 0;
            count++;
        }

        if (rowCheck == connectNumber){
            gameWin = 1;
            break;
        }

        // Top left Diagonal Check.
        /*
            Similar to the board algorithm, checks every
            diagonal from top left to bottom right. 

            If we're looking for a blue win and a blue 
            chip is found, then the (element - 1) in the 
            next linked list gets examined
        */
        rowCheck = 0;
        count = 0;
        while (count < rowSize - 1)
        {
            for (int i = 0; i < boardSize; i++){
                auto it = board[i].begin();
                for (int j = 0; j < count; j++)
                    it++;

                if (rowCheck > 0) {
                    for (int h = 0; h < rowCheck; h++)
                        it--;
                }   
                if (it != board[i].end() 
                    && count - rowCheck < board[i].size() 
                    && *it == !turn)
                    rowCheck++;
                else 
                    rowCheck = 0;

                if (rowCheck >= connectNumber)
                    break;
            }
            if (rowCheck >= connectNumber)
                break;
            rowCheck = 0;
            count++;
        }

        if (rowCheck == connectNumber){
            gameWin = 1;
            break;
        }
        
        //Horizontal Check
        /*
            Using the board algorithm, goes to element n in
            i linked list, then compares that to the elements next
            to it.
        */
        rowCheck = 0;
        count = 0;
        while(count < rowSize - 1) {
            for (int i = 0; i < boardSize; i++){
                auto it = board[i].begin();
                for (int j = 0; j < count; j++)
                    it++;

                if (it != board[i].end() && count < board[i].size() 
                    && *it == !turn)
                    rowCheck++;
                else 
                    rowCheck = 0;

                if (rowCheck >= connectNumber)
                    break;
            }
            if (rowCheck >= connectNumber)
                break;
            rowCheck = 0;
            count++;
        }

        if (rowCheck == connectNumber){
            gameWin = 1;
            break;
        }
        
        rowCheck = 0;
        
        //tie check

        // Checks if all spots of the board have been filled.
        for (int i = 0; i < boardSize; i++){
            rowCheck += board[i].size();
        }
        
        if (rowCheck == boardSize * rowSize){
            gameWin = 2;
            break;
        }

    }

    // Prints out the board again.
    count = rowSize - 1;
    while(count >= 0) {
        for (int i = 0; i < boardSize; i++){
            auto it = board[i].begin();
            for (int j = 0; j < count; j++)
                it++;

            if (it == board[i].end() || count > board[i].size()) 
                std::cout << " - ";
            else if (!*it)
                std::cout << "\033[1;36m X \033[0m";
            else if (*it)
                std::cout << "\033[1;31m O \033[0m";
            else 
                std::cout << "\nThis is NOT what the founding fathers intended!\n";
        }
        std::cout << "\n";
        count--;
    }

    std::cout << "\n ";
    for (int i = 0; i < boardSize; i++) {
        std:: cout << char(65 + i) << "  ";
    }
    
    // Depending on what value gameWin was, prints
    // out the appropriate message.
    switch (gameWin)
    {
    case 0:
        std::cout << "\nHow'd you get out?\n";
        break;

    case 1:
        if (!turn)
            std::cout << "\nRed Wins!\n";
        else std::cout << "\nBlue Wins!\n";
        break;

    case 2:
        std::cout << "\nTie.\n";
        break;

    case 3:
        std::cout << "\nMaster Exit Confirmed\n";
        break;
    
    default:
        std::cout << "\nWhat the devil?\n";
        break;
    }
    
    
    return 0;
}