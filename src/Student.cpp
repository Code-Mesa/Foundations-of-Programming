#include "Student.h"

Student::Student(std::string n, int i) : name(n), id(i) {}

void Student::addGrade(float grade) {
    grades.push_back(grade);
}

float Student::getAverageGrade() const {
    float sum = 0;
    for (float grade : grades) {
        sum += grade;
    }
    return grades.empty() ? 0 : sum / grades.size();
}

float Student::getGPA() const {
    float average = getAverageGrade();
    if (average >= 90) return 4.0;
    if (average >= 80) return 3.0;
    if (average >= 70) return 2.0;
    if (average >= 60) return 1.0;
    return 0.0;
}
