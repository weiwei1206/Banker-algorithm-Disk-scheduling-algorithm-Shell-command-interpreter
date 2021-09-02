#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define MaxNum 20
static int n;//�У�������
static int m;//�У���Դ��
static int all;//������Դֵ�Ƿ�ȫΪ��
static int flag;//�жϰ�ȫ��ʾ
static char ID[MaxNum];//���̳���
static int Max[MaxNum][MaxNum];//��������������Դ
static int Allocation[MaxNum][MaxNum];//�����ѷ�����Դ
static int Need[MaxNum][MaxNum];//���̻���Ҫ��Դ
static int Available[MaxNum];////ϵͳ�ɷ�����Դ

static int Request[MaxNum];//ָ��ִ�н���������Դ
static int SafeOrder[MaxNum];//��ȫִ��˳��

void Enter();//��ʼ������������ѷ�����Դ��������Դ��ϵͳ�ɷ�����Դ��������������������Դ
bool Safe();//�жϵ�ǰ�Ƿ�ȫ
void banker();//ִ�����м��㷨�����ִ��ĳһ���̺��Ƿ�ȫ
void display();//��ʾ���

int main(){
	
    Enter();
	Safe();
    banker();
    return 0;
}

//��ʼ������������ѷ�����Դ��������Դ��ϵͳ�ɷ�����Դ��������������������Դ
void Enter(){
    int i,j;

    cout<<"�����������: ";
    cin>>n;

    cout<<"������Դ��������: ";
    cin>>m;

    //��ʼ��������
    for (i=0;i<m;i++){
        ID[i]=i+65;
    }
	cout<<"��������������: "<<endl;
    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            cin>>Max[i][j];
        }
    }

	 cout<<"����������: "<<endl;
    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            cin>>Allocation[i][j];
        }
    }

    cout<<"�����������Դ����: ";
    for (i=0;i<m;i++){
        cin>>Available[i];
    }

    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    display();

}

//�жϵ�ǰ״̬�Ƿ�ȫ
bool Safe(){
    int work[MaxNum];
    bool Finish[MaxNum];//����Ƿ�ȫ
    for (int i=0;i<m;i++){
        work[i] = Available[i];
    }
    //��ʼ����ȫ����
    for ( i=0;i<n;i++){
        Finish[i] = false;
        SafeOrder[i] = -1;
    }

    int FinishNumebr = 0;
    int isSafe;
    int j;
	i=0;
    while(i<n){
        isSafe = 0;
        //�жϽ��̶�Ӧ��������Դ�������Ƿ�����û����ɡ�������ԴС�ڿ��ṩ��Դ
        for(j=0;j<m;j++){
            if (Finish[i]==false && Need[i][j]<=work[j])
                isSafe++;
            else
                break;
        }

        //���ҽ������̶�Ӧ��������Դ�������������ʱ��Ž�����Դִ��
        if (isSafe == m){
            Finish[i] = true;//��Ǹ���Դ��ִ��
            SafeOrder[FinishNumebr] = i;//��¼��ִ�еİ�ȫ����Դ�ı��
			//cout<<"�ͷ��̵߳�Ϊ��"<<i;
			//cout<<endl;
            FinishNumebr++;
            //��ȫ����Դִ�У��ͷ���������Դ
            for (j=0;j<m;j++){
                work[j] += Allocation[i][j];
            }
			
            i=0;  //�ҵ����������Ľ��̲�ִ�к��ٴ�ͷ��ʼ��Ѱ��������������Դ
        }
        else
            i++; //���û��������������Դ��鿴��һ����Դ

        //��Դȫ����ȫִ�������ִ��˳��
        if (FinishNumebr==n){
            cout<<"Ŀǰϵͳ�ǰ�ȫ��"<<endl;;
			flag=7;
            cout<<"��ȫ����Ϊ: P"<<SafeOrder[0];
            for (i=1;i<n;i++){
                cout<<" -> P"<<SafeOrder[i] ;
            }
            cout<<endl;
            return true;
        }
    }

    //��û��ִ�������г������ǲ���ȫ��
	//cout<<"FinshNumber��ֵΪ��"<<FinishNumebr;
	//cout<<endl;
    cout<<"Ŀǰϵͳ�ǲ���ȫ��"<<endl;
    return false;
}

//ִ�����м��㷨�����ִ��ĳһ���̺��Ƿ�ȫ
void banker(){
    int i,j;
    int chooseP;
    char isContinue;

while(true){

        bool RequestNeed = false;
        bool RequestAvailable = false;

        cout<<"����������Դ�Ľ��̺�: ";
        cin>>chooseP;
        cout<<"��������������Դ����: ";
        while(RequestNeed==false){
            for (int i=0;i<m;i++){
                cin>>Request[i];
            }
            for (i=0;i<m;i++){
                //�ж�Request�Ƿ����Need
                if (Request[i]>Need[chooseP][i]){
                    cout<<"����������Դ�������������������������룡"<<endl;
                    RequestNeed = false;
                    continue;
                }
                else
                    RequestNeed = true;
                //�ж�Request�Ƿ����Available
                if (Request[i]>Available[i]){
                    cout<<"����������Դ�������ڿ�������Դ�������������룡"<<endl;
                    RequestAvailable = false;
                    continue;
                }
                else
				{   RequestNeed = true;
					RequestAvailable = true;
				}
            }
        }


        //��Ҫ���ȵ���Դִ��
        for (j = 0;j<m;j++){
            Available[j] -=Request[j];
            Allocation[chooseP][j] += Request[j];
            Need[chooseP][j] -= Request[j];
        }
	
        //�������ȫ����ָ���ԭ����ֵ������
if (!Safe())   {
				 for (j = 0;j<m;j++){
						  Available[j] +=Request[j];
							Allocation[chooseP][j] -= Request[j];
								Need[chooseP][j] += Request[j];
										 }
								//����������ȴ����ȫ�ǣ�֤��ϵͳ�Ѳ����ٷ�����Դ��������״̬
						if (RequestAvailable&&RequestNeed){
							 cout<<"ϵͳ����ȫ�������ٽ��з�����Դ"<<endl;
									}
				}
			
if(flag==7){
			all=Need[chooseP][0];
				for (j = 1;j<m;j++)
				{
					all=all+Need[chooseP][j];
				}
				if(all==0)
				{
					cout<<"����Դȫ���� "<<endl;	
					for(j=0;j<m;j++){
					Available[j]=Available[j]+Allocation[chooseP][j];
				}
			}
			
		

        }

			cout<<"��Դ�����P"<<chooseP<<"�̺߳�: "<<endl;
			display();	
        cout<<"�Ƿ����Ϊ�߳�������Դ(Y/N): ";
        cin>>isContinue;
        if (isContinue=='Y'||isContinue=='y')//input();//ʵ�ֶ�����󣨱�����һ�������״̬��
            continue;
        else if (isContinue=='N'||isContinue=='n')
            break;

}
}

//��ʾ���
void display(){
    int i,j;
    int processName[MaxNum];
    for (i=0;i<MaxNum;i++){
        processName[i]=i;
    }
    cout<<endl;

    cout<<"processName"<<"\t";
    cout<<"Max"<<"\t\t";
    cout<<"Allocation"<<"\t";
    cout<<"Need"<<"\t\t";
    cout<<"Available"<<endl;
    cout<<"\t\t";
    for (i=0;i<m;i++){
        cout<<ID[i]<<"  ";
    }
    cout<<"\t";
    for (i=0;i<m;i++){
        cout<<ID[i]<<"  ";
    }
    cout<<"\t";
    for (i=0;i<m;i++){
        cout<<ID[i]<<"  ";
    }
    cout<<"\t";
    for (i=0;i<m;i++){
        cout<<ID[i]<<"  ";
    }
    cout<<endl;


    bool FirstLine = true;  //Avaliable����ֻ�����һ��
    for (i=0;i<n;i++){
        cout<<"P"<<processName[i]<<"\t\t";
        for (j=0;j<m;j++){
            cout<<Max[i][j]<<"  ";
        }
        cout<<"\t";
        for (j=0;j<m;j++){
            cout<<Allocation[i][j]<<"  ";
        }
        cout<<"\t";
        for (j=0;j<m;j++){
            cout<<Need[i][j]<<"  ";
        }
        cout<<"\t";
        if (FirstLine){
            for (j=0;j<m;j++){
                cout<<Available[j]<<"  ";
            }
            FirstLine = false;
        }
        cout<<endl;
    }
}
