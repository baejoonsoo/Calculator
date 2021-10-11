// C++ 한자릿수 계산기
// 출력문은 int 범위 내 정수이며 피연산자의 자릿수는 한자릿수이다.
// 차후 자릿수 증가 예정

#include <iostream>
#include <stack>
#include <queue>
using namespace std;


void postfix(queue<char> &res1,stack<char> &st,char n){
    if(n>=48&&n<=57) {  // 숫자라면 res1에 저장
        res1.push(n);
    }
    else if(n==41) {    //닫힌 괄호일 경우 열린 괄호 위치 전까지 모두 출력
        while(st.top()!=40) {
            res1.push(st.top());
            st.pop();
        }
        st.pop(); // 괄호 제거
    }
    else if(!st.empty()) {
        if ((st.top()=='/'||st.top()=='*')&&(n=='+'||n=='-')){  // n 보다 st의 top의 연산자 순위가 높을 경우
            res1.push(st.top());
            st.pop();
            st.push(n);
        }
        else {  // 아닐 경우 (열린 괄호 입력 포함)
            st.push(n);
        }
    }
    else {  // st가 비어 있을 경우 비교를 생략하고 push 한다
        st.push(n);
    }
    
}

void oper(stack<int> &st, int n1, int n2, char oper){
    int res;

    // 연산자에 맞게 계산하여 st에 push
    if(oper=='+'){
        res=(n2+n1);
        st.push(res);
    }
    else if(oper=='-'){
        res=(n2-n1);
        st.push(res);
    }
    else if(oper=='/'){
        res=(n2/n1);
        st.push(res);
    }
    else if(oper=='*'){
        res=(n2*n1);
        st.push(res);
    }
}

void sum(queue<char> &res,stack<int> &st) {
    while(!(res.empty())){
        char n = res.front();   // res에 앞에서 부터 하나씩 꺼낸다
        res.pop();

        if(n>=48&&n<=57) {  // 숫자라면
            int num = (static_cast<int>(n) - 48);
            st.push(num);
        }
        else {  // 연산자라면
            int r1=st.top(); // stack에서 값 두 개를 꺼내온다
            st.pop();
            int r2=st.top();
            st.pop();

            oper(st,r1,r2,n); // stack의 주소와 값들, 연산자를 넘겨준다
        }
    }

    cout<<st.top()<<endl;
}


int main() {
    string num;
    stack<char> st;
    stack<int> nSt;
    queue<char> res1;
    cin>>num;

    for(auto &n:num){   // num의 각 원소로 나눠 함수 호출
        postfix(res1,st,n);
    }

    while(!(st.empty())) {  // 수식 정리 이후 남은 연산자 모두 res1에 저장
        res1.push(st.top());
        st.pop();
    }

    sum(res1,nSt);

    return 0;
}