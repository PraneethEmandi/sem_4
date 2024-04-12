class Solution {
public:
    string makeGood(string s) {
        for(int i=0;i<s.size()-1;i++){
            
                if(s[i+1]==s[i]-32 || s[i+1]==s[i]+32){
                    s.erase(i,2);
                    i=-1;
                }
            
        }
        return s;
    }
};