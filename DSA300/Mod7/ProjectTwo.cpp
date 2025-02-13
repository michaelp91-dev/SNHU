/******************************************************************************
* Program: Advising Assistance Program
* Author: Michael Puckett
* Date: February 13, 2025
* Description: This program allows users to load course data from a file,
*              search for specific courses, and print out a list of courses.
*              It is designed to assist academic advisors in the Computer
*              Science department at ABCU.
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iomanip>   // Required for formatting output
#include <algorithm> // Required for std::sort
#include <cctype>    // Required for std::tolower

using namespace std;

// --- Course Structure ---
struct Course {
    string courseNumber;        // Unique identifier for the course (e.g., "CSCI101")
    string courseName;          // Name of the course (e.g., "Introduction to Programming")
    vector<string> prerequisites; // List of course numbers that are prerequisites
};

// --- Function Declarations ---
unordered_map<string, Course> loadCourseData(const string& filePath);
int displayMenu();
void printCourseData(const unordered_map<string, Course>& courses);
bool compareCourses(const Course& course1, const Course& course2);
bool validateData(const unordered_map<string, Course>& courses);
void searchCourse(const unordered_map<string, Course>& courses, const string& courseNumber);

// --- Helper function to convert a string to lowercase ---
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// --- Main Function ---
int main() {
    unordered_map<string, Course> courses; // Stores the course data (courseNumber -> Course object)
    int menuChoice;                        // Stores the user's menu selection
    string filePath;                         // Stores the path to the course data file
    string courseNumber;                     // Stores the course number to search for
    bool dataIsValid = false;              // Flag to indicate if the loaded data is valid

    do {
        menuChoice = displayMenu(); // Display the menu and get the user's choice

        if (menuChoice == -1) {
            continue; // If displayMenu() returned -1 (invalid input), skip to the next loop iteration
        }

        switch (menuChoice) {
            case 1: // Load Course Data
                cout << "Enter the course file path: ";
                cin.ignore();   // consume any stray newline characters from previous inputs
                getline(cin, filePath); //Use Getline

                courses = loadCourseData(filePath); // Load the course data from the file

                if (!courses.empty()) {
                    cout << "Course data loaded." << endl;
                    dataIsValid = validateData(courses); // Validate the loaded data
                    if (!dataIsValid) {
                        cout << "Error: Course Data is Invalid. Please check the course file" << endl;
                        courses.clear(); // Clear the data if it's invalid
                    }
                } else {
                    cout << "Failed to load course data." << endl;
                }
                break;
            case 2: // Search Course
                if (!courses.empty()) {
                    cout << "Enter course number to search: ";
                      cin.ignore();   // consume any stray newline characters from previous inputs
                     getline(cin, courseNumber);

                    searchCourse(courses, courseNumber); // Search for the course and display its information
                } else {
                    cout << "Error: Load course data first." << endl;
                }
                break;
            case 3: // Print Course Data
                printCourseData(courses); // Print all loaded course data
                break;
            case 9: // Exit
                cout << "Exiting..." << endl;
                break;
            default: // Invalid input
                cout << "Invalid choice." << endl;
        }
    } while (menuChoice != 9); // Continue looping until the user chooses to exit

    return 0;
}

// --- Function Definitions ---

// --- displayMenu ---
int displayMenu() {
    string input; //Store the menu input into a string
    int choice;   //Store the integer after it has been parsed

    cout << "--- Menu ---" << endl;
    cout << "1. Load Course Data" << endl;
    cout << "2. Search Course" << endl;
    cout << "3. Print Course Data" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
    getline(cin, input); // get input from the user

    // Attempt to convert the string to an integer
    stringstream ss(input);
    if (ss >> choice) {
        // Check if there's anything left in the string (to ensure it's *only* a number)
        if (ss.eof()) {
            return choice; // Valid integer input
        }
    }

    // Input is not a valid integer
    cout << "Incorrect input value. Please enter a menu choice." << endl;
    return -1;
}

// --- loadCourseData ---
unordered_map<string, Course> loadCourseData(const string& filePath) {
    unordered_map<string, Course> courses; // Hash map to store course data
    ifstream file(filePath);              // File stream to read the course data file
    string line;                           // String to store each line from the file

    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return courses; // Return empty map if file cannot be opened
    }

    while (getline(file, line)) {
        stringstream ss(line);         // Create a string stream from the line
        string token;                  // String to store each token (value) from the line
        vector<string> lineValues;    // Vector to store all values from the line

        while (getline(ss, token, ',')) { // Split the line by commas
            lineValues.push_back(token);    // add the item to the vector
        }

        if (lineValues.size() < 2) {
            cerr << "Error: Invalid line format in file." << endl;
            file.close();
            return unordered_map<string, Course>(); // Return empty map if line is invalid
        }

        string strPrereq; //Create a string object
        Course currentCourse;                 // Course object
        currentCourse.courseNumber = lineValues[0]; // course number from the first element in the vector
        currentCourse.courseName = lineValues[1];   // course name from the second element in the vector
        strPrereq = lineValues[2]; //Create a string object for the prerequsite
        bool bStrCheck = strPrereq.empty(); //Check if it is empty.
        if (!bStrCheck) {
            for (size_t i = 2; i < lineValues.size(); ++i) {
                currentCourse.prerequisites.push_back(lineValues[i]); //Iterate through the other elements
            }
        }

        // Check for duplicate course numbers
        if (courses.find(currentCourse.courseNumber) != courses.end()) {
            cout << "Duplicate course number found: " + currentCourse.courseNumber << endl;
        } else {
            courses[currentCourse.courseNumber] = currentCourse; // Insert into map
        }
    }

    file.close(); //Close the file

    return courses;
}

// --- printCourseData ---
bool compareCourses(const Course& course1, const Course& course2) {
    return course1.courseNumber < course2.courseNumber;
}

//Print the course in a cleaned and formatted manner:
void printCourseData(const unordered_map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "Please load the course data first." << endl;
        return;
    }

    vector<Course> sortedCourses;
    for (const auto& pair : courses) {
        sortedCourses.push_back(pair.second);
    }

    // Sort the vector
    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

    // Output the header, this will help the user understand what each column represents.
    cout << "\n--- Course Information ---" << endl;
    cout << left << setw(10) << "Number" << setw(40) << "Name" << "Prerequisites" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl; //Print a line

    for (const Course& course : sortedCourses) {
        cout << left << setw(10) << course.courseNumber << setw(40) << course.courseName; //Format
        if (course.prerequisites.empty()) { //Print none if there are none
            cout << "None" << endl;
        } else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) { //Output the elements and connect them with a line
                cout << course.prerequisites[i] << " ";
            }
            cout << endl;
        }
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

// --- searchCourse ---
void searchCourse(const unordered_map<string, Course>& courses, const string& courseNumber) {
    string lowercaseCourseNumber = toLowercase(courseNumber); //The course that the user inputs is set to lowercase for comparison.
    
    for (const auto& pair : courses) {
        string lowercaseStoredNumber = toLowercase(pair.first); // Convert stored course number to lowercase

        if (lowercaseStoredNumber == lowercaseCourseNumber) {
            const Course& course = pair.second;
              cout << "\n--- Course Information ---" << endl; //If the file is found
            cout << "Course Number: " << course.courseNumber << endl;   //Print the course number
            cout << "Course Name: " << course.courseName << endl;       //Print the course name

            cout << "Prerequisites: ";                                //The next section is to check and implement the prequisites.
            if (course.prerequisites.empty()) {                     //If there are no prequisites, then show none.
                cout << "None" << endl;
            } else {
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {      //Loop through each prerequistic and print the courses,
                    const string& prereq = course.prerequisites[i];   //The prequisites are then seperated via a comma for a better view.
                    cout << prereq;
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

    cout << "Error: Course with number " << courseNumber << " not found." << endl; //If the course can't be found at the number
}