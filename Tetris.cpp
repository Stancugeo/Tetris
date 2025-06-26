#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include<time.h>
#include <queue>
#include <cstring>
#include <sstream>

using namespace std;
int numofshapes = 7;

vector<string> arena;
vector<vector<string>> options;
bool pxy[25][25];
vector<int>col(16);
int score = 0 ;
vector<int>fscore{0,1,3,5,10};
int level = 1 ;
int combo = 1;
string name ;




class Object{
public:
    vector<vector<pair<int,int>>>rots;
    vector<pair<int,int>> forms;
    int curr_posx;
    int curr_posy;
    int type;




    Object(int tshape){
        if(tshape==0){
            vector<vector<pair<int,int>>>vec{
                {{0,0},{0,-1},{0,1},{0,2}},
                {{0,0},{-1,0},{1,0},{-2,0}},
                {{-1,-1},{-1,0},{-1,1},{-1,2}},
                {{-2,1},{-1,1},{0,1},{1,1}}
            };
            rots = vec;
            forms = vec[0];

        }
        else if(tshape==1){
            forms.push_back(make_pair(0,-1));
            forms.push_back(make_pair(0,0));
            forms.push_back(make_pair(-1,0));
            forms.push_back(make_pair(-1,-1));

        }
        else if(tshape==2){
            vector<vector<pair<int,int>>>vec{
            {{-1,0},{0,0},{1,0},{1,1}},
            {{-1,1},{0,-1},{0,0},{0,1}},
            {{1,0},{0,0},{-1,0},{-1,-1}},
            {{1,-1},{0,-1},{0,0},{0,1}},
            };
            forms = vec[0];
            rots = vec;


        }
        else if(tshape==3){
            vector<vector<pair<int,int>>>vec{
            {{0,0},{-1,0},{0,-1},{1,-1}},
            {{0,-1},{0,0},{1,0},{1,1}},
            {{-1,1},{0,1},{0,0},{1,0}},
            {{-1,-1},{-1,0},{0,0},{0,1}}
            };
            forms = vec[0];
            rots = vec;
            cout << "Hello";
            


        }
        else if(tshape==4){
            vector<vector<pair<int,int>>>vec{
            {{0,0},{-1,-1},{0,-1},{1,-1}},
            {{0,0},{1,0},{1,1},{1,-1}},
            {{0,0},{0,1},{-1,1},{1,1}},
            {{0,0},{-1,0},{-1,-1},{-1,1}}
            };
            forms = vec[0];
            rots = vec;


        }
        else if(tshape==5){
            vector<vector<pair<int,int>>>vec{
            {{0,0},{1,0},{1,-1},{-1,0}},
            {{0,0},{0,1},{0,-1},{1,1}},
            {{0,0},{1,0},{-1,0},{-1,1}},
            {{0,0},{0,1},{0,-1},{-1,-1}}
            };
            forms = vec[0];
            rots = vec;

        }
        else if(tshape==6){
            vector<vector<pair<int,int>>>vec{
            {{0,0},{0,-1},{-1,-1},{1,0}},
            {{0,0},{1,0},{1,-1},{0,1}},
            {{0,0},{-1,0},{0,1},{1,1}},
            {{0,0},{0,-1},{-1,0},{-1,1}}
            };
            forms = vec[0];
            rots = vec;
        }
        this->curr_posx = 5;
        this->type = 0;
        this->curr_posy = 1;


    }
    void AddObjectinMap(){
        for(int i = 0 ; i < forms.size() ; i++){
            arena[curr_posy+forms[i].first][curr_posx+forms[i].second] = '*';
        }
    }



    void Move(int y , int x){
        //moveleft:0 -1
        //moveright:0 1
        //moveup: -1 0
        //movedown: 1 0
        erase_object();
        for(int i = 0 ; i < forms.size() ; i++){
            arena[curr_posy+forms[i].first + y][curr_posx+forms[i].second + x] = '*';
        }
        this->curr_posx = this->curr_posx + x;
        this->curr_posy = this->curr_posy + y;

    }
    bool check(int y , int x){
        for(int z = 0 ; z < forms.size() ; z++){
            int posx = curr_posx+forms[z].second+x;
            int posy = curr_posy+forms[z].first+y;
            if(posy >= arena.size() || posy < 0) return false;
            else if(posx < 0 || posx >= arena[0].size()) return false;
            else if(arena[posy][posx] == '*')
                if(pxy[posy][posx]==true)
                    return false;

        }

        return true;


    }


    void operator=(Object & obj){
        this->curr_posx = obj.curr_posx;
        this->curr_posy = obj.curr_posy;
        this->forms = obj.forms;
        this->rots = obj.rots;
        this->type = obj.type;

    }




    int get_maxy_down(){
        int maxy_down = 0;
        for(int i = 0 ; i < forms.size() ; i++){
            maxy_down = max(maxy_down,forms[i].first);
        }
        return maxy_down;
    }
    int get_maxx_right(){
        int maxx_right = 0;
        for(int i = 0 ; i < forms.size() ; i++){
            maxx_right = max(maxx_right,forms[i].second);
        }
        return maxx_right;
    }
    void erase_object(){
        for(int i = 0 ; i < forms.size() ; i++){
            arena[curr_posy+forms[i].first][curr_posx+forms[i].second] = ' ';
        }
    }
    void Rotate(int stage){
        if(!rots.empty()){
            this->type = (this->type + stage)%4;
            if(this->type < 0) this->type = 3 ;
            erase_object();
            forms = rots[type];
            AddObjectinMap();

        }
    }
    bool check_nextpiece(){
        if(!rots.empty()){
            int ntype = (this->type + 1)%4;
            vector<pair<int,int>>cord;
            cord = rots[ntype];
            for(int i = 0 ; i < cord.size(); i++){
                if(pxy[cord[i].first+curr_posy][cord[i].second+curr_posx])
                    return false;

            }
            return true;
        }else return false;
    }




};



void print_start(){
    ifstream myGame("start.txt");
    string line;
    if(myGame.is_open()){
        while(getline(myGame,line)){
            cout << line << endl;
        }
        myGame.close();
    }
}
void ClearScreen(){
    system("CLS");
}
void print_arena(){
    for(int i = 0 ; i < arena.size() ; i++ ){
        cout << arena[i] << endl;
    }
}
void create_arena(){
    fill(col.begin(),col.end(),2);
    ifstream Arena("cage.txt");
    if(Arena.is_open()){
        for(int i = 0 ; i < 16 ; i ++){
            string temp;
            getline(Arena,temp);
            arena.push_back(temp);

        }
        Arena.close();
    }
    for(int i = 0 ; i < arena.size() ; i++){
        for(int j = 0 ; j < arena[0].size(); j++){
            if(arena[i][j]=='*'){
                pxy[i][j] = true;
            }
        }
    }

}
void map_update(int bottom,int length,Object & obj){

    int top = bottom - length;

    int botcpy = bottom;
    for(int line = top; line >= 1 ; line --){
        arena[botcpy] = arena[line];
        for(int stars = 0 ; stars < arena[0].size(); stars++){
            pxy[botcpy][stars] = pxy[line][stars];

        }

        col[botcpy] = col[line];
        botcpy --;
    }
    obj.Move(1,0);
    obj.Move(-1,0);

}
void map_check(Object & obj){
    int bottom = 0;
    int length = 0;
    for(int line = 0 ; line < col.size()-1 ; line++){
        if(!(col[line]<arena[0].size())){
            arena[line] = "*                  *";
            col[line] = 2;

            if(bottom < line){ bottom = line; length++; }
        }
    }

    if(length > 0){
        map_update(bottom,length,obj);
        score = score + (fscore[length]*100)*level*combo;
        combo++;

    }else combo = 1;

}
void print_scoreboard(){
    ifstream tabel("Scoreboard.txt");
    string line;
    if(tabel.is_open()){
        while(getline(tabel,line)){
            cout << line << endl;
        }
        tabel.close();

    }
}
void main_menu(){
    string line;
    ifstream optionfile("options.txt");
    if(optionfile.is_open()){
        for(int j = 0 ; j <= 2 ; j++){
            vector<string> list;
            for(int i = 0 ; i <= 2 ; i++){
                getline(optionfile,line);
                list.push_back(line);
            }
            options.push_back(list);
        }

    }

}


struct myComp{
    bool operator()(pair<string,int> & a,pair<string,int> & b){
        return(a.second < b.second);
    }
};
void fsort(){
    ifstream flist("Stats.txt");
    string line;
    priority_queue<pair<string,int>,vector<pair<string,int>>,myComp> q;

    if(flist.is_open()){
        while(getline(flist,line)){
            string name;
            string str_score;
            name = line.substr(0,line.find(":")+1);
            str_score = line.substr(line.find(":")+1,line.size());
            int num = stoi(str_score);
            q.push(make_pair(name,num));

        }
        flist.close();
    }

    ifstream tabel("Scoreboard.txt");
    if(tabel.is_open()){
        int j = 0 ;
        getline(tabel,line);
        cout << line << endl;
        getline(tabel,line);
        cout << line << endl;
        while(getline(tabel,line)){
            if(!q.empty() && j < 6){
                string playerstats;

                line[1] = char(j+49);
                line[2] = '.';

                stringstream ss;
                ss << q.top().second;
                string num ;
                ss >> num;

                int st = 3;
                playerstats = q.top().first + num;
                for(int i = 0 ; i < playerstats.size() ; i ++){
                    line[st] = playerstats[i];
                    st++;
                }


                q.pop();
                j++;
            }
            cout << line << endl;
        }

        tabel.close();
    }



}
void set_player(){
    cout << "Please write your name before we can start:";
    cin >> name;
}
void print_nextpiece(int nextobj){
    cout <<"Next piece:"<<endl;
    vector<pair<int,int>>v = Object(nextobj).forms;
    char mat[4][4];
    for(int i = 0 ; i < 4 ; i ++){
        for(int j = 0 ; j < 4 ; j ++){
            mat[i][j] = ' ';
        }
    }
    for(int i = 0 ; i < v.size() ; i++){
        mat[v[i].first+1][v[i].second+1] = '*';
    }
    for(int i = 0 ; i < 4 ; i ++){
        for(int j = 0 ; j < 4 ; j ++){
            cout << mat[i][j] ;
        }cout << endl;
    }



}
void start(int i){
    if(i == 0){
    char s;
    int pos = 0;
    while(1){
        print_start();
        for(int i = 0 ; i <= 2 ; i++){
            cout << options[pos][i] << endl;
        }

        s = getch();
        if(s == 's'){ pos = (pos + 1) % 3; }
        else if(s == 'w'){
            pos = pos - 1;
            if(pos < 0) pos = 2 ;
        }else if( s == 'x'){
            switch(pos){
                case 0:
                    start(1);
                    break;
                case 1:
                    return;
                    break;
                case 2:
                    start(2);
                    break;

            }
        }

        ClearScreen();
    }
    }else if(i == 1){

        set_player();
        int nextobject = rand()%numofshapes;
        Object obj(rand()%numofshapes);
        obj.AddObjectinMap();
        char cmd = '\0';

        while(1){


            srand (time(NULL));
            ClearScreen();
            print_arena();
            cout << "Score:" << score << endl;
            print_nextpiece(nextobject);
            cout << "Level" << level;
            cmd = getch();


            if(cmd == 'a' && obj.check(0,-1)){
                obj.Move(0,-1);
            }else if(cmd == 'd' && obj.check(0,1)){
                obj.Move(0,1);
            }
            else if(cmd == 's'){
                if(obj.check(1,0)){
                    score++;
                    obj.Move(1,0);

                }else{
                    for(int i = 0 ; i < obj.forms.size() ; i++){
                        if(pxy[obj.curr_posy+obj.forms[i].first][obj.curr_posx+obj.forms[i].second]==false){
                        pxy[obj.curr_posy+obj.forms[i].first][obj.curr_posx+obj.forms[i].second] = true;
                        col[obj.curr_posy+obj.forms[i].first]++;
                        }else{
                            ofstream g;
                            g.open("Stats.txt", std::ios_base::app);
                            obj.AddObjectinMap();
                            cout << "~~~~GAME OVER~~~~";
                            g<<name<<":"<<score<<endl;

                            exit(0);
                        }

                    }
                    Object tempobj(nextobject);
                    nextobject = rand()%numofshapes;
                    obj = tempobj;
                    obj.AddObjectinMap();
                    map_check(obj);



                }
            }else if(cmd == 'r' && obj.check_nextpiece()){
                    obj.Rotate(1);
            }else if(cmd == 'q'&& obj.check_nextpiece()){
                    obj.Rotate(-1);
            }



            _sleep(100);


        }
    }else if(i == 2){
        char cmd = '/0';
        ClearScreen();
        fsort();
        cmd = getch();



    }
}

int main(){


    create_arena();
    main_menu();
    start(0);
    return 0;

}
