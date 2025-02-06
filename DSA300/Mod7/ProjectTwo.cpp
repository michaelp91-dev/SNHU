#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>  // For Hash Table
#include <algorithm>      // For sorting

using namespace std;

// --- Course Structure ---
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// --- Function Declarations ---
unordered_map<string, Course> loadCourseData(const string& filePath);
bool validateData(const unordered_map<string, Course>& courses);
void searchCourse(const unordered_map<string, Course>& courses, const string& courseNumber);
void printAllCourses(const unordered_map<string, Course>& courses);
int displayMenu();
bool compareCourses(const Course& course1, const Course& course2);


// --- Function Definitions ---

// --- displayMenu ---
int displayMenu() {
    int choice;
    cout << "--- Menu ---" << endl;
    cout << "1. Load Course Data" << endl;
    cout << "2. Print All Courses" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// --- loadCourseData ---
unordered_map<string, Course> loadCourseData(const string& filePath) {
    unordered_map<string, Course> courses;
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return courses; // Return empty map
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> lineValues;

        while (getline(ss, token, ',')) {
            lineValues.push_back(token);
        }

        if (lineValues.size() < 2) {
            cerr << "Error: Invalid line format in file." << endl;
            file.close();
            return unordered_map<string, Course>();  // Return empty
        }

        Course currentCourse;
        currentCourse.courseNumber = lineValues[0];
        currentCourse.courseName = lineValues[1];

        for (size_t i = 2; i < lineValues.size(); ++i) {
            currentCourse.prerequisites.push_back(lineValues[i]);
        }

        // Check for duplicate course numbers
        if (courses.find(currentCourse.courseNumber) != courses.end()) {
            cout << "Duplicate course number found: " + currentCourse.courseNumber << endl;
        } else {
            courses[currentCourse.courseNumber] = currentCourse; // Insert into map
        }
    }

    file.close();

    return courses;
}

// --- validateData ---
bool validateData(const unordered_map<string, Course>& courses) {
    for (const auto& pair : courses) {
        const Course& course = pair.second;
        for (const string& prerequisite : course.prerequisites) {
            if (courses.find(prerequisite) == courses.end()) {
                cerr << "Error: Prerequisite '" << prerequisite << "' for course '"
                     << course.courseNumber << "' does not exist." << endl;
                return false;
            }
        }
    }
    return true;
}

// --- searchCourse ---
void searchCourse(const unordered_map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);

    if (it != courses.end()) {
        const Course& course = it->second;
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Name: " << course.courseName << endl;
        cout << "Prerequisites: ";

        if (course.prerequisites.empty()) {
            cout << "None" << endl;
        } else {
            for (const string& prereq : course.prerequisites) {
                cout << prereq << " " ;
            }
        cout << endl;
        }
    } else {
        cout << "Error: Course with number " << courseNumber << " not found." << endl;
    }
}

// --- printAllCourses ---
bool compareCourses(const Course& course1, const Course& course2) {
    return course1.courseNumber < course2.courseNumber;
}

void printAllCourses(const unordered_map<string, Course>& courses) {
    // Copy courses into a vector for sorting
    vector<Course> sortedCourses;
    for (const auto& pair : courses) {
        sortedCourses.push_back(pair.second);
    }

    // Sort the vector
    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

    // Print the sorted courses
    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << " " << course.courseName << endl;
    }
}

// --- Main Function ---
int main() {
    unordered_map<string, Course> courses; // Data structure to store courses
    int menuChoice;
    string filePath;
    string courseNumber;

    do {
        menuChoice = displayMenu();

        switch (menuChoice) {
            case 1:
                cout << "Enter the course file path: ";
                cin >> filePath;
                courses = loadCourseData(filePath);

                if (!courses.empty()) {
                    cout << "Course data loaded." << endl;
                    validateData(courses);
                } else {
                    cout << "Failed to load course data." << endl;
                }
                break;
            case 2:
                printAllCourses(courses);
                break;
            case 3:
                cout << "Enter course number to search: ";
                cin >> courseNumber;
                searchCourse(courses, courseNumber);
                break;
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (menuChoice != 9);

    return 0;
}
