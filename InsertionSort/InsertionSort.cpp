#include <cstdlib>
#include <ctime>
#include <iostream>

#include <algorithm>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;
//Shuffle deck
void Random(string deck[], int deckSize){
    srand(static_cast<unsigned int>(time(nullptr)));
    random_shuffle(deck, deck + deckSize);
}

template <class T> void InsertionSort(T arr[], int n) {


    for(int i = 1; i < n; i++){
        for(int j = i-1; j >=0 && arr[j+1] < arr[j]; j--){
            T temp_value = arr[j+1];
            arr[j+1] = arr[j];
            arr[j] = temp_value;
        }
    }
}


int* RankCard(const char deck[], int num) {
    int* transdeck = new int[num];
    int index = 0;
    for (int i = 0; i < num; i++) {
        int val = deck[i];
        switch (val) {
        case 'A':
            transdeck[index] = 1;
            index += 1;
            break;
        case 'T':
            transdeck[index] = 10;
            index += 1;
            break;
        case 'J':
            transdeck[index] = 11;
            index += 1;
            break;
        case 'Q':
            transdeck[index] = 12;
            index += 1;
            break;
        case 'K':
            transdeck[index] = 13;
            index += 1;
            break;
        default:
            transdeck[index] = val - '0';
            index += 1;
            break;
        }
    }
    return transdeck;
}

char* ReverseCard(int deck[], int num) {
    char* transdeck = new char[num];
    int index = 0;
    for (int i = 0; i < num; i++) {
        int val = deck[i];
        switch (val) {
        case 1:
            transdeck[index] = 'A';
            break;
        case 10:
            transdeck[index] = 'T';
            break;
        case 11:
            transdeck[index] = 'J';
            break;
        case 12:
            transdeck[index] = 'Q';
            break;
        case 13:
            transdeck[index] = 'K';
            break;
        default:
            transdeck[index] = char(deck[i] + '0');
            break;
        }
        index += 1;
    }
    return transdeck;
}


int main() {
    // your code goes here
    // Prepare a deck
    string deck[52] = {"SA", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "ST", "SJ", "SQ", "SK",
                        "HA", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "HT", "HJ", "HQ", "HK",
                        "DA", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DT", "DJ", "DQ", "DK",
                        "CA", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CT", "CJ", "CQ", "CK"
                        };

    // Shuffle
    Random(deck, 52);

    // 2D array
    string cardsMatrix[4][13];

    // Put elements into array
    int index = 0;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 13; ++j) {
            cardsMatrix[i][j] = deck[index++];
        }
    }

    // 2D array output
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 13; ++j){
            cout << cardsMatrix[i][j] << " | ";
        }
        cout << "\n-----------------------------------------------------------------\n";
    }

    // Players: North, East, South, West
    string North[13];
    string East[13];
    string South[13];
    string West[13];

    // North
    int N_index = 0;
    for(int i = 0; i <= 8; i += 4){
            for(int j = 0; j < 4; ++j){
                North[N_index++] = cardsMatrix[j][i];
            }
    }
    North[12] = cardsMatrix[0][12];
    cout << "North's hand: ";
    for(int i = 0; i < 13; ++i){
        cout << North[i] << " ";
    }
    cout << "\n";

    // East
    int E_index = 0;
    for(int i = 1; i <= 9; i += 4){
            for(int j = 0; j < 4; ++j){
                East[E_index++] = cardsMatrix[j][i];
            }
    }
    East[12] = cardsMatrix[1][12];
    cout << "East's hand: ";
    for(int i = 0; i < 13; ++i){
        cout << East[i] << " ";
    }
    cout << "\n";

    // South
    int S_index = 0;
    for(int i = 2; i <= 10; i += 4){
            for(int j = 0; j < 4; ++j){
                South[S_index++] = cardsMatrix[j][i];
            }
    }
    South[12] = cardsMatrix[2][12];
    cout << "South's hand: ";
    for(int i = 0; i < 13; ++i){
        cout << South[i] << " ";
    }
    cout << "\n";

    // West
    int W_index = 0;
    for(int i = 3; i <= 11; i += 4){
            for(int j = 0; j < 4; ++j){
                West[W_index++] = cardsMatrix[j][i];
            }
    }
    West[12] = cardsMatrix[3][12];
    cout << "West's hand: ";
    for(int i = 0; i < 13; ++i){
        cout << West[i] << " ";
    }
    cout << "\n";

    // Sort

    // North
    char S[13], H[13], D[13], C[13];

    int SC = 0;
    int HC = 0;
    int DC = 0;
    int CC = 0;

    // Separate the cards into the respective suit array
    for (int r = 0; r < 13; ++r){
        char suit = North[r][0]; // Extract the suit characters

        switch (suit) {
        case 'S':
            S[SC] = North[r][1];
            SC += 1;
            break;
        case 'H':
            H[HC] = North[r][1];
            HC += 1;
            break;
        case 'D':
            D[DC] = North[r][1];
            DC += 1;
            break;
        case 'C':
            C[CC] = North[r][1];
            CC += 1;
            break;
        default:
            //cout << "CHEAT" << endl;
            break;
        }

    }

    // Resize
    char Sn[SC];
    char Hn[HC];
    char Dn[DC];
    char Cn[CC];

    for (int i = 0; i < SC; ++i) {
        Sn[i] = S[i];
    }
    for (int i = 0; i < HC; ++i) {
        Hn[i] = H[i];
    }
    for (int i = 0; i < DC; ++i) {
        Dn[i] = D[i];
    }
    for (int i = 0; i < CC; ++i) {
        Cn[i] = C[i];
    }

    // Insertionsort
    int* ns_intcard = RankCard(Sn, SC);
    //delete[] ns_intcard;
    InsertionSort(ns_intcard, SC);
    char* ns_card = ReverseCard(ns_intcard, SC);
    //delete[] ns_card;

    int* nh_intcard = RankCard(Hn, HC);
    //delete[] nh_intcard;
    InsertionSort(nh_intcard, HC);
    char* nh_card = ReverseCard(nh_intcard, HC);
    //delete[] nh_card;

    int* nd_intcard = RankCard(Dn, DC);
    //delete[] nd_intcard;
    InsertionSort(nd_intcard, DC);
    char* nd_card = ReverseCard(nd_intcard, DC);
    //delete[] nd_card;

    int* nc_intcard = RankCard(Cn, CC);
    //delete[] nc_intcard;
    InsertionSort(nc_intcard, CC);
    char* nc_card = ReverseCard(nc_intcard, CC);
    //delete[] nc_card;

    cout << "North" << endl;
    cout << "S: ";
    for (int i = 0; i < SC; ++i) {
        cout << ns_card[i] << " ";
    }
    cout << "\nH: ";
    for (int i = 0; i < HC; ++i) {
        cout << nh_card[i] << " ";
    }
    cout << "\nD: ";
    for (int i = 0; i < DC; ++i) {
        cout << nd_card[i] << " ";
    }
    cout << "\nC: ";
    for (int i = 0; i < CC; ++i) {
        cout << nc_card[i] << " ";
    }

    // East
    char S1[13], H1[13], D1[13], C1[13];

    int SC1 = 0;
    int HC1 = 0;
    int DC1 = 0;
    int CC1 = 0;

    // Separate the cards into the respective suit array
    for (int r = 0; r < 13; ++r){
        char suit = East[r][0]; // Extract the suit characters

        switch (suit) {
        case 'S':
            S1[SC1] = East[r][1];
            SC1 += 1;
            break;
        case 'H':
            H1[HC1] = East[r][1];
            HC1 += 1;
            break;
        case 'D':
            D1[DC1] = East[r][1];
            DC1 += 1;
            break;
        case 'C':
            C1[CC1] = East[r][1];
            CC1 += 1;
            break;
        default:
            //cout << "CHEAT" << endl;
            break;
        }

    }

    // Resize
    char Sn1[SC1];
    char Hn1[HC1];
    char Dn1[DC1];
    char Cn1[CC1];

    for (int i = 0; i < SC1; ++i) {
        Sn1[i] = S1[i];
    }
    for (int i = 0; i < HC1; ++i) {
        Hn1[i] = H1[i];
    }
    for (int i = 0; i < DC1; ++i) {
        Dn1[i] = D1[i];
    }
    for (int i = 0; i < CC1; ++i) {
        Cn1[i] = C1[i];
    }

    // Insertionsort
    int* ns1_intcard = RankCard(Sn1, SC1);
    InsertionSort(ns1_intcard, SC1);
    char* ns1_card = ReverseCard(ns1_intcard, SC1);

    int* nh1_intcard = RankCard(Hn1, HC1);
    InsertionSort(nh1_intcard, HC1);
    char* nh1_card = ReverseCard(nh1_intcard, HC1);

    int* nd1_intcard = RankCard(Dn1, DC1);
    InsertionSort(nd1_intcard, DC1);
    char* nd1_card = ReverseCard(nd1_intcard, DC1);

    int* nc1_intcard = RankCard(Cn1, CC1);
    InsertionSort(nc1_intcard, CC1);
    char* nc1_card = ReverseCard(nc1_intcard, CC1);


    cout << "\n\nEast" << endl;
    cout << "S: ";
    for (int i = 0; i < SC1; ++i) {
        cout << ns1_card[i] << " ";
    }
    cout << "\nH: ";
    for (int i = 0; i < HC1; ++i) {
        cout << nh1_card[i] << " ";
    }
    cout << "\nD: ";
    for (int i = 0; i < DC1; ++i) {
        cout << nd1_card[i] << " ";
    }
    cout << "\nC: ";
    for (int i = 0; i < CC1; ++i) {
        cout << nc1_card[i] << " ";
    }

    // South
    char S2[13], H2[13], D2[13], C2[13];

    int SC2 = 0;
    int HC2 = 0;
    int DC2 = 0;
    int CC2 = 0;

    // Separate the cards into the respective suit array
    for (int r = 0; r < 13; ++r){
        char suit = South[r][0]; // Extract the suit characters

        switch (suit) {
        case 'S':
            S2[SC2] = South[r][1];
            SC2 += 1;
            break;
        case 'H':
            H2[HC2] = South[r][1];
            HC2 += 1;
            break;
        case 'D':
            D2[DC2] = South[r][1];
            DC2 += 1;
            break;
        case 'C':
            C2[CC2] = South[r][1];
            CC2 += 1;
            break;
        default:
            //cout << "CHEAT" << endl;
            break;
        }

    }

    // Resize
    char Sn2[SC2];
    char Hn2[HC2];
    char Dn2[DC2];
    char Cn2[CC2];

    for (int i = 0; i < SC2; ++i) {
        Sn2[i] = S2[i];
    }
    for (int i = 0; i < HC2; ++i) {
        Hn2[i] = H2[i];
    }
    for (int i = 0; i < DC2; ++i) {
        Dn2[i] = D2[i];
    }
    for (int i = 0; i < CC2; ++i) {
        Cn2[i] = C2[i];
    }

    // Insertionsort
    int* ns2_intcard = RankCard(Sn2, SC2);
    InsertionSort(ns2_intcard, SC2);
    char* ns2_card = ReverseCard(ns2_intcard, SC2);

    int* nh2_intcard = RankCard(Hn2, HC2);
    InsertionSort(nh2_intcard, HC2);
    char* nh2_card = ReverseCard(nh2_intcard, HC2);

    int* nd2_intcard = RankCard(Dn2, DC2);
    InsertionSort(nd2_intcard, DC2);
    char* nd2_card = ReverseCard(nd2_intcard, DC2);

    int* nc2_intcard = RankCard(Cn2, CC2);
    InsertionSort(nc2_intcard, CC2);
    char* nc2_card = ReverseCard(nc2_intcard, CC2);

    cout << "\n\nSouth" << endl;
    cout << "S: ";
    for (int i = 0; i < SC2; ++i) {
        cout << ns2_card[i] << " ";
    }
    cout << "\nH: ";
    for (int i = 0; i < HC2; ++i) {
        cout << nh2_card[i] << " ";
    }
    cout << "\nD: ";
    for (int i = 0; i < DC2; ++i) {
        cout << nd2_card[i] << " ";
    }
    cout << "\nC: ";
    for (int i = 0; i < CC2; ++i) {
        cout << nc2_card[i] << " ";
    }

    // West
    char S3[13], H3[13], D3[13], C3[13];

    int SC3 = 0;
    int HC3 = 0;
    int DC3 = 0;
    int CC3 = 0;

    // Separate the cards into the respective suit array
    for (int r = 0; r < 13; ++r){
        char suit = West[r][0]; // Extract the suit characters

        switch (suit) {
        case 'S':
            S3[SC3] = West[r][1];
            SC3 += 1;
            break;
        case 'H':
            H3[HC3] = West[r][1];
            HC3 += 1;
            break;
        case 'D':
            D3[DC3] = West[r][1];
            DC3 += 1;
            break;
        case 'C':
            C3[CC3] = West[r][1];
            CC3 += 1;
            break;
        default:
            //cout << "CHEAT" << endl;
            break;
        }

    }

    // Resize
    char Sn3[SC3];
    char Hn3[HC3];
    char Dn3[DC3];
    char Cn3[CC3];

    for (int i = 0; i < SC3; ++i) {
        Sn3[i] = S3[i];
    }
    for (int i = 0; i < HC3; ++i) {
        Hn3[i] = H3[i];
    }
    for (int i = 0; i < DC3; ++i) {
        Dn3[i] = D3[i];
    }
    for (int i = 0; i < CC3; ++i) {
        Cn3[i] = C3[i];
    }

    // Insertionsort
    int* ns3_intcard = RankCard(Sn3, SC3);
    InsertionSort(ns3_intcard, SC3);
    char* ns3_card = ReverseCard(ns3_intcard, SC3);

    int* nh3_intcard = RankCard(Hn3, HC3);
    InsertionSort(nh3_intcard, HC3);
    char* nh3_card = ReverseCard(nh3_intcard, HC3);

    int* nd3_intcard = RankCard(Dn3, DC3);
    InsertionSort(nd3_intcard, DC3);
    char* nd3_card = ReverseCard(nd3_intcard, DC3);

    int* nc3_intcard = RankCard(Cn3, CC3);
    InsertionSort(nc3_intcard, CC3);
    char* nc3_card = ReverseCard(nc3_intcard, CC3);

    cout << "\n\nWest" << endl;
    cout << "S: ";
    for (int i = 0; i < SC3; ++i) {
        cout << ns3_card[i] << " ";
    }
    cout << "\nH: ";
    for (int i = 0; i < HC3; ++i) {
        cout << nh3_card[i] << " ";
    }
    cout << "\nD: ";
    for (int i = 0; i < DC3; ++i) {
        cout << nd3_card[i] << " ";
    }
    cout << "\nC: ";
    for (int i = 0; i < CC3; ++i) {
        cout << nc3_card[i] << " ";
    }

    // Score
    //char ranks = "0A23456789TJQK";
    char North_Score[13], East_Score[13], South_Score[13], West_Score[13];
    for (int r = 0; r < 13; ++r) {
        North_Score[r] = North[r][1];
    }
    for (int r = 0; r < 13; ++r) {
        East_Score[r] = East[r][1];
    }
    for (int r = 0; r < 13; ++r) {
        South_Score[r] = South[r][1];
    }
    for (int r = 0; r < 13; ++r) {
        West_Score[r] = West[r][1];
    }
    int* NScore = RankCard(North_Score, 13);
    InsertionSort(NScore, 13);

    int* EScore = RankCard(East_Score, 13);
    InsertionSort(EScore, 13);

    int* SScore = RankCard(South_Score, 13);
    InsertionSort(SScore, 13);

    int* WScore = RankCard(West_Score, 13);
    InsertionSort(WScore, 13);

    // North's Score

    cout << "\nNorth's MAX_MIN_Sum Value: " << NScore[0] << "+" << NScore[1] << "+" << NScore[11] << "+" << NScore[12] << "=" << NScore[0] + NScore[1] + NScore[11] + NScore[12] << endl;

    // East's Score

    cout << "\nEast's MAX_MIN_Sum Value: " << EScore[0] << "+" << EScore[1] << "+" << EScore[11] << "+" << EScore[12] << "=" << EScore[0] + EScore[1] + EScore[11] + EScore[12] << endl;

    // South's Score

    cout << "\nSouth's MAX_MIN_Sum Value: " << SScore[0] << "+" << SScore[1] << "+" << SScore[11] << "+" << SScore[12] << "=" << SScore[0] + SScore[1] + SScore[11] + SScore[12] << endl;

    // West's Score

    cout << "\nWest's MAX_MIN_Sum Value: " << WScore[0] << "+" << WScore[1] << "+" << WScore[11] << "+" << WScore[12] << "=" << WScore[0] + WScore[1] + WScore[11] + WScore[12] << endl;

    //Test the template
    cout << "\n\nTest template:" << endl;
    cout << "Double\n" << endl;
    double test1[5] = {2.56, 4.99, 2.99, 5, 2.3};
    InsertionSort(test1, 5);
    for (int i = 0; i < 5; ++i) {
        cout << test1[i] << " ";
    }
    cout << "\n\nChar\n" << endl;
    char test2[5] = {'b', 'l', 'v', 'z', 'a'};
    InsertionSort(test2, 5);
    for (int i = 0; i < 5; ++i) {
        cout << test2[i] << " ";
    }





    return 0;
}
