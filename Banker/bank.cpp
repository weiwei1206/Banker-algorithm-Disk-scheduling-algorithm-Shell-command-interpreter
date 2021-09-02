#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define MaxNum 20
static int n;//行，进程数
static int m;//列，资源数
static int all;//计算资源值是否全为零
static int flag;//判断安全标示
static char ID[MaxNum];//进程程名
static int Max[MaxNum][MaxNum];//进程所需所有资源
static int Allocation[MaxNum][MaxNum];//进程已分配资源
static int Need[MaxNum][MaxNum];//进程还需要资源
static int Available[MaxNum];////系统可分配资源

static int Request[MaxNum];//指定执行进程所需资源
static int SafeOrder[MaxNum];//安全执行顺序

void Enter();//初始化，输入进程已分配资源、仍需资源、系统可分配资源，计算出进程所需最大资源
bool Safe();//判断当前是否安全
void banker();//执行银行家算法，检测执行某一进程后是否安全
void display();//显示结果

int main(){
	
    Enter();
	Safe();
    banker();
    return 0;
}

//初始化，输入进程已分配资源、仍需资源、系统可分配资源，计算出进程所需最大资源
void Enter(){
    int i,j;

    cout<<"输入进程数量: ";
    cin>>n;

    cout<<"输入资源种类数量: ";
    cin>>m;

    //初始化进程名
    for (i=0;i<m;i++){
        ID[i]=i+65;
    }
	cout<<"输入最大需求矩阵: "<<endl;
    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            cin>>Max[i][j];
        }
    }

	 cout<<"输入分配矩阵: "<<endl;
    for (i=0;i<n;i++){
        for (j=0;j<m;j++){
            cin>>Allocation[i][j];
        }
    }

    cout<<"输入可利用资源向量: ";
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

//判断当前状态是否安全
bool Safe(){
    int work[MaxNum];
    bool Finish[MaxNum];//标记是否安全
    for (int i=0;i<m;i++){
        work[i] = Available[i];
    }
    //初始化安全序列
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
        //判断进程对应的所有资源的数量是否都满足没有完成、所需资源小于可提供资源
        for(j=0;j<m;j++){
            if (Finish[i]==false && Need[i][j]<=work[j])
                isSafe++;
            else
                break;
        }

        //当且仅当进程对应的所有资源的数量都满足的时候才将该资源执行
        if (isSafe == m){
            Finish[i] = true;//标记该资源已执行
            SafeOrder[FinishNumebr] = i;//记录已执行的安全的资源的编号
			//cout<<"释放线程的为："<<i;
			//cout<<endl;
            FinishNumebr++;
            //安全的资源执行，释放其所需资源
            for (j=0;j<m;j++){
                work[j] += Allocation[i][j];
            }
			
            i=0;  //找到满足条件的进程并执行后，再从头开始再寻找满足条件的资源
        }
        else
            i++; //如果没有满足条件的资源则查看下一个资源

        //资源全部安全执行则输出执行顺序
        if (FinishNumebr==n){
            cout<<"目前系统是安全的"<<endl;;
			flag=7;
            cout<<"安全序列为: P"<<SafeOrder[0];
            for (i=1;i<n;i++){
                cout<<" -> P"<<SafeOrder[i] ;
            }
            cout<<endl;
            return true;
        }
    }

    //若没有执行完所有程序则是不安全的
	//cout<<"FinshNumber的值为："<<FinishNumebr;
	//cout<<endl;
    cout<<"目前系统是不安全的"<<endl;
    return false;
}

//执行银行家算法，检测执行某一进程后是否安全
void banker(){
    int i,j;
    int chooseP;
    char isContinue;

while(true){

        bool RequestNeed = false;
        bool RequestAvailable = false;

        cout<<"输入申请资源的进程号: ";
        cin>>chooseP;
        cout<<"输入请求分配的资源数量: ";
        while(RequestNeed==false){
            for (int i=0;i<m;i++){
                cin>>Request[i];
            }
            for (i=0;i<m;i++){
                //判断Request是否大于Need
                if (Request[i]>Need[chooseP][i]){
                    cout<<"请求分配的资源数量大于需求量，请重新输入！"<<endl;
                    RequestNeed = false;
                    continue;
                }
                else
                    RequestNeed = true;
                //判断Request是否大于Available
                if (Request[i]>Available[i]){
                    cout<<"请求分配的资源数量大于可利用资源量，请重新输入！"<<endl;
                    RequestAvailable = false;
                    continue;
                }
                else
				{   RequestNeed = true;
					RequestAvailable = true;
				}
            }
        }


        //将要调度的资源执行
        for (j = 0;j<m;j++){
            Available[j] -=Request[j];
            Allocation[chooseP][j] += Request[j];
            Need[chooseP][j] -= Request[j];
        }
	
        //如果不安全，则恢复到原来的值并警告
if (!Safe())   {
				 for (j = 0;j<m;j++){
						  Available[j] +=Request[j];
							Allocation[chooseP][j] -= Request[j];
								Need[chooseP][j] += Request[j];
										 }
								//当输入无误却不安全是，证明系统已不能再分配资源进入死锁状态
						if (RequestAvailable&&RequestNeed){
							 cout<<"系统不安全，不能再进行分配资源"<<endl;
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
					cout<<"该资源全分配 "<<endl;	
					for(j=0;j<m;j++){
					Available[j]=Available[j]+Allocation[chooseP][j];
				}
			}
			
		

        }

			cout<<"资源分配给P"<<chooseP<<"线程后: "<<endl;
			display();	
        cout<<"是否继续为线程申请资源(Y/N): ";
        cin>>isContinue;
        if (isContinue=='Y'||isContinue=='y')//input();//实现多次请求（保留上一次请求的状态）
            continue;
        else if (isContinue=='N'||isContinue=='n')
            break;

}
}

//显示结果
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


    bool FirstLine = true;  //Avaliable数组只输出第一行
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
