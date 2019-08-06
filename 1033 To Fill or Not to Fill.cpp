#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-10;
double Cmax,D,Davg;
int N;
struct Station{
	double price,dis;
}sta[510];
bool cmp(Station & X,Station & Y){
	return X.dis < Y.dis;
}
int main(){
	scanf("%lf%lf%lf%d",&Cmax,&D,&Davg,&N);
	for(int i = 0 ;i < N;i ++)
		scanf("%lf%lf",&sta[i].price,&sta[i].dis);
	sort(sta,sta + N,cmp);
	sta[N].dis = D;//������ļ���վ�����յ㣬�������ȥ����ʹ�ǣ��������Ҳ����Ӱ����
	sta[N].price = 0;
	
	double CurPos = 0,tank = 0,TotalPrice = 0, Maxrange = Cmax * Davg, tankRange = 0;
	int idx;
	if(fabs(sta[0].dis) < eps){//��һ������վ�������
		for(int i = 0;i < N;){
			tankRange = tank * Davg;
			idx = i;
			for(int j = i + 1;j <= N;j ++)
				if(CurPos + tankRange >= sta[j].dis && sta[j].price < sta[idx].price)
					idx = j;
			if(idx != i){//�п��Բ����;��ܵ���ļ۸�����˼���վ
                tank -= (sta[idx].dis - CurPos) / Davg;
                CurPos = sta[idx].dis;            
				i = idx;
			}else{//û�п��Բ����;��ܵ���ļ۸�����˵ļ���վ
				for(int j = i + 1;j <= N;j ++)
					if(CurPos + Maxrange >= sta[j].dis && sta[j].price <= sta[i].price){
						idx = j;
						break;
					}
					if(idx != i){//�мӵ��;��ܵ���ļ۸���Ȼ��߸����˵ļ���վ
						TotalPrice += ((sta[idx].dis - sta[i].dis) / Davg - tank) * sta[i].price;
						tank = 0;
						CurPos = sta[idx].dis;
						i = idx;
					}else{//�����ͷ�Χ��û�м۸���Ȼ��߸����˵ļ���վ
						if(CurPos + Maxrange < sta[i + 1].dis){
							//���ͷ�Χ��û�м���վ
							TotalPrice += (Cmax - tank) * sta[i].price;
							CurPos += Maxrange;
							break;
						}else{//���ͷ�Χ��ֻ�и���ļ���վ
							if(i == N - 1){//��һվ�����յ㣬����Ҫ����
								TotalPrice += ((sta[i + 1].dis - CurPos) / Davg - tank) * sta[i].price;
								CurPos = sta[i + 1].dis;
								tank = 0;
								i ++;
							}else{//�����Ϳ������ͷ�Χ������˵ļ���վ
								idx = i + 1;
								for(int j = i + 1;j <= N;j ++)
									if(CurPos + Maxrange >= sta[j].dis && sta[j].price < sta[idx].price)
										idx = j;
								TotalPrice += (Cmax - tank) * sta[i].price;
								tank = Cmax;
								tank -= (sta[idx].dis - CurPos) / Davg;
								CurPos = sta[idx].dis;
								i = idx;
							}
						}
					}
			}
		}
	}
	if(CurPos == D)
		printf("%.2lf",TotalPrice);
	else
		printf("The maximum travel dis = %.2f",CurPos);
	return 0;
}