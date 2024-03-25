#include <iostream>
#include <string>
using namespace std;

// Function to check if substring 'sub' is present in string 'str'
bool isSubstring(const string& sub, const string& str) {
    size_t found = str.find(sub);
    return (found != string::npos);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        int cnt = 0;
        size_t found1 = s.find("map");
        size_t found2 = s.find("pie");
        
        while (found1 != string::npos || found2 != string::npos) {
            if (found1 != string::npos) {
                s.erase(found1+1, 1); // Remove the "map" substring
                cnt++;
                found1 = s.find("map");
            }
            if (found2 != string::npos) {
                s.erase(found2+1, 1); // Remove the "pie" substring
                cnt++;
                found2 = s.find("pie");
            }
        }
        
        cout << cnt << endl;
    }
    return 0;
}
