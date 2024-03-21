#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

#include"course.h"

class Student {
private:
    int studentID;
    string name;
    vector<Course*> coursesEnrolled;

public:
    Student(int id, string n) : studentID(id), name(n) {}

    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses();

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << studentID << "," << name << ",";
            for (const Course* course : coursesEnrolled) {
                file << course->getCourseName() << ",";
            }
            file.close();
            cout << "Data of student is saved to " << filename << endl;
        }
        else {
            cout << "There is an error,not able to open file for writing." << endl;
        }
    }