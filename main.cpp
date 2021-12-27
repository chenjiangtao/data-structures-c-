#include <iostream>
#include<math.h>
#include <map>
#include <set>

using namespace std;

bool IsPrime(int n) {
    int i;
    if (n < 2)
        return false;
    for (i = 2; i <= sqrt(n); i++)//i=n-1
        if (n % i == 0)
            return false;
    return true;
}

map<int, int> GoldbachGuess(int c) {
    int even, a;
    //a+b=c
    //b=c-a
    map<int, int> result;
    // for(even=6;even<max_num;even+=2)
    for (int a = 3; a <= c / 2; a = a + 2)
        if (IsPrime(a) && IsPrime(c - a))
            result.insert(pair<int, int>(a, c - a));
    return result;
}

void Triangle() {
    int borderA, borderB, borderC;
    cout << "请输入A边的长度:";
    cin >> borderA;
    cout << "请输入B边的长度:";
    cin >> borderB;
    cout << "请输入C边的长度:";
    cin >> borderC;
    if (borderA <= 0 || borderB <= 0 || borderC <= 0) {
        cout << "不能构成三角形";
        return;
    }
    if (borderA + borderB > borderC &&
        borderA + borderC > borderB &&
        borderB + borderC > borderA
            )
        cout << "可以构成三角形";
    else
        cout << "不能构成三角形";

}

int Sum(int n) {
    int total = 0;//  1
    int i;
    if (n <= 0)     //1
        return n;
    for (i = 1; i <= n; i++)
        total = total + i;//频度n
    return total;   //   1
}


int Sum1(int n) {
    int i, j, r = 0;//  1
    for (i = 0; i < n; i++) //n+1
        for (j = 0; j <= n; j++)
            r++;//频度n
    return r;   //   1
}

void Big9Guess(int max_num) {
    set<string> myset;
    for (int i = max_num - 1; i >= 6; i = i - 2) {
        map<int, int> r = GoldbachGuess(i);
        map<int, int>::iterator iter;
        iter = r.begin();
        while (iter != r.end()) {
            int number1 = iter->first;
            int number2 = iter->second;
            int number3 = max_num - i;
            int temp;
            /*
            cout<<max_num<<"="<<number1<<"+"
                <<number2<<"+"<<max_num-i<<endl;
                */
            if (number1 > number2) {
                temp = number1;
                number1 = number2;
                number2 = temp;
            }
            if (number1 > number3) {
                temp = number1;
                number1 = number3;
                number3 = temp;
            }
            if (number2 > number3) {
                temp = number2;
                number2 = number3;
                number3 = temp;
            }
            string s1 = to_string(number1);
            string s2 = to_string(number2);
            string s3 = to_string(number3);
            s1.append("+");
            s1.append(s2);
            s1.append("+");
            s1.append(s3);
            //cout<<"s1="<<s1<<endl;
            if (myset.find(s1) == myset.end())
                myset.insert(s1);
            iter++;
        }


    }
    set<string>::iterator sit = myset.begin();
    cout << "myset.size()=" << myset.size() << endl;
    while (sit != myset.end()) {
        cout << max_num << "=" << *sit << endl;
        sit++;
    }
}

int Ferrers(int num) {
    int count = 0;
    int i, j, k;
    int sum = 0;
    for (i = 1; i <= num / 2; i++) {
        sum = 0;
        for (j = i; j <= num / 2 + 1; j++) {
            sum = sum + j;
            if (sum >= num)
                break;
        }
        if (sum == num) {
            count++;
            cout << num << "=";
            for (k = i; k < j; k++)
                cout << k << "+";
            cout << j << endl;
        }

    }
    return count;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    /* int data[10]={2,3,4,5,6,7,8,9,10,11};

     for(i=0;i<10;i++)
         cout<<data[i]<<IsPrime(data[i])<<endl;

    map<int,int> result=GoldbachGuess(60);
    int i;

    map<int, int>::iterator iter;
    iter = result.begin();
    while(iter != result.end())
    {
        cout<<iter->first<<"+"<<iter->second<<endl;
        iter++;
    }*/
//    Ferrers(20);
    cout << Sum1(10);
}