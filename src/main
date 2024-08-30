#include <iostream>
#include <vector>
#include "Student.h"
#include "Utility.h"

using namespace std;

int main() {
    vector<Student> students;
    loadData(students);
    int choice;

    do {
        cout << "1. Add Student\n2. View Students\n3. Edit Student\n4. Generate Report Cards\n5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from the input buffer

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: viewStudents(students); break;
            case 3: editStudent(students); break;
            case 4: generateReportCards(students); break;
            case 5: saveData(students); cout << "Data saved. Exiting...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
