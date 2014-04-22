#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<set>
#include<limits.h>
#include<queue>
using namespace std;

#define MAXN 100

vector<pair<double,double> > nodes;
vector<set<int> > th_neigh(MAXN);
vector<set<int> > fh_neigh(MAXN);
vector<vector<int> > neigh(MAXN);
vector<int> vw1;
vector<int> vw2;

int gloflag;
int nowhole;
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double compute_pn (double r, double R, double b)
{
	double t1 = (8*(R/b + 0.5)*(R/b + 0.5)*acos(r/(2*R+b)))/M_PI;
	double t2 = (4*r*sqrt((R+b/2)*(R+b/2) - ((r*r)/4)))/(M_PI*b*b);

	return (int)(t1-t2);
}
double distance(double x1, double y1,double x2, double y2)
{
	double dx=x2-x1;
	double dy=y2-y1;
	return sqrt(dx*dx + dy*dy);
}

double dis(int i, int j)
{
	double x1 = nodes[i].first;
	double y1 = nodes[i].second;
	double x2 = nodes[j].first;
	double y2 = nodes[j].second;
	double dx=x2-x1;
	double dy=y2-y1;
	return sqrt(dx*dx + dy*dy);
}
void findneighbours(double r)
{
	int i,j;
	for (i=0;i<MAXN;i++)
		for (j=0;j<MAXN;j++)
			if (i!=j && dis(i,j) <= r)
				neigh[i].push_back(j);
}

void insertwormhole(double r)
{
	/*double wx1=fRand(1.0,2.0);
	double wy1=fRand(1.0,2.0);

	double wx2=fRand(8.0,9.0);
	double wy2=fRand(8.0,9.0);*/

	double wx1=fRand(0.5,1.0);
	double wy1=fRand(0.5,1.0);

	double wx2=fRand(4.0,4.5);
	double wy2=fRand(4.0,4.5);
	
	int i;
	for (i=0;i<MAXN;i++)
		if (distance(nodes[i].first,nodes[i].second,wx1,wy1) <= r )
			vw1.push_back(i);
	
	for (i=0;i<MAXN;i++)
		if (distance(nodes[i].first,nodes[i].second,wx2,wy2) <= r )
			vw2.push_back(i);
	cout << "wormhole links" << endl;
	cout << wx1 << " " << wy1 << " - "; 
	for (i=0;i<vw1.size();i++)
		cout << vw1[i] << " ";
	puts("");

	cout << "----------------" << endl;
	cout << wx2 << " " << wy2 << " - "; 
	for (i=0;i<vw2.size();i++)
		cout << vw2[i] << " ";
	puts("");
}

void updateneighbours()
{
	int i,j;
	for (i=0;i<vw1.size();i++)
	{
		for (j=0;j<vw2.size();j++)
		{
			if (find(neigh[vw1[i]].begin(),neigh[vw1[i]].end(),vw2[j])==neigh[vw1[i]].end())
				neigh[vw1[i]].push_back(vw2[j]);
		}
	}

	for (i=0;i<vw2.size();i++)
	{
		for (j=0;j<vw1.size();j++)
		{
			if (find(neigh[vw2[i]].begin(),neigh[vw2[i]].end(),vw1[j])==neigh[vw2[i]].end())
				neigh[vw2[i]].push_back(vw1[j]);
		}
	}

}

void computeTwoKhopneighbours()
{
	int i,j,k;
	for (i=0;i<MAXN;i++)
	{
		for (j=0;j<neigh[i].size();j++)
			th_neigh[i].insert(neigh[i][j]);
		for (j=0;j<neigh[i].size();j++){
			for (k=0;k<neigh[neigh[i][j]].size();k++)
				if(neigh[neigh[i][j]][k] != i)
					th_neigh[i].insert(neigh[neigh[i][j]][k]);	
		}
	}

}


void computeFourKhopneighbours()
{
	int i,j;
	for (i=0;i<MAXN;i++)
	{
		queue<pair<int,int> > q;
		q.push(make_pair(i,0));
		fh_neigh[i].insert(i);
		while (!q.empty())
		{
			pair<int,int> ss = q.front();
			q.pop();
			int node = ss.first;
			int level = ss.second;
			if (level <=4)
			{
				for (j=0;j<neigh[node].size();j++)
				{
					if (fh_neigh[i].find(neigh[node][j]) == fh_neigh[i].end()){
						fh_neigh[i].insert(neigh[node][j]);
						q.push(make_pair(neigh[node][j],level+1));
					}
				}
			}
		}
		fh_neigh[i].erase(fh_neigh[i].find(i));
	}
}

vector<int> compute_common1(int u, int v){
	vector<int> myvec;
	for(int i=0; i<neigh[u].size(); i++)
		if(find(neigh[v].begin(), neigh[v].end(), neigh[u][i]) != neigh[v].end())
			myvec.push_back(neigh[u][i]);
	return myvec;
}


vector<int> compute_common2(int u, int v){
	vector<int> myvec;
	set<int>::iterator it1;
	for(it1=th_neigh[u].begin(); it1 != th_neigh[u].end(); it1++)
		if(th_neigh[v].find(*it1) != th_neigh[v].end())
			myvec.push_back((*it1));
	return myvec;
}

vector<int> maximal_indep(vector<int>& myvec){
	vector<int> vec;
	for(int i=0;i<myvec.size();i++){
		int flag = 1;
		for(int j=0;j<vec.size();j++){
			int vert = vec[j];
			if( find(neigh[vert].begin(), neigh[vert].end(), myvec[i]) != neigh[vert].end() ){
				flag = 0;
				break;
			}
		}
		if(flag)
			vec.push_back(myvec[i]);
	}
	return vec;
}

void interrupt(int node){
	cout << "Wormhole Interrupt called by : " << node << " " << nodes[node].first << " " << nodes[node].second <<  endl ;
	return ;
}

void detectWormhole1(){
	int i;
	for(i=0; i<MAXN; i++){
		set<int> tset;
		tset = th_neigh[i];
		set<int>::iterator it = tset.begin();
		for(; it!=tset.end(); it++){
			if(find(neigh[i].begin(), neigh[i].end(), (*it) ) == neigh[i].end()){
				int ver1 = i, ver2 = (*it);
				vector<int> common;
				common = compute_common1(ver1, ver2);
				common = maximal_indep(common);
			//	int fk = compute_pn(dis(ver1,ver2),1.0,1.0) + 1;
				int fk=3;
				if(common.size() >= fk){
					gloflag = 1;
					cout << "using 1 hop - FK==" << fk << "--- ";
					interrupt(i);

				}
			}
		}
	}
	return ;
}

void detectWormhole2(){
	int i;
	for(i=0; i<MAXN; i++){
		set<int> tset;
		tset = fh_neigh[i];
		set<int>::iterator it = tset.begin();
		for(; it!=tset.end(); it++){
			if(find(neigh[i].begin(), neigh[i].end(), (*it) ) == neigh[i].end()){
				int ver1 = i, ver2 = (*it);
				vector<int> common;
				common = compute_common2(ver1, ver2);
				common = maximal_indep(common);
				//int fk = compute_pn(dis(ver1,ver2),2.0,1.0) + 1;
				int fk=8;
				if(common.size() >= fk){
					cout << "using 2 hop - FK==" << fk << "---" << common.size() << "===";
					nowhole = 1;
					interrupt(i);

				}
			}
		}
	}
	return ;
}

int main()
{
	int i,j;
	gloflag = 0;
	nowhole = 0;
	double xoff,yoff,genx,geny;	
	set<int>::iterator it;
	freopen("graph.txt", "r", stdin);
	srand(time(NULL));
	//xoff=1.0;
	//yoff=1.0;
	xoff=0.5;
	yoff=0.5;
	for (i=1;i<=10;i++){
		for (j=1;j<=10;j++){
			//genx=fRand(xoff*(i-1),xoff*i);
			//geny=fRand(yoff*(j-1),yoff*j);
			cin >> genx  >> geny;
			nodes.push_back(make_pair(genx,geny));
		}
	}
	findneighbours(1.000);
	/*for (i=0;i<MAXN;i++)
			cout << nodes[i].first << endl;
	cout<<"##################\n";
	for (i=0;i<MAXN;i++)
			cout << nodes[i].second<< endl;*/
	
//	insertwormhole(1.000);
	updateneighbours();
	/*for (i=0;i<MAXN;i++){
		cout << nodes[i].first << " " << nodes[i].second << " -- " << i << "  " ;
		for (j=0;j<neigh[i].size();j++)
			cout << neigh[i][j]<< " " ;
		puts("");
	}*/		
	computeTwoKhopneighbours();
	computeFourKhopneighbours();
	/*puts("-------------TWO HOP LIST---------------");
	for (i=0;i<MAXN;i++)
	{
		cout << i << " -- ";
		for (it=th_neigh[i].begin();it!=th_neigh[i].end();it++)
		{
			cout << (*it) << " " ;
		}
		puts("");
	}
	puts("-------------FOUR HOP LIST---------------");
	for (i=0;i<MAXN;i++)
	{
		cout << i << " -- ";
		for (it=fh_neigh[i].begin();it!=fh_neigh[i].end();it++)
		{
			cout << (*it) << " " ;
		}
		puts("");
	}*/
	detectWormhole1();

	cout << endl;
	cout << "Verification of Network with No wormhole" << endl << endl;
	if (gloflag == 0)
	{
		detectWormhole2();
	}
	if (nowhole == 0)
		cout << "NO WORMHOLE in NODAL NETWORK" << endl;

	return 0;
}
