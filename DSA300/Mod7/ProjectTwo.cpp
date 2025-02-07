#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>  // For Hash Table
#include <algorithm>      // For sorting
#include <cctype> // Required for std::tolower
#include <iomanip>

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

// --- Helper function to convert a string to lowercase ---
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// --- Main Function ---
int main() {
    unordered_map<string, Course> courses; // Data structure to store courses
    int menuChoice;
    string filePath;
    string courseNumber;
    bool dataIsValid = false; // Flag to track data validity

    do {
        menuChoice = displayMenu();

        switch (menuChoice) {
            case 1:
                cout << "Enter the course file path: ";
                cin >> filePath;
                courses = loadCourseData(filePath);

                if (!courses.empty()) {
                    cout << "Course data loaded." << endl;
                    dataIsValid = validateData(courses); // Validate the data

                    if (dataIsValid) {
                        cout << "Data is valid." << endl;
                    } else {
                        cout << "Data is invalid. Please check the file." << endl;
                        courses.clear(); // Clear the data if invalid
                    }
                } else {
                    cout << "Failed to load course data." << endl;
                }
                break;
            case 2:
                if (dataIsValid) { // Only allow if data is valid
                    printAllCourses(courses);
                } else {
                    cout << "Error: Load and validate course data first." << endl;
                }
                break;
            case 3:
                if (dataIsValid) { // Only allow if data is valid
                    cout << "Enter course number to search: ";
                    cin >> courseNumber;
                    searchCourse(courses, courseNumber);
                } else {
                    cout << "Error: Load and validate course data first." << endl;
                }
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
    string lowercaseCourseNumber = toLowercase(courseNumber);

    for (const auto& pair : courses) {
        string lowercaseStoredNumber = toLowercase(pair.first); // Convert stored course number to lowercase

        if (lowercaseStoredNumber == lowercaseCourseNumber) {
            const Course& course = pair.second;

            cout << "\n--- Course Information ---" << endl;
            cout << "Course Number: " << course.courseNumber << endl;
            cout << "Course Name: " << course.courseName << endl;

            cout << "Prerequisites: ";
            if (course.prerequisites.empty()) {
                cout << "None" << endl;
            } else {
                // Print prerequisites comma-separated on one line
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    const string& prereq = course.prerequisites[i];
                    auto it2 = courses.find(prereq);
                    if (it2 != courses.end()) {
                        cout << prereq << " " << it2->second.courseName;
                    } else {
                        cout << prereq << " (Not Found)";
                    }

                    if (i < course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            cout << endl;
            return;  // Course found and printed, exit function
        }
    }

    cout << "Error: Course with number " << courseNumber << " not found." << endl;
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

    // Print the sorted courses with formatting
    cout << "\n--- Course List ---" << endl;
    cout << left << setw(10) << "Number" << setw(40) << "Name" << endl; // Header
    cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl; // Separator line

    for (const Course& course : sortedCourses) {
        cout << left << setw(10) << course.courseNumber << setw(40) << course.courseName << endl;
    }

    cout << endl;
}
