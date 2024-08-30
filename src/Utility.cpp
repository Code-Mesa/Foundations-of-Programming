#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void addStudent(vector<Student> &students) {
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

void viewStudents(const vector<Student> &students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    for (const auto& student : students) {
        cout << "Name: " << student.name << ", ID: " << student.id << endl;
    }
}

void editStudent(vector<Student> &students) {
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

void generateReportCards(const vector<Student> &students) {
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

void saveData(const vector<Student> &students) {
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

void loadData(vector<Student> &students) {
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
