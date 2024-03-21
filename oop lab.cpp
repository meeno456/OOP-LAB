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
void Course::viewStudents() const {
cout << "Students enrolled in course " << courseCode << ":" << endl;
for (const auto& student : studentsEnrolled) {
cout << student->getStudentID() << " - " << student->getName() << endl;
}
}
void Course::saveToFile() const {
ofstream outFile(courseCode + "_course.txt");
if (outFile.is_open()) {
outFile << "Course Code: " << courseCode << endl;
outFile << "Course Name: " << courseName << endl;
outFile << "Max Capacity: " << maxCapacity << endl;
outFile << "Students Enrolled:" << endl;
for (const auto& student : studentsEnrolled) {
outFile << student->getStudentID() << " - " << student->getName() << endl;
}
outFile.close();
cout << "Course data saved to file." << endl;
}
else {
cout << "Unable to save course data to file." << endl;
}
}
void Course::loadFromFile() {
ifstream inFile(courseCode + "_course.txt");
if (inFile.is_open()) {
string line;
while (getline(inFile, line)) {
stringstream ss(line);
string key, value;
ss >> key >> value;
if (key == "Course" && value == "Code:") {
ss >> courseCode;
}
else if (key == "Course" && value == "Name:") {
getline(ss, courseName);
courseName = courseName.substr(1);
}
else if (key == "Max" && value == "Capacity:") {
ss >> maxCapacity;
}
else if (key == "Students" && value == "Enrolled:") {
while (getline(inFile, line)) {
stringstream student_ss(line);
int studentID;
string studentName;
student_ss >> studentID;
getline(student_ss, studentName);
studentName = studentName.substr(1);
Student* student = new Student(studentID, studentName, "");
studentsEnrolled.push_back(student);
}
}
}
inFile.close();
cout << "Course data loaded from file." << endl;
}
else {
cout << "Unable to load course data from file." << endl;
}
}
// Teacher methods
void Teacher::assignCourse(Course* course) {
coursesTaught.push_back(course);
cout << "Course " << course->getCourseCode() << " assigned to teacher " << name << "." << endl;
}
void Teacher::removeCourse(Course* course) {
auto it = find(coursesTaught.begin(), coursesTaught.end(), course);
if (it != coursesTaught.end()) {
coursesTaught.erase(it);
cout << "Course " << course->getCourseCode() << " removed from teacher " << name << "." <<
endl;
}
else {
cout << "Course " << course->getCourseCode() << " is not assigned to teacher " << name << "."
<< endl;
}
}
void Teacher::viewCourses() const {
cout << "Courses taught by teacher " << name << ":" << endl;
for (const auto& course : coursesTaught) {
cout << course->getCourseCode() << " - " << course->getCourseName() << endl;
}
}
void Teacher::saveToFile() const {
ofstream outFile(to_string(teacherID) + "_teacher.txt");
if (outFile.is_open()) {
outFile << "Teacher ID: " << teacherID << endl;
outFile << "Name: " << name << endl;
outFile << "Email: " << email << endl;
outFile << "Courses Taught:" << endl;
for (const auto& course : coursesTaught) {
outFile << course->getCourseCode() << " - " << course->getCourseName() << endl;
}
outFile.close();
cout << "Teacher data saved to file." << endl;
}
else {
cout << "Unable to save teacher data to file." << endl;
}
}
void Teacher::loadFromFile() {
ifstream inFile(to_string(teacherID) + "_teacher.txt");
if (inFile.is_open()) {
string line;
while (getline(inFile, line)) {
stringstream ss(line);
string key, value;
ss >> key >> value;
if (key == "Teacher" && value == "ID:") {
ss >> teacherID;
}
else if (key == "Name:") {
getline(ss, name);
name = name.substr(1);
}
else if (key == "Email:") {
ss >> email;
}
else if (key == "Courses" && value == "Taught:") {
while (getline(inFile, line)) {
stringstream course_ss(line);
string courseCode, courseName;
course_ss >> courseCode >> courseName;
Course* course = new Course(courseCode, courseName, 0); // Capacity not known from
file
coursesTaught.push_back(course);
}
}
}
inFile.close();
cout << "Teacher data loaded from file." << endl;
}
else {
cout << "Unable to load teacher data from file." << endl;
}
}
int main() {
vector<Student> students;
vector<Course> courses;
vector<Teacher> teachers;
char choice;
do {
cout << "\nChoose an option:\n";
cout << "1. Add Student\n";
cout << "2. Add Course\n";
cout << "3. Add Teacher\n";
cout << "4. Display Info\n";
cout << "5. Exit\n";
cout << "Enter choice: ";
cin >> choice;
switch (choice) {
case '1': {
string name, email;
cout << "\nEnter student name: ";
cin >> name;
cout << "Enter student email: ";
cin >> email;
students.push_back(Student(studentCounter++, name, email));
break;
}
case '2': {
string code, name;
int capacity;
cout << "\nEnter course code: ";
cin >> code;
cout << "Enter course name: ";
cin >> name;
cout << "Enter max capacity: ";
cin >> capacity;
courses.push_back(Course(code, name, capacity));
break;
}
case '3': {
string name, email;
cout << "\nEnter teacher name: ";
cin >> name;
cout << "Enter teacher email: ";
cin >> email;
teachers.push_back(Teacher(teachers.size() + 1, name, email));
break;
}
case '4':
// Displaying Information
cout << "\nStudent Information:\n";
for (const auto& student : students) {
cout << "Student ID: " << student.getStudentID() << endl;
cout << "Name: " << student.getName() << endl;
cout << "Email: " << student.getEmail() << endl;
student.viewCourses();
cout << endl;
}
// Display course information
cout << "\nCourse Information:\n";
for (const auto& course : courses) {
cout << "Course Code: " << course.getCourseCode() << endl;
cout << "Course Name: " << course.getCourseName() << endl;
course.viewStudents();
cout << endl;
}
// Display teacher information
cout << "\nTeacher Information:\n";
for (const auto& teacher : teachers) {
cout << "Teacher ID: " << teacher.getTeacherID() << endl;
cout << "Name: " << teacher.getName() << endl;
cout << "Email: " << teacher.getEmail() << endl;
teacher.viewCourses();
cout << endl;
}
break;
case '5':
cout << "Exiting the program.\n";
return 0; // Exit the program
default:
cout << "Invalid choice. Please enter again.\n";
break;
}
} while (true);
// Save data to files
for (auto& student : students) {
student.saveToFile();
}
for (auto& course : courses) {
course.saveToFile();
}
for (auto& teacher : teachers) {
teacher.saveToFile();
}
cout << "Data saved to files." << endl;
// Load data from files
for (auto& student : students) {
student.loadFromFile();
}
for (auto& course : courses) {
course.loadFromFile();
}
for (auto& teacher : teachers) {
teacher.loadFromFile();
}
cout << "Data loaded from files." << endl;
// Display student information
cout << "\nStudent Information:\n";
for (const auto& student : students) {
cout << "Student ID: " << student.getStudentID() << endl;
cout << "Name: " << student.getName() << endl;
cout << "Email: " << student.getEmail() << endl;
student.viewCourses();
cout << endl;
}
// Display course information
cout << "\nCourse Information:\n";
for (const auto& course : courses) {
cout << "Course Code: " << course.getCourseCode() << endl;
cout << "Course Name: " << course.getCourseName() << endl;
course.viewStudents();
cout << endl;
}
// Display teacher information
cout << "\nTeacher Information:\n";
for (const auto& teacher : teachers) {
cout << "Teacher ID: " << teacher.getTeacherID() << endl;
cout << "Name: " << teacher.getName() << endl;
cout << "Email: " << teacher.getEmail() << endl;
teacher.viewCourses();
cout << endl;
}
return 0;
