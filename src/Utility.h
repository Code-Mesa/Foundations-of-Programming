#ifndef UTILITY_H
#define UTILITY_H

#include "Student.h"
#include <vector>

void addStudent(std::vector<Student> &students);
void viewStudents(const std::vector<Student> &students);
void editStudent(std::vector<Student> &students);
void generateReportCards(const std::vector<Student> &students);
void saveData(const std::vector<Student> &students);
void loadData(std::vector<Student> &students);

#endif // UTILITY_H
