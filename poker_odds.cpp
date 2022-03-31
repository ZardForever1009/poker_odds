// poker odds calculator
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// code info
void show_info(){
    cout<<"=======Pokers Odds Calculator=======\n";
    cout<<"> Welcome to poker odds calculator\n";
    cout<<"> Return instant odds of poker cards\n";
    cout<<"> Autosave current status\n";
    cout << "\n> creator: zardforever\n";
    cout<<"====================================\n";
    return;
}

// get user input integer
int get_integer(const string& info){
    string input;
    bool okay=false;
    WHILE:
    while(!okay){
        cout<<info;
        getline(cin, input);
        for(int i=0;i<input.size();i++){
            if(!isdigit(input[i])){
                cout<<"> integer only\n\n";
                goto WHILE;
            }
        }       
        if(stoi(input)>13||stoi(input)<1){
            cout<<"> invalid input\n\n";
            goto WHILE;
        }
        okay=true;
    }
    return stoi(input);
}

// get yes or no
bool yes_or_not(const string& info){
    string input;
    bool okay=false;
    WHILE:
    while(!okay){
        cout<<info;
        getline(cin, input);
        if(input=="y"||input=="Y")return true;
        else if(input=="n"||input=="N")return false;
        else cout<<"> invalid input\n\n";
    }
}

// read file for recovering state
vector<float> read_file(){
    ifstream file;
    file.open("stats.txt",ios::in);
    if(file){
        string line;
        vector<float> o_file;
        while(getline(file,line)){                
            o_file.push_back(stof(line));
        }
        return o_file;
    }
    else{
        vector<float> error(1,-1.0);
        cout<<"> reading file error\n\n";
        return error;
    }
}

// save file and make it only read.
void save_file(vector<float> cards){
    remove("stats.txt"); // delete last stats
    ofstream file("stats.txt");
    // write save data into file
    for(int i=0;i<cards.size();i++){
        file<<cards[i]<<endl;
    }
    file.close();
}

// calculate poker odds 
void poker_odds(vector<float> cards){
    cout<<"=======Pokers Odds Result=======\n";
    for(int i=1;i<=13;i++){
        float odd;
        if(cards[0]==0.0)odd=0.00;
        else odd=(cards[i]/cards[0]);
        if(i>=10)cout<<" "<<i<<" --->  "<<fixed<<setprecision(2)<<100*odd<<"%"<<endl; 
        else cout<<" "<<i<<"  --->  "<<fixed<<setprecision(2)<<100*odd<<"%"<<endl; 
    }
    cout<<"================================\n\n";
    return; 
}

// reload game or not
vector<float> reload_stats(){
    vector<float> cards;
    ifstream file("stats.txt");
    string str;
    while(file>>str){
        cards.push_back(stof(str));
    }
    return cards;
}

// print current cards stats
void print_status(vector<float> cards){
    cout<<"> Poker Cards Odds Calculator\n\n";
    cout<<"=======Poker Cards Status=======\n";
    for(int i=1;i<=13;i++){
        if(i>=10)cout<<" "<<i<<" --->  "<<int(cards[i])<<" left\n";
        else cout<<" "<<i<<"  --->  "<<int(cards[i])<<" left\n";
    }
    cout<<"\n> Total: "<<int(cards[0])<<" left"<<endl;
    cout<<"================================\n\n";
}

// a game operation
void operation(vector<float>& cards){
    while(cards[0]!=0.0){
        print_status(cards);
        save_file(cards);
        bool okay=false;
        while(!okay){                
            int card_num=get_integer("> Enter card number you choose: ");
            if(cards[card_num]==0.0)cout<<"> invalid input\n\n";            
            else{
                cards[card_num]--;
                cards[0]--;                    
                poker_odds(cards);                    
                system("pause");
                system("cls");
                okay=true;
             }
         }  
     }
     
     cout<<"> End of Poker Odds Calculator\n";
     cout<<"> Hope you have fun with it !!\n";
     cout<<"> See you next time ~\n\n";
     remove("stats.txt");
     ofstream file("stats.txt");
     file.close();
     return;
}

// execute function (combine all function together)
void execute(){
    // reload or not
    show_info();
    bool reload=yes_or_not("> Reload saved states ??? (y/n): ");
    // new game
    if(!reload){
        NEW_GAME:
        int deck=get_integer("> Enter decks of pokers: ");
        system("cls");
        vector<float> cards(14, 4.0*deck);
        cards[0]=52.0*deck;
        operation(cards);
    }
    // reload game
    else{
        system("cls");
        vector<float> cards=reload_stats();
        if(cards.empty()){
            cout<<"> seems no available stats\n";
            cout<<"> create new calculator\n\n";
            system("pause");
            system("cls");
            goto NEW_GAME;
        }
        else operation(cards);
    }
    return;
}

int main(){
    
    execute();
    
    system("pause");
    return 0;
}