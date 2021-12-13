//
// Created by Jens on 19.11.2021.
//

#ifndef BINARY_TREE_LAB_STUDENT_TEST_CLASS_H
#define BINARY_TREE_LAB_STUDENT_TEST_CLASS_H
class Student {
    static int latestId = 0;
    String name;
    int studentId;
    int age;
    int gpa;
public:
    Student(String name, int age)
        : name(name), age(age), gpa(0) {
        // student id auto increment
        studentId = ++latestId;
    }

    bool operator<(const Student& other) {
        return this->studentId < other.studentId;
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << student.name;
        return os;
    }

};
#endif //BINARY_TREE_LAB_STUDENT_TEST_CLASS_H
