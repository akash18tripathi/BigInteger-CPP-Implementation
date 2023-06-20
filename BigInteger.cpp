#include <iostream>
#include <string.h>

using namespace std;



//====================== ** HELPER FUNCTIONS ** ========================
int precedence(char c){
    if(c=='+' || c=='-'){
        return 1;
    }
    if(c=='x'){
        return 2;
    }
    return 0;
}
string trim(string a){
    string a1="";
    bool flag=false;
    for(int i=0;i<a.length();i++){
        if(a[i]!='0'){
            flag=true;
        }
        if(flag){
            a1+=a[i];
        }
    }
    if(a1.length()==0){
        a1="0";
    }
    return a1;
}

bool compare(string a,string b){
    //a>b - true else false
    string a1=trim(a),b1=trim(b);
    if(a1.length()==b1.length()){
        return a1>=b1;
    }
    if(a1.length()>b1.length()){
        return true;
    }
    return false;
}


//======================= ** STACK HELPER CLASS ** ==========================
template <typename T>
class stack{

    int top;
    T* arr;
    public:

    stack(){
        this->top=-1;
        this->arr = new T[100000];
    }

    void push(T x){
        arr[++top]=x;
    }
    T up(){
        return arr[top];
    }
    bool empty(){
        if(this->top==-1){
            return true;
        }
        return false;
    }
    void pop(){
        this->top--;
    }

    int size(){
        return this->top+1;
    }

};



//========================== ** BIGINTEGER CLASS ** =======================
class BigInteger{
    string num;

    public:
    string addition(string a,string b){
        if(a.length()<b.length()){
            string temp = a;
            a = b;
            b = temp;
        }
        int l1=a.length();
        int l2=b.length();
        int carry=0;
        string ans="";
        for(int i=0;i<max(l1,l2);i++){
            int n1=l1-i-1>=0?a[l1-i-1]-'0':0;
            int n2=l2-i-1>=0?b[l2-i-1]-'0':0;
            if((n1+n2+carry)>=10){
                ans=to_string((n1+n2+carry)%10)+ans;
                carry=1;
            }else{
                ans=to_string((n1+n2+carry)%10)+ans;
                carry=0;
            }
        }
        if(carry==1){
            ans='1'+ans;
        }
        return ans;
    }


    string subtraction(string a,string b){
        if(a.length()<b.length()){
            string temp=a;
            a=b;
            b=temp;
        }
        int l1=a.length();
        int l2=b.length();
        int borrow=0;
        string ans="";
        for(int i=0;i<max(l1,l2);i++){
            int n1=l1-i-1>=0?a[l1-i-1]-'0':0;
            int n2=l2-i-1>=0?b[l2-i-1]-'0':0;
            if(n1-borrow<n2){
                ans = to_string(n1+10-borrow-n2) + ans;
                borrow=1;
            }else{
                ans = to_string(n1-borrow-n2)+ans;
                borrow=0;
            }
        }

        bool flag=false;
        int k=ans.length();
        string finalAns=trim(ans);

        return finalAns;
    }

    string multiply(string a,string b){
        int l1=a.length();
        int l2=b.length();
        int arr[l1+l2+1];
        for(int i=0;i<l1+l2+1;i++){
            arr[i]=0;
        }
        int k=l1+l2;
        string ans="";
        int carry=0;
        for(int i=l2-1;i>=0;i--){
            int temp=k;
            carry=0;
            int n1 = b[i]-'0';
            for(int j=l1-1;j>=0;j--){
                int n2 = a[j]-'0';
                int num = (arr[temp]+n2*n1+carry);
                carry = (num)/10;
                arr[temp] = (num)%10;            
                temp--;
            }
            arr[temp]=carry;
            k--;
        }
        bool flag=false;
        for(int i=1;i<l1+l2+1;i++){
            if(arr[i]!=0){
                flag=true;
            }
            if(flag){
                ans+= to_string(arr[i]);
            }
        }
        if(ans.length()==0){
            ans="0";
        }
        return ans;
    }
    string util(string a,string b){
        string num=a;
        int i;
        for(i=1;;i++){
            if(compare(b,multiply(num,to_string(i)))){
                continue;
            }else{
                break;
            }
        }
        return to_string(i-1);
    }

        string mod(string a,string b){
        // a/b
        a=trim(a);
        b=trim(b);
        if(a.length()==b.length() && a==b){
            return "0";
        }
        if(compare(b,a)){
            return a;
        }
        
        int n = b.length();
        string num="";
        string ans="";
        string k;
        int i=0;
        while(i<a.length()){
            while(i<a.length() && num.length()!=b.length()){
                num+=a[i];
                i++;
            }
            while(i<a.length() && compare(b,num)){
                num+=a[i];
                i++;
            }  
            if(i==a.length() && compare(b,num)){
                ans=num;
                break;
            }
            k = util(b,num);
            string temp = multiply(b,k);
            temp = subtraction(num,temp);
            num=temp;
            ans+=k; 
        }
        return trim(num);
    }


    string evaluate(string a,string b,char c){
        if(c=='+'){
            return addition(a,b);
        }else if(c=='-'){
            return subtraction(a,b);
        }else{
            return multiply(a,b);
        }
    }

    string infixEvaluation(string input){
        
        stack<string> st1;
        stack<char> st2;
        string num="";
        for(int i=0;i<input.length();i++){
            if(input[i]=='+' || input[i]=='-' || input[i]=='x'){
                st1.push(num);
                num="";
                if(st2.empty()){
                    st2.push(input[i]);
                }else{
                    if(precedence(st2.up())<precedence(input[i])){
                        st2.push(input[i]);
                    }else{
                        while(!st2.empty() && precedence(st2.up())>=precedence(input[i]) ){
                            string a = st1.up();
                            st1.pop();
                            string b = st1.up();
                            st1.pop();
                            string temp = evaluate(b,a,st2.up());
                            st1.push(temp);
                            st2.pop();
                        }
                        st2.push(input[i]);
                    }
                }
            }else{
                num+=input[i];
            }
        }
        if(num.length()>0){
            st1.push(num);
        }
        
        while(st1.size()>1){
            string a = st1.up();
            st1.pop();
            string b = st1.up();
            st1.pop();
            string temp = evaluate(b,a,st2.up());
            st1.push(temp);
            st2.pop();
        }
        return st1.up();
    }

    string exponent(string x,long long int n){
        if(n==0){
            return "1";
        }
        if(n==1){
            return x;
        }
        if(n%2==0){
            string temp = exponent(x,n/2);
            return multiply(temp,temp);
        }
        return multiply(x,exponent(x,n-1));
    }

    string gcd(string a,string b){
        if(b=="0"){
            return a;
        }
        
        return gcd(b,mod(a,b));
    }


    string factorial(int n){
        
        string ans="1";
        for(int i=n;i>=1;i--){
            ans = multiply(ans,to_string(i));
        }
        cout << ans<<endl;
        return ans;
    }

};




//======================== ** DRIVER FUNCTION ** ==============================
int main(){
    int n;
    cin >> n;
    string ans="";
    BigInteger bi;
    switch(n){
        case 1:{
            string s;
            cin >> s;
            ans = bi.infixEvaluation(s);
            break;
        }
        case 2:{
            string base;
            long long int exp;
            cin >> base >> exp;
            ans=bi.exponent(base,exp);
            break;
        }
        case 3:{
            string a,b;
            cin >> a >> b;
            a=trim(a);
            b=trim(b);
            if(compare(b,a)){
                ans=bi.gcd(b,a);
            }else{
                ans=bi.gcd(a,b);
            }
            
            break;
        }
        case 4:{
            int n;
            cin >> n;
            ans= bi.factorial(n);
            break;
        }
    }
    cout << ans<<endl;
    
    return 0;
}