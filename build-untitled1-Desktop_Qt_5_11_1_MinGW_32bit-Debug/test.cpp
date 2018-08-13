#include <bits/stdc++.h>
using namespace std;
#define dbg(x) cout<<#x<<" = " << (x) << std::endl
#define dbg1(x, y)cout<<#x<<" = "<<x<<" | "<<#y<<" = "<<y<<endl
#define dbg2(x, y, z)cout<<#x<<" = " <<x<<" | "<<#y<<" = "<<y<<" | "<<#z<<" = "<<z<<endl
#define pb push_back
#define fi first
#define se second
typedef long long int ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> iv;	
int n;
static int c=0;
int arr[5]={1,2,3,4,5};

int rec(int n,int l,int r,int curr,int parent){
 int x=curr;
cout<<curr << " " << parent<<endl;
	if(n<1){
		int y=  0;cout<<x<<"$"<<y<<endl; 
		return y;
	}
	if(n==1){
		int y=  1;cout<<x<<"$"<<y<<endl; 
		return y;
	}
    int z=1+rec(n-1,l,r,++c,x);
    // if(n==3) cout<<curr<<endl;
    int z1=rec(n-2,l,r,++c,x);
    int z3=rec(n-3,l,r,++c,x);
   int y=  z+z1+z3;
   cout<<x<<"$"<<y<<endl; 
return y;

}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	// freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	rec(3,0,5,0,0);
	//rec(0,5,1);       
	return 0;
}
