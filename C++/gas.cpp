#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
class city{
    public:
    int name;
    bool visited;
    vector<city*> geitonas;
    city(){
        name=0;
    }
    city(int a){
        name=a;
        visited=false;
    }
};
class street{
    public:
    int city1,city2,gas;
    street(){
        city1=city2=gas=0;
    }
    street(int u,int v,int w){
        city1=u;
        city2=v;
        gas=w;
    }
    bool operator<(street a){
        return gas<a.gas;
    }
};
class graph{
    public:
    vector<int>gas;
    void add(city &city1,city &city2,int g){
        city1.geitonas.push_back(&city2);
        city2.geitonas.push_back(&city1);
        gas.push_back(g);
    }
    void cut(city &city1,city &city2,int g){
        city1.geitonas.pop_back();
        city2.geitonas.pop_back();
        gas.pop_back();
    }
    bool go(city &city1){
        city1.visited=true;
        int k=0;
        if(city1.geitonas.size()==1){
            return false;
        }
        int s,i;
        s=city1.geitonas.size();
        for(i=0;i<s;i++){
            if((*city1.geitonas[i]).visited==false && (*city1.geitonas[i]).geitonas.size()>1){
                bool vi=go((*city1.geitonas[i]));
                if(vi==false){
                    (*city1.geitonas[i]).visited=false;
                }
            }
        }
        for(i=0;i<s;i++){
            if((*city1.geitonas[i]).visited==true){
                k=k+1;
            }
        }
        if(k>1){
            return true;
        }
        else {
            return false;
        }
    }
};
int main(int argc,const char *argv[]) {
    int n,m,u,v,w,i,c1,c2,arr,r,number;
    vector<int> numbers;
    ifstream infile(argv[1]);
    while(infile>>number){
        numbers.push_back(number);
    }
    n=numbers[0];
    m=numbers[1];
    //cout<<n<<" "<<m;
    graph mappie;
    street *streets;
    streets=new street[m];
    city *cities;
    cities=new city[n];
    for(i=0;i<n;i++){
        cities[i]=city(i+1);
    }
    int gr;
    int gr1=0;
    gr=numbers.size();
    for(i=2;i<gr;i=i+3){
        u=numbers[i];
        v=numbers[i+1];
        w=numbers[i+2];
        //cout<<u<<" "<<v<<" "<<w<<endl;
        streets[gr1]=street(u,v,w);
        gr1=gr1+1;
    }
    sort(streets,streets+m);
    c1=streets[0].city1;
    c2=streets[0].city2;
    mappie.add(cities[c1-1],cities[c2-1],streets[0].gas);
    i=1;
    arr=1;
    r=1;
    while(arr<n-1){
        int c1,c2,g;
        bool iscircle;
        c2=streets[r].city2;
        c1=streets[r].city1;
        g=streets[r].gas;
        r=r+1;
        mappie.add(cities[c1-1],cities[c2-1],g);
        iscircle=mappie.go(cities[c1-1]);
        for(i=0;i<n;i++){
            cities[i].visited=false;
        }
        if(iscircle==false){
            arr=arr+1;
        }
        if(iscircle==true){
            mappie.cut(cities[c1-1],cities[c2-1],g);
        }
    }
        cout<<mappie.gas[n-2]<<endl;
}        
