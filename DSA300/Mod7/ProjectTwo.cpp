#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iomanip> // Required for formatting output
#include <algorithm> // Required for std::sort

using namespace std;

// --- Course Structure ---
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// --- Function Declarations ---
unordered_map<string, Course> loadCourseData(const string& filePath);
int displayMenu();
void printCourseData(const unordered_map<string, Course>& courses);
bool compareCourses(const Course& course1, const Course& course2);
bool validateData(const unordered_map<string, Course>& courses);

// --- Main Function ---
int main() {
    unordered_map<string, Course> courses;
    int menuChoice;
    string filePath;
    bool dataIsValid = false;

    do {
        menuChoice = displayMenu();

        switch (menuChoice) {
            case 1:
                cout << "Enter the course file path: ";
                cin >> filePath;
                courses = loadCourseData(filePath); // Load data into the structure

                if (!courses.empty()) {
                    cout << "Course data loaded." << endl;
                    dataIsValid = validateData(courses);
                    if (!dataIsValid) {
                        cout << "Error: Course Data is Invalid. Please check the course file" << endl;
                        courses.clear();
                    }
                } else {
                    cout << "Failed to load course data." << endl;
                }
                break;
            case 3:
                printCourseData(courses);
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

// --- Function Definitions ---

// --- displayMenu ---
int displayMenu() {
    int choice;
    cout << "--- Menu ---" << endl;
    cout << "1. Load Course Data" << endl;
    cout << "3. Print Course Data" << endl;
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
        string strPrereq;
        Course currentCourse;
        currentCourse.courseNumber = lineValues[0];
        currentCourse.courseName = lineValues[1];
        strPrereq = lineValues[2];
        bool bStrCheck = strPrereq.empty();
        if (!bStrCheck) {
            for (size_t i = 2; i < lineValues.size(); ++i) {
                currentCourse.prerequisites.push_back(lineValues[i]);
            }
        }
        // Add new course to data structure.
        if (courses.find(currentCourse.courseNumber) != courses.end()) {
            cout << "Duplicate course number found: " + currentCourse.courseNumber << endl;
        } else {
            courses[currentCourse.courseNumber] = currentCourse;
        }
    }

    file.close();

    return courses;
}

// --- printCourseData ---
bool compareCourses(const Course& course1, const Course& course2) {
    return course1.courseNumber < course2.courseNumber;
}

void printCourseData(const unordered_map<string, Course>& courses) {
    // Copy courses into a vector for sorting
    vector<Course> sortedCourses;
    for (const auto& pair : courses) {
        sortedCourses.push_back(pair.second);
    }

    // Sort the vector
    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

    // Print the formatted course data
    cout << "\n--- Course Information ---" << endl;
    cout << left << setw(10) << "Number" << setw(40) << "Name" << "Prerequisites" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

    // Print the prerequisites
    for (const Course& course : sortedCourses) {
        cout << left << setw(10) << course.courseNumber << setw(40) << course.courseName;
        bool isEmpty = course.prerequisites.empty();
        int preSize = course.prerequisites.size();
        if (!isEmpty) {
            for (int i = 0; i < preSize; i++) {
                cout << course.prerequisites[i];
                if (i < preSize - 2) {
                    cout << ", ";
                }
            }
        } else {
            cout << "None";
        }
        cout << endl;    
    }
}

// --- validateData ---
bool validateData(const unordered_map<string, Course>& courses) {
    vector<string> courseNumbers;
    for (const auto& pair: courses) {
        courseNumbers.push_back(pair.first);
    }

    for (const auto& pair : courses) {
        const Course& course = pair.second;
        bool isEmpty;
        isEmpty = course.prerequisites.empty();
        if (!isEmpty) {
            continue;
        }
        for (const string& prerequisite : course.prerequisites) {
            bool found = false;
            for (const string& courseNumber : courseNumbers) {
                if (prerequisite == courseNumber) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Error: Prerequisite " << prerequisite << " in course "
                << course.courseNumber << " does not exist." << endl;
                return false;
            }
        }
    }
    return true;
}
