#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
int times,filename,num;//num is the number of files running behind
enum { FRONT, BACK, LIST, BLANK };
int Parse(const std::string command, int& filename) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    if (tokens.size() == 0)
        return BLANK;
    if (tokens[0][0] == '.' && tokens[0][1] == '/') {
        filename = std::stoi(tokens[0].substr(2));
        if (tokens.size() >= 2 && tokens[1][0] == '&') {
            return BACK;
        } else {
            return FRONT;
        }
    } else if (tokens[0][0] == 'l') {
        return LIST;
    } 
    return -1;
}
struct node{
    int name;
    int begintime;
    int endtime;
}nodes[105];
bool cmp(node a, node b){//输出的时候比较大小
    return a.endtime<b.endtime || (a.endtime==b.endtime && a.begintime<b.begintime);
}
int span(int x){
    if(x<4000)
        return 30;
    return x/10;
}
int main(){
    string command;
    while(getline(cin,command)){
        if(Parse(command,filename)==BLANK){
            times+=1;
        }else if(Parse(command,filename)==FRONT){
            if(filename<5000)
                cout<<filename<<endl;
            times+=span(filename);
        }else if(Parse(command,filename)==BACK){
            nodes[num].name=filename;
            nodes[num].begintime=times;
            nodes[num].endtime=times+span(filename);
            num++;
            times++;
        }else if(Parse(command,filename)==LIST){
//            sort(nodes,nodes+num,cmp);
            for(int i=0;i<num;i++){
                if(nodes[i].endtime>times)
                    cout<<nodes[i].name<<" back "<<(nodes[i].endtime-times)<<endl;
            }
            times++;
        }
    }
    return 0;
}