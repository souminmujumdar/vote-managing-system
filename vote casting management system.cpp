#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Forward declaration of FriendClass
class FriendClass;

class Party {
    // FriendClass is a friend of Party, allowing it to access private members
    friend class FriendClass;

public:
    Party(const string& partyName, const string& fileName)
        : partyName(partyName), fileName(fileName) {}

    void showResults() {
        int voteCount = 0;
        ifstream file(fileName);
        file >> voteCount;
        file.close();

        cout << partyName << " Votes: " << voteCount << endl;
    }

    void showResults(bool detailed) {
        int voteCount = 0;
        ifstream file(fileName);
        file >> voteCount;
        file.close();

        cout << "Party: " << partyName << endl;
        cout << "Vote Count: " << voteCount << endl;
        if (detailed) {
            cout << "Vote Percentage: " << static_cast<double>(voteCount) / totalVotes * 100 << "%" << endl;
        }
    }

    void showResults(bool detailed, int totalVotes) {
        int voteCount = 0;
        ifstream file(fileName);
        file >> voteCount;
        file.close();

        cout << "Party: " << partyName << endl;
        cout << "Vote Count: " << voteCount << endl;
        if (detailed) {
            cout << "Vote Percentage: " << static_cast<double>(voteCount) / totalVotes * 100 << "%" << endl;
        }
    }

    virtual void castVote() {
        int voteCount = 0;
        ifstream file(fileName);
        file >> voteCount;
        file.close();

        voteCount++;
        ofstream outFile(fileName);
        outFile << voteCount;
        outFile.close();

        cout << "Your vote for " << partyName << " has been cast successfully." << endl;
    }

private:
    string partyName;
    string fileName;
    static int totalVotes;
};

int Party::totalVotes = 0;

// FriendClass can access the private members of Party
class FriendClass {
public:
    void accessPrivateMembers(Party& party) {
        // FriendClass can access private members of Party
        cout << "FriendClass accessed private member: " << party.partyName << endl;
        cout << "FriendClass cannot access private members of Party: " << party.fileName << endl;
    }
};

class PTI : public Party {
public:
    PTI() : Party("PTI", "PTI.txt") {}
};

class PMLN : public Party {
public:
    PMLN() : Party("PMLN", "PMLN.txt") {}
};

class PPP : public Party {
public:
    PPP() : Party("PPP", "PPP.txt") {}
};

void displayMenu() {
    cout << "\nChoose a Party to cast your Vote" << endl;
    cout << "1 - PTI" << endl;
    cout << "2 - PMLN" << endl;
    cout << "3 - PPP" << endl;
}

int main() {
    cout << "\n\tVOTING MANAGEMENT SYSTEM\n";
    int ID;

    cout << "Enter Your ID (5555-5755): ";
    cin >> ID;

    if (ID < 5555 || ID > 5755) {
        cout << "Invalid ID. Please enter a valid ID." << endl;
        return 0;
    }

    ifstream idFile("used_ids.txt");
    int usedID;
    bool idExist = false;

    while (idFile >> usedID) {
        if (usedID == ID) {
            idExist = true;
            break;
        }
    }
    idFile.close();

    if (idExist) {
        cout << "Invalid ID or it has already been used :|" << endl;
        return 0;
    }

    ofstream idOutFile("used_ids.txt", ios::app);
    idOutFile << ID << endl;
    idOutFile.close();

    Party* selectedParty = nullptr;

    for (int i = 0; i < 1; i++) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                selectedParty = new PTI();
                break;
            case 2:
                selectedParty = new PMLN();
                break;
            case 3:
                selectedParty = new PPP();
                break;
            default:
                cout << "Invalid choice. Please choose a valid party." << endl;
                break;
        }

        if (selectedParty) {
            selectedParty->castVote();
            delete selectedParty;
        }
    }

    // Display the results after voting
    cout << "\nResult updates of the Election:" << endl;
    PTI().showResults();
    PMLN().showResults();
    PPP().showResults();

    // Create an instance of FriendClass and demonstrate access to private members
    FriendClass friendObj;
    PTI ptiParty;
    friendObj.accessPrivateMembers(ptiParty);

    return 0;
}
