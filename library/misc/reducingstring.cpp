#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <list>
#include <sstream>
#include <algorithm>

int n, j;

int main(){
	std::string s;
	getline(std::cin, s);
	while(j<s.length()-1){
		if(s.at(j) == s.at(j+1)){
			s.erase(j, j+2);
		}
		else ++j;
	}
	if(s.length()==0) printf("Empty String\n");
	else printf("%s\n", s.c_str());
  return 0;
}
