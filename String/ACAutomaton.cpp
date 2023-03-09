#include <iostream>
#include <queue>


using namespace std;

const int N = 1e5+100;

struct Trie
{
	int cnt;
	Trie* nxt[2];
	Trie* fail;
	bool vis;
	Trie(){
		cnt=0;
		vis=0;
		for(auto &x:nxt)x=nullptr;
	}
};

void clear(Trie*root){
	for(auto x:root->nxt){
		if(x!=nullptr){
			clear(x);
		}
	}
	root->vis=0;
}
void insert(Trie*root,string&s){
	Trie*p = root;
	for(auto x:s){
		int id = x-'0';
		if(p->nxt[id]==nullptr){
			Trie*tmp = new Trie;
			p->nxt[id]=tmp;
		}
		p=p->nxt[id];
	}
	p->cnt++;
}
void build(Trie*root){
	queue<Trie*>Q;
	Trie *p = root;
	root->fail=nullptr;
	Q.push(p);
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		for(int i = 0; i < 2; ++i){
			if(p->nxt[i]!=nullptr){
				if(p==root)p->nxt[i]->fail=p;
				else {
					Trie*tmp = p->fail;
					while(tmp!=nullptr){
						if(tmp->nxt[i]!=nullptr){
							p->nxt[i]->fail=tmp->nxt[i];
							break;
						}
						tmp=tmp->fail;
					}
					if(tmp == nullptr)p->nxt[i]->fail=root;
				}
			}
			Q.push(p->nxt[i]);
		}
	}
}
int qry(Trie*root,string&s){
	int ans = 0;
	Trie*p = root;
	for(auto x: s){
		int id = x - '0';
		while(p->nxt[id]==nullptr&&p!=root)p=p->fail;
		p=p->nxt[id];
		if(p==nullptr)p=root;
		Trie*tmp = p;
		while(tmp!=root&&!tmp->vis){
			ans+=tmp->cnt;
			tmp->vis=1;
			tmp=tmp->fail;
		}
	}
}
