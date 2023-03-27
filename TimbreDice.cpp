#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

enum Category { Ones=1, Twos=2, Threes=3, Fours=4,Fives=5,
    Sixes=6,Sevens=7,Eights=8,FullHouse=9, FiveOfAKind=10, SmallStraight=11,
    Straight=12, Timbre=13 };

static map< Category, const char * > names = {
   {Ones, "Ones"},
   {Twos, "Twos"},
   {Threes, "Threes"},
   {Fours, "Fours"},
   {Fives, "Fives"},
   {Sixes, "Sixes"},
   {Sevens, "Sevens"},
   {Eights, "Eights"},
   {FullHouse, "Full House"},
   {FiveOfAKind, "Five-of-a-kind"},
   {SmallStraight, "Small Straight"},
   {Straight, "Straight"},
   {Timbre, "Timbre!"},
};

map<Category, int> score;
int rollDie();
bool isValidInteger(int);
void CategoryOnesToEights(map<int, int>);
void CategoryFullHouse(map<int, int>);
void CategoryFiveOfAKind(map<int, int>);
void CategoryStraightOrSmallStraight(int);
int GetSequenceLength(map<int, int> m);
bool isTimbre(int);
void PrintResult();

int main(int argc, char *argv[])
{
    vector<int> inputs;
    if(argc<=1 || argc != 7) {
        printf("I can't understand the arguments, please follow format: ./TimbreDice x x x x x x, where x should range from 1 to 8. Exiting :( ...");
        exit(1);
    }
    for(int i = 1; i < argc; i++)
    {
        if (isValidInteger(atoi(argv[i]))){
            inputs.push_back(atoi(argv[i]));
        }else{
            printf("Please give me 6 integers and each range from 1 to 8. Exiting :( ...");
            exit(1);
        }
    }
    map<int, int> m;
    for (auto i : inputs)
        ++m[i];
    
    if (isTimbre(m.size())){
        score.insert(make_pair(Timbre, 50));
        PrintResult();
    }else{
        CategoryOnesToEights(m);
        CategoryFullHouse(m);
        CategoryFiveOfAKind(m);
        int n = GetSequenceLength(m);
        CategoryStraightOrSmallStraight(n);
        PrintResult();
    }
    return 0;
}

bool isValidInteger(int num) {        
    if (num <1 || num>8)
        return false; 
    return true;
}

void PrintResult(){
    vector<string> categories;
    map<Category, int>::iterator it;
    int max_value = score.begin()->second;
    categories.push_back(names[score.begin()->first]);

    for(it = next(score.begin()); it != score.end(); ++it) {
        if (it ->second == max_value)
        {
            categories.push_back(names[it->first]);
        } 
        if (it ->second > max_value)
        {
            categories.clear();
            max_value = it->second;
            categories.push_back(names[it->first]);
        }
 
    }

    string str;
    for (int i=0; i<categories.size(); i++)
    {
        str += categories[i]+ " ";
    }
    cout << "Your best categories were: " << str << ". You scored " << max_value << " points!" << endl;
}

void CategoryOnesToEights(map<int, int> m){
    for (auto i : m ) {
        score.insert(make_pair(Category(i.first), i.first * i.second));
    } 
}

void CategoryFullHouse(map<int, int> m){
    vector<int> v;
    bool hasThree = false;
    bool hasTwo = true;
    int result = 0;

    for (auto it=m.begin(); it!=m.end(); ++it)
        v.push_back(it->second);
    if (v.size() == 3){
        for(int i=0; i<3; i++){
            if ( v[i] == 3)
            {
                hasThree = true;
            }
            if ( v[i] == 2)
            {
                hasTwo = true;
            }
        }
        if (hasThree && hasTwo)
        {
            for (auto i : m ) {
                if (i.second > 1){
                    result += i.first*i.second;       
                }          
            }
            score.insert(make_pair(FullHouse, result));
        }else{
            return;
        }
    }
    else if (m.size() == 2)
    {  
        if (v[0] >= 2 && v[1] >=2){
            for (auto i : m ) {
                result += i.first*i.second;            
            }
            score.insert(make_pair(FullHouse, result));
        }else{
            return;
        }
    }else{
        return;
    }
}


void CategoryFiveOfAKind(map<int, int> m){
    for (auto i : m ) {
        if (i.second == 5){
            score.insert(make_pair(FiveOfAKind, i.first*i.second));   
        }          
    }
    return;
}


void CategoryStraightOrSmallStraight(int length){
    if (length == 4 ){
        score.insert(make_pair(SmallStraight, 30));   
    }else if (length == 5) {
        score.insert(make_pair(Straight, 40));   
    }else{
        return;
    }
}


int GetSequenceLength(map<int, int> m){
    vector<int> sequence;
    int count =0;
    for (auto it=m.begin(); it!=m.end(); ++it)
        sequence.push_back(it->first);
    sort(sequence.begin(), sequence.end());
	for(int i = 1; i < sequence.size(); i++)
	{
		if(sequence[i] == sequence[i-1]+1)
			count++;
	}
    return count;
}

bool isTimbre(int size){
    return (size == 1) ? true : false;
}

/*
In case if random rolling dice is needed.
*/
int rollDie()
{
    int roll;
    int max = 8;  
    roll = rand() % 8 + 1;
    return roll;
}
