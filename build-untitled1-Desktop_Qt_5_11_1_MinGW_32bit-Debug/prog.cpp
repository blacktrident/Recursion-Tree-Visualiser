//glory glory man utd <3
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
int c=0;
int arr[5]={1,2,3,4,5};

int rec(int n,int l,int r){
	if(n<1){
		return 0;
	}
	if(n==1){
		return 1;
	}
   return rec(n-1)+rec(n-2);

}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	// freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	rec(5,0,5,0,0);
	//rec(0,5,1);
	return 0;
}
