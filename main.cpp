#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Student {
public:
    string name;
    int id;
    vector<float> grades;

    Student(string n, int i) : name(n), id(i) {}

    void addGrade(float grade) {
        grades.push_back(grade);
    }

    float getAverageGrade() {
        float sum = 0;
        for (float grade : grades) {
            sum += grade;
        }
        return grades.empty() ? 0 : sum / grades.size();
    }

    float getGPA() {
        float average = getAverageGrade();
        if (average >= 90) return 4.0;
        if (average >= 80) return 3.0;
        if (average >= 70) return 2.0;
        if (average >= 60) return 1.0;
        return 0.0;
    }
};

vector<Student> students;

void addStudent() {
    string name;
    int id;
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter student ID: ";
    cin >> id;
    cin.ignore(); // Clear newline character from the input buffer
    students.push_back(Student(name, id));
    cout << "Student added successfully.\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    for (const auto& student : students) {
        cout << "Name: " << student.name << ", ID: " << student.id << endl;
    }
}

void editStudent() {
    int id;
    cout << "Enter student ID to edit: ";
    cin >> id;
    cin.ignore(); // Clear newline character from the input buffer

    for (auto& student : students) {
        if (student.id == id) {
            cout << "Editing student " << student.name << endl;
            cout << "Enter new name (leave blank to keep current): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                student.name = newName;
            }

            float grade;
            cout << "Enter grades (enter -1 to finish): ";
            student.grades.clear();
            while (cin >> grade && grade != -1) {
                student.addGrade(grade);
            }
            cin.ignore(); // Clear newline character from the input buffer

            cout << "Student updated successfully.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void generateReportCards() {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    cout << setw(20) << left << "Name" << setw(10) << left << "ID" << setw(15) << left << "Average Grade" << setw(10) << left << "GPA" << endl;
    for (const auto& student : students) {
        cout << setw(20) << left << student.name
             << setw(10) << left << student.id
             << setw(15) << left << fixed << setprecision(2) << student.getAverageGrade()
             << setw(10) << left << fixed << setprecision(2) << student.getGPA() << endl;
    }
}

void saveData() {
    ofstream file("students.dat", ios::binary);
    size_t size = students.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& student : students) {
        size_t nameLength = student.name.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(student.name.c_str(), nameLength);
        file.write(reinterpret_cast<const char*>(&student.id), sizeof(student.id));

        size_t gradesSize = student.grades.size();
        file.write(reinterpret_cast<const char*>(&gradesSize), sizeof(gradesSize));
        file.write(reinterpret_cast<const char*>(student.grades.data()), gradesSize * sizeof(float));
    }
    file.close();
}

void loadData() {
    ifstream file("students.dat", ios::binary);
    if (!file) return;

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    students.resize(size);

    for (auto& student : students) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        student.name.resize(nameLength);
        file.read(&student.name[0], nameLength);
        file.read(reinterpret_cast<char*>(&student.id), sizeof(student.id));

        size_t gradesSize;
        file.read(reinterpret_cast<char*>(&gradesSize), sizeof(gradesSize));
        student.grades.resize(gradesSize);
        file.read(reinterpret_cast<char*>(student.grades.data()), gradesSize * sizeof(float));
    }
    file.close();
}

int main() {
    loadData();
    int choice;

    do {
        cout << "1. Add Student\n2. View Students\n3. Edit Student\n4. Generate Report Cards\n5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from the input buffer

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: editStudent(); break;
            case 4: generateReportCards(); break;
            case 5: saveData(); cout << "Data saved. Exiting...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
