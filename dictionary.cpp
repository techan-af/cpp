#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    string word;
    string meaning;
    Node * next;

    public:
    Node(){
        this->word = "";
        this->meaning = "";
        this->next = NULL;
    }

    Node(string word,string meaning){
        this->word = word;
        this->meaning = meaning;
        this->next = NULL;
    }
};

class hashing : public Node{
    public:
    Node* record[10];

    hashing(){
        for(int i=0;i<10;i++){
            record[i] = NULL;
        }
    }

    int hashfunc(string word){
        int val = 0;
        for(int i=0;i<word.length();i++){
            val+=(word[i]-'a'+1);
        }

        return val%10;
    }

    void insert(string word, string meaning){

        int index = hashfunc(word);
        Node * temp = new Node(word,meaning);
        if(record[index] == NULL){
            record[index] = temp;
        }else{
            Node * chain = record[index];
            record[index] = temp;
            record[index]->next = chain;
        }

    }

    void search(string s){
        int index = hashfunc(s)%10;
        Node* temp = record[index];
        while(temp->word!=s and temp!=NULL){
            temp = temp->next;
        }

        if(temp!=NULL){
            cout<<"Word Found : " << s <<" Meaning is : "<<temp->meaning <<" ";
        }else{
            cout<<"Not Found ";
        }

        cout << endl;
    }

    void display(){
        for(int i=0;i<10;i++){
            cout << "Record at Index " << i << " : ";
            Node * temp = record[i];
            while(temp!=NULL){
                cout << temp->word << "->" << temp->meaning << "   ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main(){

    hashing h1;

    h1.insert("abc","bc");
    h1.insert("bca","bc");
    h1.display();

    h1.search("abc");
}