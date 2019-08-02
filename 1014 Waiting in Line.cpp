#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 21
#define OPENTIME 8 * 60
#define CLOSETIME 17 * 60
int N,M,K,Q;
struct Customer {
	int No,pTime,startTime,endTime;
	Customer() {}
};
queue <Customer> Outer, Inner[MAXN];
map <int, Customer> Done;
map <int, Customer>::iterator it;
int table[MAXN] = {0};
int FindEarliest() {
	int idx = -1,endTime = 0x3f3f3f3f;
	for(int i = 0; i < N; i ++) {
		if(table[i] > 0 && Inner[i].front().endTime < endTime) {
			endTime = Inner[i].front().endTime;
			idx = i;
		}
	}
	return idx;
}
int main() {
	scanf("%d%d%d%d",&N,&M,&K,&Q);
	Customer tmp;
	tmp.startTime = OPENTIME;
	for(int i = 1; i <= K; i ++) {
		scanf("%d",&tmp.pTime);
		tmp.No = i;
		Outer.push(tmp);
	}
	int leastQ;
	while(!Outer.empty()) {
		leastQ = min_element(table,table + N) - table;//�������ٵĶ��飬�������ʱ�ұ����С��
		if(Inner[leastQ].size() == M) { //inner queues are full,someone must be out
			int idx = FindEarliest();
			tmp = Inner[idx].front();
			Done.insert(make_pair(tmp.No,tmp));
			Inner[idx].pop();
			table[idx] --;
			if(table[idx] > 0) { //�ö����ﻹ���ˣ���Ҫ���º�����˵Ŀ�ʼʱ��ͽ���ʱ��
				Inner[idx].front().startTime = tmp.endTime;
				Inner[idx].front().endTime = tmp.endTime + Inner[idx].front().pTime;
			}
		} else {
			tmp = Outer.front();
			Outer.pop();
			if(table[leastQ] == 0)//��һ������ö�����ˣ�����ʱ����ǿ���ʱ����ϴ���ʱ��
				tmp.endTime = OPENTIME + tmp.pTime;
			Inner[leastQ].push(tmp);
			table[leastQ] ++;
		}
	}

	int cnt = 0;
	for(int i = 0; i < N; i ++)
		cnt += table[i];
	while(cnt) {
		int idx = FindEarliest();
		cnt --;
		table[idx] --;
		tmp = Inner[idx].front();
		Done.insert(make_pair(tmp.No,tmp));
		Inner[idx].pop();
		if(table[idx] > 0) {
			Inner[idx].front().startTime = tmp.endTime;
			Inner[idx].front().endTime = tmp.endTime + Inner[idx].front().pTime;
		}
	}

	int No;
	for(int i = 0; i < Q; i ++) {
		scanf("%d",&No);
		it = Done.find(No);
		if(it->second.startTime >= CLOSETIME)
			printf("Sorry\n");
		else
			printf("%02d:%02d\n",it->second.endTime / 60,it->second.endTime % 60);
	}
	return 0;
}
