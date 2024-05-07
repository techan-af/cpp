#include <bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    int rollno;
    char name[50];
    char division;
    char address[100];

    Student() : rollno(0), division('A') {
        name[0] = '\0';
        address[0] = '\0';
    }

    void readFromConsole() {
        cout << "Enter roll number: ";
        cin >> rollno;
        cin.ignore();
        cout << "Enter name: ";
        cin.getline(name, sizeof(name));
        cout << "Enter division: ";
        cin >> division;
        cin.ignore();
        cout << "Enter address: ";
        cin.getline(address, sizeof(address));
    }

    void display() const {
        cout << "Roll No: " << rollno << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }

    // Calculate the position in the file
    streampos calculatePosition(int recordNumber) const {
        return static_cast<streampos>(sizeof(Student) * recordNumber);
    }
};

class StudentDatabase {
private:
    fstream file;

public:
    StudentDatabase(const string& filename) {
        file.open(filename, ios::in | ios::out | ios::binary | ios::app);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            exit(EXIT_FAILURE);
        }
    }

    ~StudentDatabase() {
        file.close();
    }

    void addStudent() {
        // Seek to the end of the file
        file.seekp(0, ios::end);
        Student student;
        student.readFromConsole();

        // Write student data to the file
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        cout << "Student added successfully!" << endl;
    }

    void editStudent(int rollno) {
        Student student;
        streampos pos = findStudent(rollno);
        if (pos == static_cast<streampos>(-1)) {
            cout << "Student not found!" << endl;
            return;
        }

        // Read the existing student data from the file
        file.seekg(pos);
        file.read(reinterpret_cast<char*>(&student), sizeof(Student));

        cout << "Editing student details:" << endl;
        student.display();

        // Read new student details
        cout << "\nEnter new details:" << endl;
        student.readFromConsole();

        // Seek to the position and write the updated student data
        file.seekp(pos);
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        cout << "Student details updated!" << endl;
    }

    void deleteStudent(int rollno) {
        Student student;
        streampos pos = findStudent(rollno);
        if (pos == static_cast<streampos>(-1)) {
            cout << "Student not found!" << endl;
            return;
        }

        // Read the existing student data
        file.seekg(pos);
        file.read(reinterpret_cast<char*>(&student), sizeof(Student));

        // Mark the student record as deleted
        student.rollno = -1;

        // Write the modified record back to the file
        file.seekp(pos);
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        cout << "Student deleted!" << endl;
    }

    void insertStudent(int position) {
        // Seek to the end of the file
        file.seekp(0, ios::end);
        streampos totalRecords = file.tellp() / sizeof(Student);

        if (position > totalRecords) {
            cout << "Position out of bounds!" << endl;
            return;
        }

        Student student;
        student.readFromConsole();

        if (position == totalRecords) {
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
            cout << "Student inserted at the end." << endl;
        } else {
            // Read records from the end to make space for the new student
            vector<Student> temp;
            for (int i = totalRecords - 1; i >= position; --i) {
                file.seekg(i * sizeof(Student), ios::beg);
                Student tempStudent;
                file.read(reinterpret_cast<char*>(&tempStudent), sizeof(Student));
                temp.push_back(tempStudent);
            }

            // Write the new student at the given position
            file.seekp(position * sizeof(Student), ios::beg);
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));

            // Write back the temporarily shifted records
            for (int i = temp.size() - 1; i >= 0; --i) {
                file.write(reinterpret_cast<const char*>(&temp[i]), sizeof(Student));
            }

            cout << "Student inserted at position " << position << "." << endl;
        }
    }

    void searchStudent(int rollno) {
        Student student;
        streampos pos = findStudent(rollno);
        if (pos == static_cast<streampos>(-1)) {
            cout << "Student not found!" << endl;
            return;
        }

        file.seekg(pos);
        file.read(reinterpret_cast<char*>(&student), sizeof(Student));
        cout << "Student found!" << endl;
        student.display();
    }

    streampos findStudent(int rollno) {
        // Search for a student by roll number
        file.seekg(0, ios::beg);
        Student student;
        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if (student.rollno == rollno) {
                // Return the position of the found student
                return file.tellg() - static_cast<streamoff>(sizeof(Student));
            }
        }
        // Return -1 if the student was not found
        return static_cast<streampos>(-1);
    }
};

int main() {
    string filename = "students.dat";
    StudentDatabase db(filename);

    int choice;
    int rollno, position;

    while (true) {
        cout << "\n1. Add Student" << endl;
        cout << "2. Edit Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Insert Student at Position" << endl;
        cout << "5. Search Student" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                cout << "Enter roll number of student to edit: ";
                cin >> rollno;
                db.editStudent(rollno);
                break;
            case 3:
                cout << "Enter roll number of student to delete: ";
                cin >> rollno;
                db.deleteStudent(rollno);
                break;
            case 4:
                cout << "Enter position to insert student: ";
                cin >> position;
                db.insertStudent(position);
                break;
            case 5:
                cout << "Enter roll number of student to search: ";
                cin >> rollno;
                db.searchStudent(rollno);
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
