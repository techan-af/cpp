#include<bits/stdc++.h>
using namespace std;

struct student{

    public:
    int rollno;
    string name;
    string division;
    string address;
};

void addstudentinfo(int r, string n, string d, string a){

    student s1;
    s1.rollno = r;
    s1.name = n;
    s1.division = d;
    s1.address = a;

    ofstream outfile("data.txt",ios::app);
    if(outfile.is_open()){
        outfile << s1.rollno <<"," << s1.name <<"," << s1.division << "," << s1.address << "," << endl;
        outfile.close();
    }else{
        cerr << "Error opening file "<<endl;
    }
}

void editstudentinfo(int rn){
    ifstream infile("data.txt");
    if (!infile.is_open()) {
        cerr << "Error opening file " << endl;
        return;
    }

    ofstream tempfile("temp.txt");
    if (!tempfile.is_open()) {
        cerr << "Error opening file " << endl;
        return;
    }

    bool found = false;
    string line;

    while (getline(infile, line)) {
        stringstream ss(line);
        string field;
        student stu;

        getline(ss, field, ',');
        stu.rollno = stoi(field);

        // Parse name
        getline(ss, stu.name, ',');

        // Parse division
        getline(ss, stu.division, ',');

        // Parse address
        getline(ss, stu.address);

        // Check if the roll number matches
        if (stu.rollno == rn) {
            found = true;
            cout << "Enter new details (rollno, name, division, address): " << endl;
            int r;
            string n, d, a;
            cin >> r;
            cin.ignore(); // Clear newline character
            getline(cin, n);
            getline(cin, d);
            getline(cin, a);

            // Update student information
            stu.rollno = r;
            stu.name = n;
            stu.division = d;
            stu.address = a;
        }

        // Write updated student data to the temp file
        tempfile << stu.rollno << ", " << stu.name << ", " << stu.division << ", " << stu.address << endl;
    }

    // Close files
    infile.close();
    tempfile.close();

    // Replace the original file with the temp file
    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (found) {
        cout << "Student edited successfully." << endl;
    } else {
        cout << "No student found with roll number " << rn << "." << endl;
    }

}

void searching(int rn){
    ifstream infile("data.txt");

    string line;

    while(getline(infile,line)){
        stringstream ss(line);
        string field;
        student stu;

        getline(ss,field,',');
        stu.rollno = stoi(field);

        getline(ss,stu.name,',');
        getline(ss,stu.division,',');
        getline(ss,stu.address,',');

        if(stu.rollno == rn){
            cout << "Found " << endl;
            cout << stu.rollno <<"-" << stu.name << "-" << stu.division <<"-" << stu.address << endl;
        }
    }

    infile.close();
    
}

void deleting(int rn){
 ifstream infile("data.txt");
    if (!infile.is_open()) {
        cerr << "Error opening file " << endl;
        return;
    }

    ofstream tempfile("temp.txt");
    if (!tempfile.is_open()) {
        cerr << "Error opening file " << endl;
        return;
    }

    bool found = false;
    string line;

    while (getline(infile, line)) {
        stringstream ss(line);
        string field;
        student stu;

        getline(ss, field, ',');
        stu.rollno = stoi(field);

        // Parse name
        getline(ss, stu.name, ',');

        // Parse division
        getline(ss, stu.division, ',');

        // Parse address
        getline(ss, stu.address);

        // Check if the roll number matches
        if (stu.rollno == rn) {
            continue;
        }

        // Write updated student data to the temp file
        tempfile << stu.rollno << ", " << stu.name << ", " << stu.division << ", " << stu.address << endl;
    }

    // Close files
    infile.close();
    tempfile.close();

    // Replace the original file with the temp file
    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (found) {
        cout << "Student deleted successfully." << endl;
    } else {
        cout << "No student found with roll number " << rn << "." << endl;
    }
}

void displaying(){
    ifstream infile("data.txt");

    string line;

    while(getline(infile,line)){
        stringstream ss(line);
        string field;
        student stu;

        getline(ss,field,',');
        stu.rollno = stoi(field);

        getline(ss,stu.name,',');
        getline(ss,stu.division,',');
        getline(ss,stu.address,',');

        cout << stu.rollno <<"-" << stu.name << "-" << stu.division <<"-" << stu.address << endl;
        
    }

    infile.close();
}

void MENU(){
    cout << "------MENU---------" << endl;
    cout << "Enter 1 for adding " << endl;
    cout << "Enter 2 for editing " << endl;
    cout << "Enter 3 for searching " << endl;
    cout << "Enter 4 for deleting " << endl;
    cout << "Enter 5 for displaying " << endl;
    cout << "Enter 6 for exiting " << endl;
    cout << "---------------------" << endl;
}

int main(){


    while(true){
        MENU();
        int choice; cout <<"Enter choice " ; cin>>choice;

        if(choice == 1){
            // adding 
            string name,division,address;
            int rollno;

            cin>>rollno;
            cin>>name;
            cin>>division;
            cin>>address;

            addstudentinfo(rollno,name,division,address);
            
        }else if(choice == 2){
            cout << "Enter rollno of student :  ";
            int rollno; cin>>rollno;
            editstudentinfo(rollno);

        }else if(choice == 3){
            cout << "Enter rollno of student :  ";
            int rollno; cin>>rollno;

            searching(rollno);

        }else if(choice == 4){
            cout << "Enter rollno of student :  ";
            int rollno; cin>>rollno;

            deleting(rollno);

        }else if(choice == 5){
            displaying();
        }else if(choice == 6){
            cout << "THANKS" << endl;
            break;
        }else{
            cout << "Enter right choice" << endl;
        }
    }
    
}