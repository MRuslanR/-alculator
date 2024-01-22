#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class StringProcessor {
private:
    string inputString;

public:
    StringProcessor(const string& input) : inputString(input) {}
    double Culc_tg(double x) {
        return tan(x);
    }
    double Culc_ctg(double x) {
        return 1/Culc_tg(x);
    }
    double Culc_sin(double x) {
        return sin(x);
    }
    double Culc_cos(double x) {
        return cos(x);
    }
    double Culc_ln(double x) {
        return log(x);
    }
    double Culc_lg(double x) {
        return log10(x);
    }
    double Culc_sqrt(double x) {
        return sqrt(x);
    }
    double Culc_log(double x,double y) {
        return Culc_lg(y)/Culc_lg(x);
    }
    double Culc_sqrt(double x,double y) {
        return pow(y,1/x);
    }
    string getString() const {
        return inputString;
    }
};


int main()
{
    string userInput; getline(cin, userInput);
    StringProcessor processor(userInput);
    string str = processor.getString();
    int len = str.length();
    vector <char> ans;
    vector <char> stack;
    string op = "+-/*^";
    string op1 = "*/";
    string op2 = "+-";
    string opp = "!";
    string op3 = "^";
    vector<int>numbers;
    cout << "Expression:" << endl;
    cout << str << endl;
    for (int i = 0; i < len; i++) {
        int stack_len = stack.size() - 1;
        if (str[i] >= 48 && str[i] <= 57) {
            int j = i;
            while (str[i] >= 48 && str[i] <= 57) { ans.push_back(str[i++]); }
            ans.push_back(' '); i--;
        }

        else if (str[i] == '(') stack.push_back(str[i]);
        else if (str[i] == ')') {
            int cnt = 0; 
            while (stack[stack_len] != '(') {
                ans.push_back(stack[stack_len--]);
                ans.push_back(' ');
                cnt++;
                stack.pop_back();
            }
            stack.pop_back();
            int flag = 1;
            for (int j = i; j >= 0; j--) {
                if (str[j] == '(') {
                    if(str[j + 1] == '-')flag = 0;
                    break; 
                }
            }
            if (cnt == 1 && ans[ans.size() - 2] == '-' && flag==0) { ans[ans.size() - 2] = '!'; }

        }

        else if (op.find(str[i]) != string::npos) {
            if (op2.find(str[i]) != string::npos) {
                for (int i = stack_len; i >= 0; i--) { if (stack[i] == '(') {break; } ans.push_back(stack[i]); ans.push_back(' '); stack.pop_back(); }
            }
            else if (op1.find(str[i]) != string::npos){
                while (stack.size()!=0 && op1.find(stack[stack_len]) != string::npos && op3.find(str[i]) != string::npos) {
                    ans.push_back(stack[stack_len]);
                    ans.push_back(' ');
                    stack.pop_back();
                    stack_len--;
                }
            }
            else {
                while (stack.size() != 0 && op3.find(str[i]) != string::npos) {
                    ans.push_back(stack[stack_len]);
                    ans.push_back(' ');
                    stack.pop_back();
                    stack_len--;
                }
            }
            stack.push_back(str[i]);
        }

    }
    while (stack.size() > 0) {
        ans.push_back(stack[stack.size() - 1]);
        ans.push_back(' ');
        stack.pop_back();
    } 
    cout << "Reverse Polish Notation:" << endl;
    for (auto b : ans) cout << b;
    cout << endl;


    int lens = ans.size();
    for (int i = 0; i < lens; i++) {
        if (ans[i] >= 48 && ans[i] <= 57) {
            int j = i;
            while (ans[i] >= 48 && ans[i] <= 57) { i++; }
            i--;
            int cur = 0;
            for (int k = i; k >= j; k--) {
                cur += pow(10, i - k) * (ans[k] - 48);
            }
            numbers.push_back(cur);
        }
        else if (op.find(ans[i]) != string::npos || opp.find(ans[i]) != string::npos){
            if (ans[i] == '+') numbers[numbers.size() - 2] = numbers[numbers.size() - 2] + numbers[numbers.size() - 1];
            else if (ans[i] == '^') numbers[numbers.size() - 2] = pow(numbers[numbers.size() - 2], numbers[numbers.size() - 1]);
            else if (ans[i] == '*') numbers[numbers.size() - 2] = numbers[numbers.size() - 2] * numbers[numbers.size() - 1];
            else if (ans[i] == '/') numbers[numbers.size() - 2] = numbers[numbers.size() - 2] / numbers[numbers.size() - 1];
            else if (ans[i] == '!') { numbers[numbers.size() - 1] = -numbers[numbers.size() - 1]; numbers.push_back(0); }
            else if (ans[i] == '-') { 
                if (numbers.size() == 1) { numbers[0] = -numbers[0]; numbers.push_back(0); }
                else numbers[numbers.size() - 2] = numbers[numbers.size() - 2] - numbers[numbers.size() - 1];
            
            }
            numbers.pop_back();

        }


    }
    cout << "Result:" << endl;
    cout << numbers[0] ;

    return 0;
}





















