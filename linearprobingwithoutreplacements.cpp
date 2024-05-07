#include<bits/stdc++.h>
using namespace std;

struct record{
    public:
    int rollno;
    int marks;
    int chain;
};

class hashing{
    public:
    record hashtable[10];
    int cnt = 0;

    public:

    hashing(){
        for(int i=0;i<10;i++){
            hashtable[i].rollno = 0;
            hashtable[i].marks = 0;
            hashtable[i].chain = -1;
        }
    }

    void insert(int r, int marks){
        int index = r%10;

        if(hashtable[index].rollno == 0){
            hashtable[index].rollno = r;
            hashtable[index].marks = marks;
            cout << "Data entered successfully" << endl;
            cout << "-------------------" << endl;
        }else{
           
           while(hashtable[index].chain != -1){
                index = hashtable[index].chain;
           }

           int rep = index;
           index++;
           index%=10;
           bool flag = false;

           while(index!= rep){
                if(hashtable[index].rollno == 0){
                    hashtable[index].rollno = r;
                    hashtable[index].marks = marks;
                    hashtable[rep].chain = index;
                    flag = true;
                    break;
                }else{
                    index++;
                    index%=10;
                }
           }

            if(flag) cout << "Data entered successfully" << endl;
            else cout << "Data not entered" << endl; 
        }
    }

    bool search(int r){
        int index = r%10;

        if(hashtable[index].rollno == r){
            return true;
        }

        int cnt = 0;
        if(hashtable[index].rollno != 0){
            while(hashtable[index].chain != -1 || cnt == 10){
                index = hashtable[index].chain;
                if(hashtable[index].rollno == r){
                    return true;
                }
                cnt++;
            }
        }

        if(hashtable[index].rollno == r){
            return true;
        }

        return false;
        
    }

    void deleterecord(int r){
        if(!search(r)){
            cout << "Record not present" << endl;
        }else{
           int index = r%10;
           if(hashtable[index].rollno == r){
                hashtable[index].chain = -1;
                hashtable[index].rollno = 0;
                hashtable[index].marks = 0;
                cout << "Record deleted" << endl;
                return;
            }
            int prev = index;

            while(hashtable[index].chain != -1 ){
                prev = index;
                index = hashtable[index].chain;
                if(hashtable[index].rollno == r){
                    if(hashtable[index].chain != -1 ){
                        hashtable[prev].chain = hashtable[index].chain;
                        hashtable[index].chain = -1;
                        hashtable[index].rollno = 0;
                        hashtable[index].marks = 0;
                    }else{
                        hashtable[prev].chain = -1;
                        hashtable[index].chain = -1;
                        hashtable[index].rollno = 0;
                        hashtable[index].marks = 0; 
                    }
                    cout << "Record deleted" << endl;
                    return;
                }
            }

            if(hashtable[index].rollno == r){
                if(hashtable[index].chain != -1 ){
                    hashtable[prev].chain = hashtable[index].chain;
                    hashtable[index].chain = -1;
                    hashtable[index].rollno = 0;
                    hashtable[index].marks = 0;
                }else{
                    hashtable[prev].chain = -1;
                    hashtable[index].chain = -1;
                    hashtable[index].rollno = 0;
                    hashtable[index].marks = 0; 
                }
            }
            
            cout << "Record deleted" << endl;

        }
    }

    void display(){
        cout << "RN  M    C" << endl; 
        for(int i=0;i<10;i++){
            cout << hashtable[i].rollno << "   " << hashtable[i].marks <<"   " << hashtable[i].chain << endl;
        }
        cout << endl;
    }
};


int main(){
    hashing h;
    h.display();
    cout << "-------------------" << endl;

    h.insert(13,45);
    h.insert(23,99);
    h.insert(33,69);
    h.insert(10,5);
    h.insert(9,4);
    h.insert(1,3);
    h.insert(9,12);

    h.display();
    cout << "-------------------" << endl;

    if(h.search(23)) cout << "Result found" << endl;
    else cout << "Not found" << endl;

    cout << "-------------------" << endl;

    h.deleterecord(23);
    h.deleterecord(9);

    cout << "-------------------" << endl;
    h.display();

}