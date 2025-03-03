#include <iostream>
#include <vector>
using namespace std;
int N, M;
vector<int> num;
void add() {
    int x, y;
    cin >> x >> y;
    num.insert(num.begin() + x, y);
}
void erase() {
    int x;
    cin >> x;
    int size = num.size();
    num.erase(num.begin() + x - 1);
    num.resize(size - 1);
}

void (*func[3])( ) = { NULL,  add,  erase};
// add() is func[1](), and erase() is func[2]();

int main(){
    cin >> N >> M;
    num.resize(N);
    for (int i = 0; i < N; i++)
        cin >> num[i];
    while(M--) {
        int mode;
        cin >> mode;
        func[mode]();
    }
    for (int i = 0; i < num.size(); i++)
        cout << num[i] << " ";
}