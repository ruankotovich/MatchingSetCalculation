#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <unordered_map>

struct Match_t{
  unsigned int i;
  unsigned int j;
  mutable unsigned int ed;

  Match_t() : i(0), j(0), ed(0){}

  Match_t(unsigned int _i, unsigned int _j, unsigned int _ed) : i(_i), j(_j), ed(_ed){}

};

struct MatchComparator_t{
  bool operator()(const Match_t &m1, const Match_t &m2){
    return m1.i < m2.i || m1.j < m2.j;
  }
};

unsigned int dedFromMatch(const Match_t& match, unsigned int i, unsigned int j){
  return match.ed + std::max(i - match.i, j - match.j);
}

std::set<Match_t, MatchComparator_t> matchingSet(const std::string& q, const std::string s){
  std::cout << "Building set for " << q << " and " << s << '\n';
  std::set<Match_t, MatchComparator_t> matchSet;
  matchSet.emplace(0,0,0);

  // foreach q_i where 1 <= i <= |q|
  for(int i = 1; i < q.size(); i++){

    std::set<Match_t, MatchComparator_t> currentMatchSet;

    // for each m' = {i', k', ed'} € M(q_i-1, s)
    for(auto match : matchSet){

      // for each j > j' s.t. q[i] = s[j]
      for(int j = match.j+1; j < s.size(); j++){

        if(q[i] == s[j]){
          std::cout << "Match on q" << i << " and s" << j << '\n';

          unsigned int newDed = dedFromMatch(match, i-1, j-1);
          auto currentMatchSet_iterator = currentMatchSet.emplace(i, j, newDed);

          if(!currentMatchSet_iterator.second){
            std::cout << "There was a entry on the set : " << currentMatchSet_iterator.first->ed << '\n';
            if(currentMatchSet_iterator.first->ed > newDed){
              std::cout << "Replaced by " << newDed << '\n';
              currentMatchSet_iterator.first->ed = newDed;
            }else{
              std::cout << "Not replaced\n";
            }
          }else{
            std::cout << "Inserted with " << newDed << '\n';
          }

        }
      }
    }

    matchSet.insert(currentMatchSet.begin(), currentMatchSet.end());

  }

  return matchSet;
}


int main(){
  std::string s1, s2;
  std::cin >> s1 >> s2;
  s1 = "#"+s1;
  s2 = "#"+s2;
  
  std::set<Match_t, MatchComparator_t> testSet = matchingSet(s1, s2);

  for(auto item : testSet){
    std::cout << item.i << ' ' << item.j << ' ' << item.ed << '\n';
  }
}
