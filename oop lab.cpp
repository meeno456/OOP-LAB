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
/ Enroll the student in the course
coursesEnrolled.push_back(course);
cout << "Student " << name << " enrolled in course " << course->getCourseCode() << "." << endl;
}
void Student::dropCourse(Course* course) {
// Find the course in the list of enrolled courses
auto it = find(coursesEnrolled.begin(), coursesEnrolled.end(), course);
if (it != coursesEnrolled.end()) {
// Remove the course from the list
coursesEnrolled.erase(it);
cout << "Student " << name << " dropped course " << course->getCourseCode() << "." << endl;
}
else {
cout << "Student " << name << " is not enrolled in course " << course->getCourseCode() << "." <<
endl;
}
}
void Student::viewCourses() const {
cout << "Courses enrolled by student " << name << ":" << endl;
for (const auto& course : coursesEnrolled) {
cout << course->getCourseCode() << " - " << course->getCourseName() << endl;
}
}
void Student::saveToFile() const {
ofstream outFile(to_string(studentID) + ".txt");
if (outFile.is_open()) {
outFile << "Student ID: " << studentID << endl;
outFile << "Name: " << name << endl;
outFile << "Email: " << email << endl;
outFile << "Courses Enrolled:" << endl;
for (const auto& course : coursesEnrolled) {
outFile << course->getCourseCode() << " - " << course->getCourseName() << endl;
}
outFile.close();
cout << "Student data saved to file." << endl;
}
else {
cout << "Unable to save student data to file." << endl;
}
}
void Student::loadFromFile() {
ifstream inFile(to_string(studentID) + ".txt");
if (inFile.is_open()) {
string line;
while (getline(inFile, line)) {
stringstream ss(line);
string key, value;
ss >> key >> value;
if (key == "Student" && value == "ID:") {
ss >> studentID;
}
else if (key == "Name:") {
getline(ss, name);
name = name.substr(1);
}
else if (key == "Email:") {
ss >> email;
}
else if (key == "Courses" && value == "Enrolled:") {
while (getline(inFile, line)) {
stringstream course_ss(line);
string courseCode, courseName;
course_ss >> courseCode >> courseName;
Course* course = new Course(courseCode, courseName, 0); // Capacity not known from
file
coursesEnrolled.push_back(course);
}
}
}
inFile.close();
cout << "Student data loaded from file." << endl;
}
else {
cout << "Unable to load student data from file." << endl;
}
}
// Course methods
bool Course::addStudent(Student* student) {
if (studentsEnrolled.size() >= maxCapacity) {
cout << "Course " << courseCode << " is full. Cannot enroll more students." << endl;
return false;
}
for (const auto& enrolledStudent : studentsEnrolled) {
if (enrolledStudent == student) {
cout << "Student " << student->getName() << " is already enrolled in course " << courseCode
<< "." << endl;
return false;
}
}
studentsEnrolled.push_back(student);
cout << "Student " << student->getName() << " enrolled in course " << courseCode << "." << endl;
return true;
}
void Course::removeStudent(Student* student) {
auto it = find(studentsEnrolled.begin(), studentsEnrolled.end(), student);
if (it != studentsEnrolled.end()) {
studentsEnrolled.erase(it);
cout << "Student " << student->getName() << " removed from course " << courseCode << "." <<
endl;
}
else {
cout << "Student " << student->getName() << " is not enrolled in course " << courseCode << "."
<< endl;
}
}
