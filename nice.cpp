#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    string id;
    string name;
    double marks[6];
    double total;
    double average;
    string status;
};

string generateID(int num) {
    string id = "S";
    if (num < 10) id += "00" + string("int num");
    else if (num < 100) id += "0" + string("int num");
    else id += string("int num");
    return id;
}

bool loginSystem() {
    string username, password;
    int attempts = 0;
    const int MAX_ATTEMPTS = 4;

    while (attempts < MAX_ATTEMPTS) {
        cout << "=== LOGIN REQUIRED ===\n";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (username == "manuel" && password == "12345") {
            cout << "Login successful! Welcome, " << username << ".\n";
            return true;
        } else {
            attempts++;
            cout << "Invalid login! Attempts left: " << (MAX_ATTEMPTS - attempts) << "\n\n";
        }
    }

    cout << "You need assistance. Too many failed login attempts.\n";
    return false;
} 

int main() {
    if (!loginSystem()) {
        return 0;
    }

    const int NUM_STUDENTS = 8;
    const int NUM_MARKS = 6;
    Student students[NUM_STUDENTS];

    ofstream resultsFile("StudentResults.txt");
    ofstream emailsFile("Emails.txt");
    ofstream tagsFile("NameTags.txt");

    if (!resultsFile || !emailsFile || !tagsFile) {
        cout << "Error creating files!" << endl;
        return 1;
    }

    cout << "=== Coursework Evaluation System ===\n";

    for (int s = 0; s < NUM_STUDENTS; s++) {
        students[s].id = generateID(s + 1);

        cout << "\nEnter name of student " << (s + 1) << ": ";
        cin >> students[s].name;

        students[s].total = 0;
        cout << "Enter 6 coursework marks for " << students[s].name << " (0 - 100):\n";
        for (int m = 0; m < NUM_MARKS; m++) {
            cout << "Mark " << (m + 1) << ": ";
            cin >> students[s].marks[m];
            students[s].total += students[s].marks[m];
        }

        students[s].average = students[s].total / NUM_MARKS;
        students[s].status = (students[s].average >= 50) ? "Allowed" : "Not Allowed";

        resultsFile << students[s].id << "\t"
                    << students[s].name << "\t"
                    << "Total: " << students[s].total << "\t"
                    << "Average: " << students[s].average << "\t"
                    << "Status: " << students[s].status << endl;

        tagsFile << "======================" << endl;
        tagsFile << " Student ID: " << students[s].id << endl;
        tagsFile << " Name: " << students[s].name << endl;
        tagsFile << " Status: " << students[s].status << endl;
        tagsFile << "======================" << endl << endl;

        emailsFile << "To: student_email@example.com" << endl;
        emailsFile << "Subject: Exam Eligibility Notification" << endl;
        emailsFile << "Dear " << students[s].name << " (" << students[s].id << ")," << endl;
        if (students[s].status == "Allowed") {
            emailsFile << "Congratulations! You are eligible to sit for the exams. "
                       << "Your coursework average is " << students[s].average << "%." << endl;
        } else {
            emailsFile << "Unfortunately, you are not eligible to sit for the exams because "
                       << "your coursework average is " << students[s].average << "% (below 50%)." << endl;
        }
        emailsFile << "Best wishes," << endl;
        emailsFile << "Examination Department" << endl;
        emailsFile << "--------------------------------------------" << endl;
    }

    cout << "\n\n=== SUMMARY RESULTS TABLE ===\n";
    cout << left << setw(8) << "ID"
         << setw(15) << "Student"
         << setw(10) << "Total"
         << setw(10) << "Average"
         << setw(15) << "Exam Status" << endl;
    cout << "------------------------------------------------------\n";

    for (int s = 0; s < NUM_STUDENTS; s++) {
        cout << left << setw(8) << students[s].id
             << setw(15) << students[s].name
             << setw(10) << students[s].total
             << setw(10) << students[s].average
             << setw(15) << students[s].status << endl;
    }

    

    ofstream seatingFile("SeatingArrangement.txt");
    seatingFile << "=== Seating Arrangement (Alphabetical Order - Passed Students) ===\n";
    int seat = 1;
    for (int s = 0; s < NUM_STUDENTS; s++) {
        if (students[s].status == "Allowed") {
            seatingFile << "Seat " << seat++ << " -> "
                        << students[s].name << " (" << students[s].id << ")\n";
        }
    }

    cout << "\nResults saved in:\n"
         << " - StudentResults.txt\n"
         << " - Emails.txt\n"
         << " - NameTags.txt\n"
         << " - SeatingArrangement.txt\n";

    resultsFile.close();
    emailsFile.close();
    tagsFile.close();
    seatingFile.close();
    return 0;
}
