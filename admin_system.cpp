#include <bits/stdc++.h>
#include "common.h"
using namespace std;


const string admin_username = "admin";
const string admin_password = "admin123";

class AdminApprovalModule {
private:
    queue<User> pendingQueue;   
    vector<User> allUsers;         
   
    void ldUs() {
        allUsers.clear(); 
        ifstream file(USERS_FILE); 
        if (!file.is_open()) {
            cout << "Warning: Users file not found. Creating new file.\n";
            ofstream newFile(USERS_FILE);  
            newFile.close(); 
            return;
        }
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line); 
            string token;    
                       vector<string> tokens;  
            
            while (getline(ss, token, '|')) {
                tokens.push_back(trim(token));
            }
            
            if (tokens.size() >= 12) {
                try {
                    User user;
                    user.id = stoi(tokens[0]);
                    user.name = tokens[1];
                    user.email = tokens[2];
                    user.phone = tokens[3];
                    user.password = tokens[4];
                    user.age = stoi(tokens[5]);
                    user.cleanliness = stoi(tokens[6]);
                    user.sleepSchedule = stoi(tokens[7]);
                    user.studyHabits = stoi(tokens[8]);
                    user.socialLevel = stoi(tokens[9]);
                    user.description = tokens[10];
                    user.status = tokens[11];
                    
                    allUsers.push_back(user);
                } catch (...) {
                    continue;
                }
            }
        }
        
        file.close();
    }
    
    void bPQ() {
        while (!pendingQueue.empty()) {
            pendingQueue.pop();
        }
        
        for (const User& user : allUsers) {
            if (user.status == "PENDING") {
                pendingQueue.push(user);
            }
        }
    }
    
    bool uUS(int userId, const string& newStatus) {
        bool updated = false;
        for (User& user : allUsers) {
            if (user.id == userId) {
                user.status = newStatus;
                updated = true;
                break;
            }
        }
        
        if (!updated) return false;
        
        ofstream file(USERS_FILE);
        if (!file.is_open()) {
            cout << "Error: Cannot update users file!\n";
            return false;
        }
        
        for (const User& user : allUsers) {
            file << user.id << "|"
                 << user.name << "|"
                 << user.email << "|"
                 << user.phone << "|"
                 << user.password << "|"
                 << user.age << "|"
                 << user.cleanliness << "|"
                 << user.sleepSchedule << "|"
                 << user.studyHabits << "|"
                 << user.socialLevel << "|"
                 << user.description << "|"
                 << user.status << endl;
        }
        
        file.flush();
        
        file.close();
        return true;
    }
    
    void dA(const User& user) {
        cout << "\n================================================================================\n";
        cout << "                      APPLICATION #" << user.id << "\n";
        cout << "================================================================================\n";
        cout << "Name        : " << user.name << "\n";
        cout << "Email       : " << user.email << "\n";
        cout << "Phone       : " << user.phone << "\n";
        cout << "Age         : " << user.age << "\n";
        cout << "\n--- Preference Scores ---\n";
        cout << "Cleanliness    : " << user.cleanliness << "/10\n";
        cout << "Sleep Schedule : " << user.sleepSchedule << "/10\n";
        cout << "Study Habits   : " << user.studyHabits << "/10\n";
        cout << "Social Level   : " << user.socialLevel << "/10\n";
        cout << "\n--- Description ---\n";
        cout << user.description << "\n";
        cout << "================================================================================\n";
    }
    
public:
    bool lg() {
        cout << "\n================================================================================\n";
        cout << "                  ROOMMATE FINDER - ADMIN LOGIN\n";
        cout << "================================================================================\n\n";
        
        string username, password;
        
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);
        
        if (username == admin_username && password == admin_password) {
            cout << "\nAdmin lg successful!\n";
            cout << "Welcome, Administrator!\n";
            pause();
            return true;
        } else {
            cout << "\nInvalid admin credentials!\n";
            pause();
            return false;
        }
    }
    
    void rA() {
        ldUs();
        bPQ();
        
        if (pendingQueue.empty()) {
            cout << "\nNo pending applications .\n";
            pause();
            return;
        }
        
        cout << "\n" << pendingQueue.size() << " application(s) are Pending \n";
        pause();
        
        int processed = 0;
        
        while (!pendingQueue.empty()) {
            User currentUser = pendingQueue.front();
            pendingQueue.pop();
            
            dA(currentUser);
            
            cout << "\n[A] Approve  |  [R] Reject  |  [S] Skip  |  [Q] Quit Review\n";
            cout << "\nYour decision: ";
            
            string input;
            getline(cin, input);
            char choice = input.empty() ? 'S' : toupper(input[0]);
            
            if (choice == 'A') {
                if (uUS(currentUser.id, "APPROVED")) {
                    cout << "\nApplication #" << currentUser.id << " APPROVED!\n";
                    cout << "User " << currentUser.name << " can now lg.\n";
                    processed++;
                } else {
                    cout << "\nError updating status!\n";
                }
                pause();
                
            } else if (choice == 'R') {
                if (uUS(currentUser.id, "REJECTED")) {
                    cout << "\nApplication #" << currentUser.id << " REJECTED!\n";
                    processed++;
                } else {
                    cout << "\nError updating status!\n";
                }
                pause();
                
            } else if (choice == 'S') {
                cout << "\nApplication skipped. Moving to next.\n";
                pause();
                continue;
                
            } else if (choice == 'Q') {
                cout << "\nExiting review mode.\n";
                break;
            } else {
                cout << "\nInvalid choice!\n";
                pause();
            }
        }
        
        cout << "\nReview session complete!\n";
        cout << "Processed: " << processed << " application(s)\n";
        pause();
    }
    
    void vUBS() {
        ldUs();
        
        cout << "\n================================================================================\n";
        cout << "                        ALL USERS BY STATUS\n";
        cout << "================================================================================\n\n";
        
        int pending = 0, approved = 0, rejected = 0;
        
        cout << "--- PENDING APPLICATIONS ---\n";
        for (const User& user : allUsers) {
            if (user.status == "PENDING") {
                cout << "ID:" << user.id << " | " << left << setw(25) << user.name
                     << " | " << user.email << "\n";
                pending++;
            }
        }
        if (pending == 0) cout << "None\n";
        
        cout << "\n--- APPROVED USERS ---\n";
        for (const User& user : allUsers) {
            if (user.status == "APPROVED") {
                cout << "ID:" << user.id << " | " << left << setw(25) << user.name 
                     << " | " << user.email << "\n";
                approved++;
            }
        }
        if (approved == 0) cout << "None\n";
        
        cout << "\n--- REJECTED APPLICATIONS ---\n";
        for (const User& user : allUsers) {
            if (user.status == "REJECTED") {
                cout << "ID:" << user.id << " | " << left << setw(25) << user.name 
                     << " | " << user.email << "\n";
                rejected++;
            }
        }
        if (rejected == 0) cout << "None\n";
        
        cout << "\n================================================================================\n";
        cout << "Total: " << allUsers.size() 
             << " (Pending: " << pending 
             << ", Approved: " << approved 
             << ", Rejected: " << rejected << ")\n";
        cout << "================================================================================\n";
        
        pause();
    }
    
    void dS() {
        ldUs();
        
        int pending = 0, approved = 0, rejected = 0;
        double avgAge = 0;
        
        for (const User& user : allUsers) {
            if (user.status == "PENDING") pending++;
            else if (user.status == "APPROVED") approved++;
            else if (user.status == "REJECTED") rejected++;
            
            avgAge += user.age;
        }
        
        if (!allUsers.empty()) {
            avgAge /= allUsers.size();
        }
        
        cout << "\n================================================================================\n";
        cout << "                      SYSTEM STATISTICS\n";
        cout << "================================================================================\n\n";
        cout << "Total Registrations : " << allUsers.size() << "\n";
        cout << "Pending Queue Size  : " << pending << " \n";
        cout << "Approved Users      : " << approved << "\n";
        cout << "Rejected Apps       : " << rejected << "\n";
        cout << "\nAverage Age         : " << fixed << setprecision(1) << avgAge << " years\n";
        cout << "================================================================================\n";
        
        pause();
    }
};

class MatchManagementModule {
private:
    vector<User> allUsers;
    vector<MatchRequest> matchRequests;
    vector<ConfirmedMatch> confirmedMatches;
    map<int, vector<pair<int, double>>> compatibilityGraph;
    
    void ldUs() {
        allUsers.clear();
        ifstream file(USERS_FILE);
        if (!file.is_open()) return;
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string token;
            vector<string> tokens;
            
            while (getline(ss, token, '|')) {
                tokens.push_back(trim(token));
            }
            
            if (tokens.size() >= 12) {
                try {
                    User user;
                    user.id = stoi(tokens[0]);
                    user.name = tokens[1];
                    user.email = tokens[2];
                    user.phone = tokens[3];
                    user.password = tokens[4];
                    user.age = stoi(tokens[5]);
                    user.cleanliness = stoi(tokens[6]);
                    user.sleepSchedule = stoi(tokens[7]);
                    user.studyHabits = stoi(tokens[8]);
                    user.socialLevel = stoi(tokens[9]);
                    user.description = tokens[10];
                    user.status = tokens[11];
                    
                    if (user.status == "APPROVED") {
                        allUsers.push_back(user);
                    }
                } catch (...) {
                    continue;
                }
            }
        }
        
        file.close();
    }
    
    void ldMR() {
        matchRequests.clear();
        ifstream file(MATCH_REQUESTS_FILE);
        if (!file.is_open()) return;
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string token;
            vector<string> tokens;
            
            while (getline(ss, token, '|')) {
                tokens.push_back(trim(token));
            }
            
            if (tokens.size() >= 5) {
                try {
                    MatchRequest req;
                    req.senderId = stoi(tokens[0]);
                    req.receiverId = stoi(tokens[1]);
                    req.status = tokens[2];
                    req.senderName = tokens[3];
                    req.receiverName = tokens[4];
                    
                    matchRequests.push_back(req);
                } catch (...) {
                    continue;
                }
            }
        }
        
        file.close();
    }
    
    void ldCM() {
        confirmedMatches.clear();
        ifstream file(MATCHES_FILE);
        if (!file.is_open()) return;
        
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string token;
            vector<string> tokens;
            
            while (getline(ss, token, '|')) {
                tokens.push_back(trim(token));
            }
            
            if (tokens.size() >= 3) {
                try {
                    ConfirmedMatch match;
                    match.user1Id = stoi(tokens[0]);
                    match.user2Id = stoi(tokens[1]);
                    match.matchDate = tokens[2];
                    
                    confirmedMatches.push_back(match);
                } catch (...) {
                    continue;
                }
            }
        }
        
        file.close();
    }
   
    double cC(const User& u1, const User& u2) {
        double score = 0;
        
        score += (10 - abs(u1.cleanliness - u2.cleanliness)) * 2.5;
        score += (10 - abs(u1.sleepSchedule - u2.sleepSchedule)) * 2.0;
        score += (10 - abs(u1.studyHabits - u2.studyHabits)) * 2.0;
        score += (10 - abs(u1.socialLevel - u2.socialLevel)) * 3.5;
        
        return score;
    }
    
    void bCG() {
        compatibilityGraph.clear();
        
        for (int i = 0; i < allUsers.size(); i++) {
            for (int j = i + 1; j < allUsers.size(); j++) {
                double score = cC(allUsers[i], allUsers[j]);
                
                compatibilityGraph[allUsers[i].id].push_back({allUsers[j].id, score});
                compatibilityGraph[allUsers[j].id].push_back({allUsers[i].id, score});
            }
        }
    }
    
    User* gU(int id) {
        for (User& user : allUsers) {
            if (user.id == id) return &user;
        }
        return nullptr;
    }

    static bool compareScores(const pair<int, double>& a, const pair<int, double>& b) {
        return a.second > b.second;
    }

public:
    void dCG() {
        ldUs();
        bCG();
        
        if (allUsers.empty()) {
            cout << "\nNo approved users to build graph.\n";
            pause();
            return;
        }
        
        cout << "\n================================================================================\n";
        cout << "                              COMPATIBILITY GRAPH \n";
        cout << "================================================================================\n\n";
        cout << "Graph: " << allUsers.size() << " nodes,"
             << "Each edge = compatibility score\n\n";
        
        for (const User& user : allUsers) {
            cout << "User " << user.id << " (" << user.name << ") -> ";
            
            if (compatibilityGraph.find(user.id) != compatibilityGraph.end()) {
                const auto& connections = compatibilityGraph[user.id];
                
                vector<pair<int, double>> topConnections = connections;

                sort(topConnections.begin(), topConnections.end(), compareScores);
                
                int shown = 0;
                for (const auto& conn : topConnections) {
                    if (shown >= 3) break;
                    
                    User* connectedUser = gU(conn.first);
                    if (connectedUser) {
                        cout << "[" << conn.first << ":" << connectedUser->name 
                             << " (" << fixed << setprecision(1) << conn.second << "%)] "; 
                        shown++;
                    }
                }
            }
            cout << "\n";
        }
        
        pause();
    }
    
    void vMR() {
        ldUs();
        ldMR();
        
        if (matchRequests.empty()) {
            cout << "\nNo match requests found.\n";
            pause();
            return;
        }
        
        cout << "\n================================================================================\n";
        cout << "                      ALL MATCH REQUESTS\n";
        cout << "================================================================================\n\n";
        
        map<string, int> statusCount;
        
        for (const auto& req : matchRequests) {
            cout << req.senderName << " (ID:" << req.senderId << ")"
                 << " -> " << req.receiverName << " (ID:" << req.receiverId << ")"
                 << " [" << req.status << "]\n";
            
            statusCount[req.status]++;
        }
        
        cout << "\n================================================================================\n";
        cout << "Total Requests: " << matchRequests.size() << "\n";
        cout << "Pending: " << statusCount["PENDING"] 
             << " | Accepted: " << statusCount["ACCEPTED"]
             << " | Rejected: " << statusCount["REJECTED"] << "\n";
        cout << "================================================================================\n";
        
        pause();
    }
    
    void vCM() {
        ldUs();
        ldCM();
        
        if (confirmedMatches.empty()) {
            cout << "\nNo confirmed roommate matches yet.\n";
            pause();
            return;
        }
        
        cout << "\n================================================================================\n";
        cout << "                    CONFIRMED ROOMMATE MATCHES\n";
        cout << "================================================================================\n\n";
        
        for (const auto& match : confirmedMatches) {
            User* user1 = gU(match.user1Id);
            User* user2 = gU(match.user2Id);
            
            if (user1 && user2) {
                cout << user1->name << " (ID:" << match.user1Id << ")"
                     << " <-> " << user2->name << " (ID:" << match.user2Id << ")"
                     << " | Date: " << match.matchDate << "\n";
            }
        }
        
        cout << "\n================================================================================\n";
        cout << "Total Confirmed Matches: " << confirmedMatches.size() << "\n";
        cout << "================================================================================\n";
        
        pause();
    }
    
    void dMS() {
        ldUs();
        ldMR();
        ldCM();
        bCG();
        
        cout << "\n================================================================================\n";
        cout << "                    MATCHING SYSTEM STATISTICS\n";
        cout << "================================================================================\n\n";
        
        cout << "--- Graph Statistics ---\n";
        cout << "Total Nodes (Users): " << allUsers.size() << "\n";
        
        int totalEdges = 0;
        double avgCompatibility = 0;
        int edgeCount = 0;
        
        for (const auto& pair : compatibilityGraph) {
            totalEdges += pair.second.size();
            for (const auto& edge : pair.second) {
                avgCompatibility += edge.second;
                edgeCount++;
            }
        }
        
        totalEdges /= 2;
        if (edgeCount > 0) avgCompatibility /= edgeCount;
        
        cout << "Total Edges: " << totalEdges << "\n";
        cout << "Average Compatibility: " << fixed << setprecision(1) 
             << avgCompatibility << "%\n";
        
        cout << "\n--- Match Request Statistics ---\n";
        cout << "Total Requests: " << matchRequests.size() << "\n";
        
        int pending = 0, accepted = 0, rejected = 0;
        for (const auto& req : matchRequests) {
            if (req.status == "PENDING") pending++;
            else if (req.status == "ACCEPTED") accepted++;
            else if (req.status == "REJECTED") rejected++;
        }
        
        cout << "Pending: " << pending << "\n";
        cout << "Accepted: " << accepted << "\n";
        cout << "Rejected: " << rejected << "\n";
        
        cout << "\n--- Confirmed Matches ---\n";
        cout << "Total Roommate Pairs: " << confirmedMatches.size() << "\n";
        
        cout << "\n================================================================================\n";
        pause();
    }
};

int main() {
    AdminApprovalModule adminApproval;
    MatchManagementModule matchManagement;
    
    if (!adminApproval.lg()) {
        return 0;
    }
    
    while (true) {
        cout << "\n================================================================================\n";
        cout << "                 ROOMMATE FINDER - ADMIN PORTAL\n";
        cout << "================================================================================\n\n";
        cout << "1. Review Pending Applications \n";
        cout << "2. View All Users by Status\n";
        cout << "3. Display System Statistics\n";
        cout << "4. View Compatibility Graph\n";
        cout << "5. View All Match Requests\n";
        cout << "6. View Confirmed Matches\n";
        cout << "7. Match Statistics\n";
        cout << "8. Logout\n";
        cout << "\nChoice: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        
        if (!isValidInt(choiceStr)) {
            cout << "\nInvalid input!\n";
            pause();
            continue;
        }
        
        int choice = stoi(choiceStr);
        
        switch(choice) {
            case 1:
                adminApproval.rA();
                break;
            case 2:
                adminApproval.vUBS();
                break;
            case 3:
                adminApproval.dS();
                break;
            case 4:
                matchManagement.dCG();
                break;
            case 5:
                matchManagement.vMR();
                break;
            case 6:
                matchManagement.vCM();
                break;
            case 7:
                matchManagement.dMS();
                break;
            case 8:
                cout << "\nAdmin logged out!\n";
                return 0;
            default:
                cout << "\nInvalid choice!\n";
                pause();
        }
    }
    
    return 0;
}