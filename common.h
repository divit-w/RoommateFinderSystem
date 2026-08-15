
    #ifndef COMMON_H
    #define COMMON_H

    #include <string>
    #include <iostream>
    using namespace std;

    const string USERS_FILE = "data/users.txt";
    const string MATCH_REQUESTS_FILE = "data/match_requests.txt";
    const string MATCHES_FILE = "data/matches.txt";

    struct User {
        int id;
        string name;
        string email;
        string phone;
        string password;      
        int age;
            int cleanliness;      
                int sleepSchedule;    
        int studyHabits;     
        int socialLevel;      
        string description;   
        string status;        
        
        User() : id(0), age(0), cleanliness(0), sleepSchedule(0), 
                studyHabits(0), socialLevel(0), status("PENDING"), description(""), password("") {}
    };

    struct MatchRequest {
        int senderId;
        int receiverId;
        string status; 
        string senderName;
        string receiverName;
        
        MatchRequest() : senderId(0), receiverId(0), status("PENDING") {}
    };

struct ConfirmedMatch {
    int user1Id;
    int user2Id;
    string matchDate;
    
    ConfirmedMatch() : user1Id(0), user2Id(0) {}
};

string trim(const string& str) {
    if (str.empty()) return str;
    
    int start = 0;
    int end = str.length() - 1;
    
    while (start <= end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) {
        start++;
    }

    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }
    
    if (start <= end) {
        return str.substr(start, end - start + 1);
    }
    
    return "";
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(10000, '\n');
    cin.get();
}

bool isValidInt(const string& str) {
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-') continue;
        if (!isdigit(str[i])) return false;
    }
    return true;
}

#endif 