#include<bits/stdc++.h>
using namespace std;

vector<string> split(string s, string delimiter){
  size_t pos = 0;
  string token;
  vector<string> res;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    res.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  res.push_back(s);
  return res;
}

int main(){
  vector<string> s = split("eggs::bus::meg", "::");
  for(int i = 0; i<s.size(); ++i)
    printf("%s ", s[i].c_str());
  printf("\n");
  return 0;
}