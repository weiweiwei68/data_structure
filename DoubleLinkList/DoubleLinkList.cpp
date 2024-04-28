#include <iostream>
#include <string>
using namespace std;

int compareStrings(const string& A, const string& B) {
    if (A < B) {
        return 0;
    } else if (A == B) {
        return 1;
    } else { // A > B
        return -1;
    }
}

struct Song {
    string songTitle;
    string singer;
    int releaseYear;
    Song* next;
    Song* prev;
};

class musicSystem {
  private:
    Song* head;
    Song* tail;

  public:
    void appendNode(const string& songTitle, const string& singer, int releaseYear) {
        Song* newNode = new Song{songTitle, singer, releaseYear, nullptr, nullptr};
        if (head == NULL) {
            head = tail = newNode;
            newNode->prev = nullptr;
            newNode->next = nullptr;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }


    void insertNode(const string& songTitle, const string& singer, int releaseYear) {
        //appendNode("LASTONE", "BOSS", 9999);
        Song* newNode = new Song{songTitle, singer, releaseYear, nullptr, nullptr};
        Song* curNode = this->head;
        while (newNode->releaseYear > curNode->releaseYear) {
            if (!curNode->next)
                {
                    break;
                }else{
                    curNode = curNode->next;
                }
        }
        while (newNode->releaseYear == curNode->releaseYear && compareStrings(newNode->singer, curNode->singer) == -1) {
            if (!curNode->next){break;}else{curNode = curNode->next;}
        }
        while (newNode->releaseYear == curNode->releaseYear && compareStrings(newNode->singer, curNode->singer) == 1 && compareStrings(newNode->songTitle, curNode->songTitle) == -1) {
            //curNode = curNode->next;
            if (!curNode->next){break;}else{curNode = curNode->next;}
        }
        if (curNode == head && curNode == tail) {
            this -> head = newNode;
            this -> head -> next = tail;
            this -> tail -> prev = newNode;
        }

        else if (curNode == head) {
            newNode -> next = curNode;
            newNode -> prev = NULL;
            curNode -> prev = newNode;
            head = newNode;
        }

        else if (curNode == tail) {
            newNode -> prev = tail;
            newNode -> next = NULL;
            tail -> next = newNode;
            tail = newNode;
        }
        else {
            newNode -> next = curNode;
            newNode -> prev = curNode -> prev;
            curNode -> prev -> next = newNode;
            curNode -> prev = newNode;
        }
    }

    void deleteNode(int year) {
        Song* target = this->head;
        //cout << "fk" << target->releaseYear<<endl;
        while (target != NULL){
                if (target->releaseYear == year) {
        if (target == head && target == tail) {
            tail = head = NULL;
        }
        // the deleteNode is the first node
        else if (target == head) {
            this->head = target->next;
            target->next->prev = NULL;
        }
        // the deleteNode is the last node
        else if (target == tail) {
            this->tail = target->prev;
            target->prev->next = NULL;
        }
        // the deleteNode is the middle node
        else {
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }
        cout << "Delete the song: " << target->songTitle << " (" << target->singer << ", " << target->releaseYear << ") from the song list." << endl;
        target = target->next;
        }else{target = target->next;}
        }
        //delete target;

 /*       for (int i = 0; i < 2; ++i) {
        if (target->releaseYear != year) {
            if (target->next == NULL){return;}else{target = target->next;}
        }
        else if (target->releaseYear == year) {

        // There is the only one node in DL
        if (target == head && target == tail) {
            tail = head = NULL;
        }
        // the deleteNode is the first node
        else if (target == head) {
            this->head = target->next;
            target->next->prev = NULL;
        }
        // the deleteNode is the last node
        else if (target == tail) {
            this->tail = target->prev;
            target->prev->next = NULL;
        }
        // the deleteNode is the middle node
        else {
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }
        delete target;
        }
    }*/
    }

    void deleteNodesInRange(int start_year, int end_year) {
        for (int i = start_year; i <= end_year; ++i) {
            deleteNode(i);
        }
    }


    void renameSingerInNode(const string& newName, const string& oldName) {
        Song* target = this->head;
        while(target != NULL) {
            if (target->singer == oldName) {
                target->singer = newName;
                target = target->next;
            }else {
                target = target->next;
            }
        }
    }


    void printAllSong() {
        Song* curNode = this->head;
        while (curNode != NULL) {
            cout << curNode->songTitle << " (" << curNode->singer << ", " << curNode->releaseYear << ")" << endl;
            curNode = curNode->next;
        }
    }
/*
    void reversePrintAllSong() {
        //Song* curNode = this->head->next->next->next->next;
        Song* curNode = this->head;
        //if (curNode == NULL) {cout << "NULL" << endl;}
        cout << curNode->songTitle << " (" << curNode->singer << ", " << curNode->releaseYear << ")" << endl;
        cout << curNode->prev << endl;
        //curNode->prev = NULL;
        if (curNode->prev == NULL) {cout<<"nice"<<endl;}
        //cout << curNode->songTitle << " (" << curNode->singer << ", " << curNode->releaseYear << ")" << endl;
    }
*/

    void reversePrintAllSong() {
        Song* curNode = this->tail;
        while (curNode != NULL) {
            cout << curNode->songTitle << " (" << curNode->singer << ", " << curNode->releaseYear << ")" << endl;
            curNode = curNode->prev;
        }
    }


    int check_num() {
        Song* curNode = this->head;
        int i = 0;
        while(curNode != NULL){
            i += 1;
            curNode = curNode->next;
        }
        return i;
    }

/*
    void reversePrintAllSong(int num) {
        Song* curNode = this->tail;
        for (int i = 0; i < num; ++i) {
            cout << curNode->songTitle << " (" << curNode->singer << ", " << curNode->releaseYear << ")" << endl;
            curNode = curNode->prev;
        }
    }
*/

    //musicSystem();


};

int main() {

    musicSystem* msys = new musicSystem;
    msys->appendNode("Yellow", "Coldplay", 2011);
    msys->appendNode("Photograph", "Ed Sheran", 2014);
    msys->appendNode("Shape of You", "Ed Sheran", 2017);
    msys->appendNode("Gorgeous", "Taylor Swift", 2017);
    cout << "Ascending order:\n";
    msys->printAllSong();
    int num = msys->check_num();
    cout << "\nDescending order:\n";
    //msys->reversePrintAllSong(num);
    msys->reversePrintAllSong();
    cout << "\n\n\n\n";


    msys->insertNode("Blank space", "Taylor Swift", 2014);
    msys->insertNode("Fix you", "Coldplay", 2011);
    msys->insertNode("Perfect", "Ed Sheran", 2017);
    msys->insertNode("Willow", "Taylor Swift", 2020);
    cout << "Ascending order:\n";
    msys->printAllSong();

    msys->deleteNodesInRange(2013, 2015);
    cout << "\n\n\nAscending order:\n";
    msys->printAllSong();


    msys->renameSingerInNode("Ed Sheeran", "Ed Sheran");
    cout << "\n\n\nAscending order:\n";
    msys->printAllSong();

    delete msys;






    cout << compareStrings("Taylor Swift","Ed sheran");


    // Q1

    //cout << "\n------------------------\n";
    // Q2

    //cout << "\n------------------------\n";
    // Q3

    //cout << "\n------------------------\n";
    // Q4

    return 0;
}
