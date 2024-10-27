#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Structure to represent a course
struct Course {
    string courseNumber;   // Course abbreviation, e.g., CSCI400
    string courseTitle;    // Course title, e.g., Large Software Development
    vector<string> prerequisites;  // List of prerequisites
};

// Map to hold the courses, keyed by course number
map<string, Course> courseMap;

// Convert string to uppercase for case-insensitive comparison
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Function to load courses from a file
void loadCourses(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq1, prereq2;

        // Read course number, title, and prerequisites (if present)
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        getline(ss, prereq1, ',');
        getline(ss, prereq2, ',');

        // Create a new course object
        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        // Add prerequisites if they exist
        if (!prereq1.empty()) {
            course.prerequisites.push_back(prereq1);
        }
        if (!prereq2.empty()) {
            course.prerequisites.push_back(prereq2);
        }

        // Insert the course into the course map
        courseMap[toUpper(courseNumber)] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Function to print the list of all courses in alphanumeric order
void printCourseList() {
    if (courseMap.empty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    cout << "Here is a sample schedule:" << endl;
    // Create a vector to sort the courses
    vector<string> courseNumbers;
    for (const auto& pair : courseMap) {
        courseNumbers.push_back(pair.first);
    }
    sort(courseNumbers.begin(), courseNumbers.end());

    // Print the sorted courses
    for (const string& courseNum : courseNumbers) {
        cout << courseMap[courseNum].courseNumber << ", " 
             << courseMap[courseNum].courseTitle << endl;
    }
}

// Function to print course information and prerequisites
void printCourseInfo(const string& courseNumber) {
    string upperCourseNumber = toUpper(courseNumber);

    if (courseMap.find(upperCourseNumber) != courseMap.end()) {
        Course course = courseMap[upperCourseNumber];
        cout << course.courseNumber << ", " << course.courseTitle << endl;

        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        } else {
            cout << "No prerequisites" << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    int choice = 0;
    string fileName, courseNumber;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        // Display menu
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        // Read choice as a string to avoid input issues
        string input;
        getline(cin, input);
        try {
            choice = stoi(input);
        } catch (invalid_argument&) {
            cout << input << " is not a valid option." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter the file name: ";
                getline(cin, fileName);
                loadCourses(fileName);
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);
                printCourseInfo(courseNumber);
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                return 0;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
