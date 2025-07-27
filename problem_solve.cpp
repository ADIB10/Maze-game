#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

int main()
{
int t;

cin>>t;
while(t>0)
{
t--;

    int n,a[200000]={0},b,ans=0;
    cin>>n;
     for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<n-2;i++)
    {b=a[i];
        a[i]-=b;
        a[i+1]-=2*b;
        a[i+2]-=b;if(a[i]!=0){ans=-1;}

    }if(a[n-2]!=0||a[n-1]!=0){ans=-1;}
    if(ans==-1){cout<<"NO"<<endl;}
    else{cout<<"YES"<<endl;}


}
return 0;
}


