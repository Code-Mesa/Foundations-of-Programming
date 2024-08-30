#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
public:
    std::string name;
    int id;
    std::vector<float> grades;

    Student(std::string n, int i);
    void addGrade(float grade);
    float getAverageGrade() const;
    float getGPA() const;
};

#endif // STUDENT_H
