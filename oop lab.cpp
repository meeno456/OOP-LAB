#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Course; 

class Person {
protected:
    string name;
    string email;

public:
    Person(string n, string e) : name(n), email(e) {}
};

class Student : public Person {
private:
    int studentID;
    list<Course*> coursesEnrolled;

public:
    Student(int id, string n, string e) : Person(n, e), studentID(id) {}

    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses();

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << studentID << "," << name << "," << email << ",";
            for (const Course* course : coursesEnrolled) {
                file << course->getCourseName() << ",";
            }
            file.close();
            cout << "Student data saved to " << filename << endl;
        }
        else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
