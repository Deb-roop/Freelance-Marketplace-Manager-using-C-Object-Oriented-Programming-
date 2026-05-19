#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Base class for all users
class User {
protected:
    string id;
    string name;
    string email;
    string role;

public:
    User(string id, string name, string email, string role)
        : id(id), name(name), email(email), role(role) {}

    // virtual function for overriding later
    virtual void displayInfo() {
        cout << "ID: " << id << " | Name: " << name << " | Role: " << role << endl;
    }

    // Getters to access private/protected data
    string getID() const { return id; }
    string getRole() const { return role; }
    string getName() const { return name; }

    virtual ~User() {}
};

// Freelancer class inheriting from User
class Freelancer : public User {
private:
    double hourlyRate;
public:
    Freelancer(string id, string name, string email, double rate)
        : User(id, name, email, "Freelancer"), hourlyRate(rate) {}

    // Overriding display function for freelancer details
    void displayInfo() override {
        cout << "[Freelancer] ";
        User::displayInfo();
        cout << "Rate: $" << hourlyRate << "/hr" << endl;
    }
};

// Client class inheriting from User
class Client : public User {
public:
    Client(string id, string name, string email)
        : User(id, name, email, "Client") {}

    void displayInfo() override {
        cout << "[Client] ";
        User::displayInfo();
    }
};

// Base class for project features
class BaseProject {
protected:
    string projectID;
    string title;
    bool isCompleted;

public:
    BaseProject(string pid, string t)
        : projectID(pid), title(t), isCompleted(false) {}

    virtual void displayProjectDetails() {
        cout << "Project ID: " << projectID << " | Title: " << title
             << " | Status: " << (isCompleted ? "Completed" : "Active") << endl;
    }

    string getProjectID() const { return projectID; }
    string getTitle() const { return title; }
    bool getStatus() const { return isCompleted; }
    virtual ~BaseProject() {}
};

// Main project class using inheritance
class ClientProject : public BaseProject {
private:
    string assignedFreelancerID;
    string ownerClientID;

public:
    ClientProject(string pid, string t, string cid)
        : BaseProject(pid, t), ownerClientID(cid), assignedFreelancerID("None") {}

    void assignFreelancer(string fid) {
        assignedFreelancerID = fid;
    }

    string getFreelancerID() const { return assignedFreelancerID; }
    string getClientID() const { return ownerClientID; }

    void displayProjectDetails() override {
        BaseProject::displayProjectDetails();
        cout << "--> Created By Client ID: " << ownerClientID
             << " | Assigned Freelancer: " << assignedFreelancerID << endl;
    }
};

// Function to save project details to file
void saveProjects(const vector<ClientProject>& projects) {
    ofstream outFile("projects.txt");
    if (!outFile) {
        cerr << "Error opening file!\n";
        return;
    }
    for (const auto& p : projects) {
        outFile << p.getProjectID() << "," << p.getTitle() << "," << p.getClientID() << ","
                << p.getFreelancerID() << "," << p.getStatus() << endl;
    }
    outFile.close();
    cout << "Data saved to text file successfully.\n";
}

// Function to link a freelancer to an available project
void applyToProject(vector<ClientProject>& projects, string pid, string fid) {
    for (auto& p : projects) {
        if (p.getProjectID() == pid && p.getFreelancerID() == "None") {
            p.assignFreelancer(fid);
            cout << "Successfully applied for project: " << p.getTitle() << endl;
            return;
        }
    }
    cout << "Project not found or already taken.\n";
}

// Displaying all active projects
void showMarketplace(vector<ClientProject>& projects) {
    cout << "\n--- Available Projects ---\n";
    for (auto& p : projects) {
        if (!p.getStatus()) {
            p.displayProjectDetails();
        }
    }
}

int main() {
    // Creating test users using base class pointers
    vector<User*> users;
    users.push_back(new Client("C1", "Debroop", "debroop34@kuet.ac.bd"));
    users.push_back(new Freelancer("F1", "Student_Dev", "aifahad@student.com", 25.0));

    // Hardcoded initial data
    vector<ClientProject> projects;
    projects.push_back(ClientProject("P101", "Web Prototype", "C1"));
    projects.push_back(ClientProject("P102", "Circuit Design", "C1"));

    string inputEmail;
    cout << "=== FREELANCE PROJECT MANAGEMENT SYSTEM ===\n";
    cout << "Enter Email to Login: ";
    cin >> inputEmail;

    User* currentUser = nullptr;
    for (auto u : users) {
        if (inputEmail == "aifahad@student.com" && u->getRole() == "Freelancer") currentUser = u;
        if (inputEmail == "debroop34@kuet.ac.bd" && u->getRole() == "Client") currentUser = u;
    }

    if (!currentUser) {
        cout << "Invalid login credentials!\n";
        for (auto u : users) delete u;
        return 0;
    }

    cout << "\nLogin Successful! ";
    currentUser->displayInfo();

    int choice;
    do {
        cout << "\n1. View Marketplace\n";
        if (currentUser->getRole() == "Freelancer") {
            cout << "2. Apply for Project\n";
        } else {
            cout << "2. Post New Project\n";
        }
        cout << "0. Save and Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            showMarketplace(projects);
        } else if (choice == 2) {
            if (currentUser->getRole() == "Freelancer") {
                string pid;
                cout << "Enter Project ID to apply: ";
                cin >> pid;
                applyToProject(projects, pid, currentUser->getID());
            } else {
                string pid, title;
                cout << "Enter Project ID: "; cin >> pid;
                cout << "Enter Title: "; cin.ignore(); getline(cin, title);
                projects.push_back(ClientProject(pid, title, currentUser->getID()));
            }
        }
    } while (choice != 0);

    // Saving modifications before exiting
    saveProjects(projects);

    // Deallocating dynamic memory to avoid leaks
    for (auto u : users) delete u;
    users.clear();

    return 0;
}
