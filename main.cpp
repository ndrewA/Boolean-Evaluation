#include <iostream>
#include <string>

// the par function recursively calls itself such that it can
// "create" every possible parenthesisation around every operation.
// Next, it counts the number of boolean values that were calculated

// returns count of true possibile booleans,
// respectively count of false possibile booleans,
// in all iterations of paranthesisation of
// str expression from [first, last)

std::pair<int, int> par(const std::string& str, const size_t first, const size_t last) {

    // substrLen is the length of the current parenthesis

    const size_t substrLen = last-first;

    // base condition

    if(substrLen == 1){
        if(str[first] == '1') return {1, 0};
        else return {0, 1};
    }

    std::pair<int, int> total = {0, 0};

    // function par iterates through all possible parenthesis lengths
    // from index first, then recursively calls itself
    // for the rest of said expression str

    for(size_t len = 1; len <= substrLen-2; len+=2) {

        // pairs left and right represent the left parenthesis,
        // respectively right parenthesis of expressions,
        // compared to the token of operation

        std::pair<int, int> left = par(str, first, first+len);
        std::pair<int, int> right = par(str, first+len+1, last);

        switch(str[first+len]) {

            case '|':

                total.first += left.first*right.second + left.second*right.first + left.first*right.first;
                total.second += left.second*right.second;
                break;

            case '&':

                total.first += left.first * right.first;
                total.second += left.first*right.second + left.second*right.first + left.second*right.second;
                break;

            case '^':

                total.first += left.first*right.second + left.second*right.first;
                total.second +=  left.first*right.first + left.second*right.second;
                break;
        }
    }
    return total;
}

// the countEval function returns count
// of target bool, after parenthesizing
// through the par function

int countEval(const std::string& str, const bool& target) {

    // checks if string is valid
    // (it must be of uneven size)

    if(str.size() % 2 == 0) return 0;

    std::pair<int, int> res = par(str, 0, str.size());

    // first number of pair res is the true number count
    // second number of pair res is the false number count

    if(target) return res.first;
    else return res.second;
}

int main() {

    const std::string str = "1^0|0|1";
    int res = countEval(str, false);

    std::cout << "res = " << res << '\n';

    return 0;
}

// TIME COMPLEXITY: O(3^n);
// SPACE COMPLEXITY : o(n);
// where n is the length of std::string str

// PROBLEM:

// Boolean Evaluation: Given a boolean expression consisting of the symbols e (false), 1 (true), &
// (AND), | (OR), and ^ (XOR), and a desired boolean result value result, implement a function to
// count the number of ways of parenthesizing the expression such that it evaluates to result.

// EXAMPLE:

// countEval("1^0|0|1", false) -> 2
// countEval("0&0&0&1^1|0", true) -> 10
