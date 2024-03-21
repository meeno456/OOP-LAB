#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;
// Forward declaration of Course class
class Course;
// Student class
class Student {
private:
int studentID;
string name;
string email;
vector<Course*> coursesEnrolled;
public:
// Constructor
Student(int id, const string& n, const string& e) : studentID(id), name(n), email(e) {}
// Getter methods
int getStudentID() const { return studentID; }
string getName() const { return name; }
string getEmail() const { return email; }
// Methods
void enrollCourse(Course* course);
void dropCourse(Course* course);
void viewCourses() const;
// File handling methods
void saveToFile() const;
void loadFromFile();
};
// Course class
class Course {
private:
string courseCode;
string courseName;
vector<Student*> studentsEnrolled;
int maxCapacity;
public:
// Constructor
Course(const string& code, const string& name, int capacity)
: courseCode(code), courseName(name), maxCapacity(capacity) {}
// Getter methods
string getCourseCode() const { return courseCode; }
string getCourseName() const { return courseName; }
/ Methods
bool addStudent(Student* student);
void removeStudent(Student* student);
void viewStudents() const;
// File handling methods
void saveToFile() const;
void loadFromFile();
};
// Teacher class
class Teacher {
private:
int teacherID;
string name;
string email;
vector<Course*> coursesTaught;
public:
// Constructor
Teacher(int id, const string& n, const string& e) : teacherID(id), name(n), email(e) {}
// Getter methods
int getTeacherID() const { return teacherID; }
string getName() const { return name; }
string getEmail() const { return email; }
// Methods
void assignCourse(Course* course);
void removeCourse(Course* course);
void viewCourses() const;
// File handling methods
void saveToFile() const;
void loadFromFile();
};
// Static counter for student ID generation
static int studentCounter = 1;
// Student methods
void Student::enrollCourse(Course* course) {
// Check if the student is already enrolled in the course
for (const auto& enrolledCourse : coursesEnrolled) {
if (enrolledCourse == course) {
cout << "Student " << name << " is already enrolled in course " << course->getCourseCode()
<< "." << endl;
return;
}
}
