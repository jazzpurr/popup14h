// Authors:
// Didrik Nordström, didrikn@kth.se
// Jesper Norberg, jenor@kth.se

#ifndef GENERAL
#define GENERAL

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <climits>
#include <cassert>
#include <algorithm>
#include <functional>

using namespace std;

template<class T> void print(T const &x) { ostringstream os; os << x; cout << os.str() << endl; }
template<class T> void print(vector<T> const &v) { ostringstream os; for (int i = 0; i < v.size(); ++i){ if (i)os << ' '; os << v[i]; } cout << os.str() << endl; }
template<class T> void print(vector<vector<T> > const &v){ ostringstream os; for (int i = 0; i < v.size(); ++i) { for (int j = 0; j < v[i].size(); ++j){ if (j)os << ' '; os << v[i][j]; }os << endl; }cout << os.str() << endl; }
template<class T, class U> T cast(U x) { ostringstream os; os << x; T res; istringstream is(os.str()); is >> res; return res; }
template<class T> vector<T> split(string s, string x = " ") { vector<T> res; for (int i = 0; i < s.size(); i++){ string a; while (i < (int)s.size() && x.find(s[i]) == string::npos)a += s[i++]; if (!a.empty())res.push_back(cast<T>(a)); } return res; }

#define EPS 1e-9
#define PI 3.14159265359

#define ffor(i, a, b) for (int i = (a); i < (b); ++i)                         // for-loop
#define rfor(i, b, a) for (int i = (b); i >= a; --i)                       // reverse for-loop
#define foreach(it, v) for (auto &it : v)    // foreach-loop
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0)) // determine the sign of x
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define maximum(a) (*max_element(all(a)))
#define minimum(a) (*min_element(all(a)))

using namespace std;

typedef long long LL;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long> vl;
typedef vector<vl> vvl;
typedef vector<LL> vLL;
typedef vector<vLL> vvLL;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef pair<bool, bool> pbb;
typedef pair<bool, int> pbi;
typedef pair<bool, long> pbl;
typedef pair<bool, LL> pbLL;
typedef pair<bool, double> pbd;
typedef pair<bool, string> pbs;
typedef pair<int, bool> pib;
typedef pair<int, int> pii;
typedef pair<int, long> pil;
typedef pair<int, LL> piLL;
typedef pair<int, double> pid;
typedef pair<int, string> pis;
typedef pair<long, bool> plb;
typedef pair<long, int> pli;
typedef pair<long, long> pll;
typedef pair<long, LL> plLL;
typedef pair<long, double> pld;
typedef pair<long, string> pls;
typedef pair<LL, bool> pLLb;
typedef pair<LL, int> pLLi;
typedef pair<LL, long> pLLl;
typedef pair<LL, LL> pLLLL; //hihi
typedef pair<LL, double> pLLd;
typedef pair<LL, string> pLLs;
typedef pair<double, bool> pdb;
typedef pair<double, int> pdi;
typedef pair<double, long> pdl;
typedef pair<double, LL> pdLL;
typedef pair<double, double> pdd;
typedef pair<double, string> pds;
typedef pair<string, bool> psb;
typedef pair<string, int> psi;
typedef pair<string, long> psl;
typedef pair<string, LL> psLL;
typedef pair<string, double> psd;
typedef pair<string, string> pss;
typedef vector<pbb> vpbb;
typedef vector<pbi> vpbi;
typedef vector<pbl> vpbl;
typedef vector<pbLL> vpbLL;
typedef vector<pbd> vpbd;
typedef vector<pbs> vpbs;
typedef vector<pib> vpib;
typedef vector<pii> vpii;
typedef vector<pil> vpil;
typedef vector<piLL> vpiLL;
typedef vector<pid> vpid;
typedef vector<pis> vpis;
typedef vector<plb> vplb;
typedef vector<pli> vpli;
typedef vector<pll> vpll;
typedef vector<plLL> vplLL;
typedef vector<pld> vpld;
typedef vector<pls> vpls;
typedef vector<pLLb> vpLLb;
typedef vector<pLLi> vpLLi;
typedef vector<pLLl> vpLLl;
typedef vector<pLLLL> vpLLLL; //hihi
typedef vector<pLLd> vpLLd;
typedef vector<pLLs> vpLLs;
typedef vector<pdb> vpdb;
typedef vector<pdi> vpdi;
typedef vector<pdl> vpdl;
typedef vector<pdLL> vpdLL;
typedef vector<pdd> vpdd;
typedef vector<pds> vpds;
typedef vector<psb> vpsb;
typedef vector<psi> vpsi;
typedef vector<psl> vpsl;
typedef vector<psLL> vpsLL;
typedef vector<psd> vpsd;
typedef vector<pss> vpss;
typedef vector<vpbb> bbGraph;
typedef vector<vpbi> biGraph;
typedef vector<vpbl> blGraph;
typedef vector<vpbLL> bLLGraph;
typedef vector<vpbd> bdGraph;
typedef vector<vpbs> bsGraph;
typedef vector<vpib> ibGraph;
typedef vector<vpii> iiGraph;
typedef vector<vpil> ilGraph;
typedef vector<vpiLL> iLLGraph;
typedef vector<vpid> idGraph;
typedef vector<vpis> isGraph;
typedef vector<vplb> lbGraph;
typedef vector<vpli> liGraph;
typedef vector<vpll> llGraph;
typedef vector<vplLL> lLLGraph;
typedef vector<vpld> ldGraph;
typedef vector<vpls> lsGraph;
typedef vector<vpLLb> LLbGraph;
typedef vector<vpLLi> LLiGraph;
typedef vector<vpLLl> LLlGraph;
typedef vector<vpLLLL> LLLLGraph; //hihi
typedef vector<vpLLd> LLdGraph;
typedef vector<vpLLs> LLsGraph;
typedef vector<vpdb> dbGraph;
typedef vector<vpdi> diGraph;
typedef vector<vpdl> dlGraph;
typedef vector<vpdLL> dLLGraph;
typedef vector<vpdd> ddGraph;
typedef vector<vpds> dsGraph;
typedef vector<vpsb> sbGraph;
typedef vector<vpsi> siGraph;
typedef vector<vpsl> slGraph;
typedef vector<vpsLL> sLLGraph;
typedef vector<vpsd> sdGraph;
typedef vector<vpss> ssGraph;

#endif // header guard