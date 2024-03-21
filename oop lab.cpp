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

    void loadFromFile(const string& filename, list<Course*>& allCourses) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            if (getline(file, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                studentID = stoi(token);
                getline(ss, name, ',');
                getline(ss, email, ',');
                coursesEnrolled.clear();
                while (getline(ss, token, ',')) {
                    for (Course* course : allCourses) {
                        if (course->getCourseName() == token) {
                            coursesEnrolled.push_back(course);
                            break;
                        }
                    }
                }
                cout << "Student data loaded from " << filename << endl;
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }
};

class Teacher : public Person {
private:
    int teacherID;
    list<Course*> coursesTaught;

public:
    Teacher(int id, string n, string e) : Person(n, e), teacherID(id) {}

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses();

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << teacherID << "," << name << "," << email << ",";
            for (const Course* course : coursesTaught) {
                file << course->getCourseName() << ",";
            }
            file.close();
            cout << "Teacher data saved to " << filename << endl;
        }
        else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadFromFile(const string& filename, list<Course*>& allCourses) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            if (getline(file, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                teacherID = stoi(token);
                getline(ss, name, ',');
                getline(ss, email, ',');
                coursesTaught.clear();
                while (getline(ss, token, ',')) {
                    for (Course* course : allCourses) {
                        if (course->getCourseName() == token) {
                            coursesTaught.push_back(course);
                            break;
                        }
                    }
                }
                cout << "Teacher data loaded from " << filename << endl;
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }
};
