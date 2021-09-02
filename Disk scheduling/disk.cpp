#include <stdio.h>
#include <algorithm>
#include <string.h>
#define maxsize 1000 //¶šÒå×îŽóÊý×éÓò

void FIFO(int disk[],int m)
{
	int sum;
	float avg;
	int p;
	int i;
	printf("\nÇëÊäÈëŽÅÍ·³õÊŒÎ»ÖÃ£º\n");
	scanf("%d",&p);
	printf("\n FIFOŽÅÅÌµ÷¶Èœá¹û£º");
	printf("%d ",p);
	for(i=0;i<m;i++)
	{
		printf("%d ",disk[i]);
	}
	printf("\n");
	sum=abs(p-disk[0]);
	for(i=1;i<m;i++)
	{
		sum+=abs(disk[i]-disk[i-1]);//ÀÛŒÆÒÆ¶¯ŸàÀë
	}
	avg=(sum*1.0)/m;//ÆœŸùÑ°ÕÒ³€¶È
	printf(" ŽÅÍ·ÒÆ¶¯µÄ×ÜŽÅµÀÊý£º %d \n",sum);
    printf(" ÆœŸùÑ°ÕÒ³€¶È£º %f \n",avg);
}
void SSTF(int disk[],int m)
{
	int i;
	int sum=0;
	float avg;
	int temp;
	int p;
	int Y=1;
	int T;
	int U;
	int j=0;



	for(i=0;i<m;i++)//œ«ŽÅµÀŽÓÐ¡µœŽóÅÅÐò
	{
		for(j=i+1;j<m;j++)
		{
			if(disk[i]>disk[j])
			{
				temp=disk[i];
				disk[i]=disk[j];
				disk[j]=temp;			
			}
		}
	}
	
	printf("\nÅÅÐòºóŽÅµÀÐòÁÐÎª£º");
	for(i=0;i<m;i++)
	{
		printf("%d ",disk[i] );
	}
	printf("\nÇëÊäÈëŽÅÍ·³õÊŒÎ»ÖÃ£º\n");
	scanf("%d",&p);
	printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");

	if(disk[m-1]<=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒÐ¡ÓÚµ±Ç°ŽÅµÀºÅ
    {	
		printf("%d ",p);
        for(i=m-1; i>=0; i--) //œ«Êý×éŽÅµÀºÅŽÓŽóµœÐ¡Êä³ö
            printf("%d  ",disk[i] );
        sum=p-disk[0];//ŒÆËãÒÆ¶¯ŸàÀë
    }
    else if(disk[0]>=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒŽóÓÚµ±Ç°ŽÅµÀºÅ
    {
		printf("%d ",p);
        for(i=0; i<m; i++) //œ«ŽÅµÀºÅŽÓÐ¡µœŽóÊä³ö
            printf("%d ",disk[i]);
        sum=disk[m-1]-p;//ŒÆËãÒÆ¶¯ŸàÀë
    }
    else
    {
        while(disk[Y]<p)
		{
			Y++;
		}
		T=Y-1;
		U=Y;
		while((T>=0)&&(U<m))
		{
			if(p-disk[T]<=disk[U]-p)
			{
				printf("%d ",disk[T]);
				sum+=p-disk[T];
				p=disk[T];
				T--;
			}
			else
			{
				printf("%d ",disk[U]);
				sum+=disk[U]-p;
				p=disk[U];
				U++;
			}
		}
		if(T==-1)
		{
			for(i=U;i<m;i++)
			{
				printf("%d ",disk[i] );
			}
			sum=sum+disk[m-1]-disk[0];
		}
		else
		{
			for(i=T;i>=0;i--)
				printf("%d ",disk[i] );
			sum+=disk[m-1]-disk[0];
		}

    }
	avg=(sum*1.0)/m;//ÆœŸùÑ°ÕÒ³€¶È
	printf("\nŽÅÍ·ÒÆ¶¯µÄ×ÜŽÅµÀÊý£º %d \n",sum);
    printf(" ÆœŸùÑ°ÕÒ³€¶È£º %f \n",avg);
}
void SCAN(int disk[],int m)
{
	int i;
	int j;
	int temp;
	int flag;
	int q;
	int Y=1;
	int U;
	int T;
	float avg;
	int sum=0;
	int p;
		for(i=0;i<m;i++)//œ«ŽÅµÀŽÓÐ¡µœŽóÅÅÐò
	{
		for(j=i+1;j<m;j++)
		{
			if(disk[i]>disk[j])
			{
				temp=disk[i];
				disk[i]=disk[j];
				disk[j]=temp;			
			}
		}
	}
	printf("\nÅÅÐòºóŽÅµÀÐòÁÐÎª£º");
	for(i=0;i<m;i++)
	{
		printf("%d ",disk[i] );
	}
	printf("\nÇëÊäÈëŽÅÍ·³õÊŒÎ»ÖÃ£º");
	scanf("%d",&p);
	printf("\nÇëÊäÈëÄ©ŽÅµÀºÅ£º");
	scanf("%d",&q);
	printf("\n1.ÔöŽó·œÏòÒÆ¶¯ 2.ŒõÐ¡·œÏòÒÆ¶¯");
	printf("\nÇëÊäÈëŽÅÍ·ÒÆ¶¯·œÊœ£º");
	scanf("%d",&flag);
	if(flag==1)
	{
			
			if(disk[m-1]<=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒÐ¡ÓÚµ±Ç°ŽÅµÀºÅ
			 {	
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p); printf("%d ",q);
				 for(i=m-1; i>=0; i--) //œ«Êý×éŽÅµÀºÅŽÓŽóµœÐ¡Êä³ö
				   printf("%d  ",disk[i] );
					sum=q-p+q-disk[0];//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else if(disk[0]>p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒŽóÓÚµ±Ç°ŽÅµÀºÅ
			 {
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p);
				 for(i=0; i<m; i++) //œ«ŽÅµÀºÅŽÓÐ¡µœŽóÊä³ö
					 printf("%d ",disk[i]);
						 sum=disk[m-1]-p;//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else
			 {
				while(disk[Y]<p)
				{
					Y++;
				}
					T=Y-1;
					U=Y;
				 //È·¶šŽÅµÀÔÚÒÑÅÅµÄÐòÁÐÖÐµÄÎ»ÖÃ
					printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
					printf("%d ",p);
					for(i=Y;i<m;i++)
						printf("%d ",disk[i]);
					printf("%d ",q);
					for(i=T;i>=0;i--)
						printf("%d ",disk[i]);
					sum=q-p+q-disk[0];
			 }
			
	}
	if(flag==2)
	{
		if(disk[m-1]<=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒÐ¡ÓÚµ±Ç°ŽÅµÀºÅ
			 {	
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p); 
				 for(i=m-1; i>=0; i--) //œ«Êý×éŽÅµÀºÅŽÓŽóµœÐ¡Êä³ö
				   printf("%d  ",disk[i] );
					printf("0 ");
					sum=p-disk[0];//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else if(disk[0]>=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒŽóÓÚµ±Ç°ŽÅµÀºÅ
			 {
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p);printf("0 ");
				 for(i=0; i<m; i++) //œ«ŽÅµÀºÅŽÓÐ¡µœŽóÊä³ö
					 printf("%d ",disk[i]);
						 sum=p+disk[m-1];//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else
			 {
				while(disk[Y]<p)
				{
					Y++;
				}
					T=Y-1;
					U=Y;
				 //È·¶šŽÅµÀÔÚÒÑÅÅµÄÐòÁÐÖÐµÄÎ»ÖÃ
					printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
					printf("%d ",p);
					for(i=T;i>=0;i--)
						printf("%d ",disk[i]);
					printf("0 ");
					for(i=Y;i<m;i++)
						printf("%d ",disk[i]);
					sum=p+disk[m-1];
			 }
	}
	avg=(sum*1.0)/m;//ÆœŸùÑ°ÕÒ³€¶È
	printf("\nŽÅÍ·ÒÆ¶¯µÄ×ÜŽÅµÀÊý£º %d \n",sum);
    printf(" ÆœŸùÑ°ÕÒ³€¶È£º %f \n",avg);
}
void CSCAN(int disk[],int m)
{
	int i;
	int j;
	int temp;
	int flag;
	int q;
	int Y=1;
	int U;
	int T;
	float avg;
	int sum=0;
	int p;
		for(i=0;i<m;i++)//œ«ŽÅµÀŽÓÐ¡µœŽóÅÅÐò
	{
		for(j=i+1;j<m;j++)
		{
			if(disk[i]>disk[j])
			{
				temp=disk[i];
				disk[i]=disk[j];
				disk[j]=temp;			
			}
		}
	}
	printf("\nÅÅÐòºóŽÅµÀÐòÁÐÎª£º");
	for(i=0;i<m;i++)
	{
		printf("%d ",disk[i] );
	}
	printf("\nÇëÊäÈëŽÅÍ·³õÊŒÎ»ÖÃ£º");
	scanf("%d",&p);
	printf("\nÇëÊäÈëÄ©ŽÅµÀºÅ£º");
	scanf("%d",&q);
	printf("\n1.ÔöŽó·œÏòÒÆ¶¯ 2.ŒõÐ¡·œÏòÒÆ¶¯");
	printf("\nÇëÊäÈëŽÅÍ·ÒÆ¶¯·œÊœ£º");
	scanf("%d",&flag);
	if(flag==1)
	{
			if(disk[m-1]<=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒÐ¡ÓÚµ±Ç°ŽÅµÀºÅ
			 {	
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p); printf("%d ",q);printf("0 ");
				  for(i=0; i<m; i++) //œ«ŽÅµÀºÅŽÓÐ¡µœŽóÊä³ö
					 printf("%d ",disk[i]);
					sum=q-p+disk[m-1];//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else if(disk[0]>p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒŽóÓÚµ±Ç°ŽÅµÀºÅ
			 {
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p);
				 for(i=0; i<m; i++) //œ«ŽÅµÀºÅŽÓÐ¡µœŽóÊä³ö
					 printf("%d ",disk[i]);
						 sum=disk[m-1]-p;//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else
			 {
				while(disk[Y]<p)
				{
					Y++;
				}
					T=Y-1;
					U=Y;
				 //È·¶šŽÅµÀÔÚÒÑÅÅµÄÐòÁÐÖÐµÄÎ»ÖÃ
					printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
					printf("%d ",p);
					for(i=Y;i<m;i++)
						printf("%d ",disk[i]);
					printf("%d ",q);
					printf("0 ");
					for(i=0;i<=T;i++)
						printf("%d ",disk[i]);
					sum=q-p+q+disk[T];
			 }
	}
		if(flag==2)
	{
		if(disk[m-1]<=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒÐ¡ÓÚµ±Ç°ŽÅµÀºÅ
			 {	
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p); 
				 for(i=m-1; i>=0; i--) //œ«Êý×éŽÅµÀºÅŽÓŽóµœÐ¡Êä³ö
				   printf("%d  ",disk[i] );
					sum=p-disk[0];//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else if(disk[0]>=p)//ÅÐ¶ÏÕûžöÊý×éÀïµÄÊýÊÇ·ñ¶ŒŽóÓÚµ±Ç°ŽÅµÀºÅ
			 {
				printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
				printf("%d ",p);printf("0 ");printf("%d ",q);
				 for(i=m-1; i>=0; i--) //œ«Êý×éŽÅµÀºÅŽÓŽóµœÐ¡Êä³ö
				   printf("%d  ",disk[i] );
						 sum=p+q+disk[m-1]-disk[0];//ŒÆËãÒÆ¶¯ŸàÀë
			 }
			else
			 {
				while(disk[Y]<p)
				{
					Y++;
				}
					T=Y-1;
					U=Y;
				 //È·¶šŽÅµÀÔÚÒÑÅÅµÄÐòÁÐÖÐµÄÎ»ÖÃ
					printf("SSTFŽÅÅÌµ÷¶Èœá¹û£º");
					printf("%d ",p);
					for(i=T;i>=0;i--)
						printf("%d ",disk[i]);
					printf("0 ");
					printf("%d ",q);
					for(i=m-1;i>=U;i--)
						printf("%d ",disk[i]);
					sum=p+q+disk[m-1]-disk[U];
			 }
	}
	avg=(sum*1.0)/m;//ÆœŸùÑ°ÕÒ³€¶È
	printf("\nŽÅÍ·ÒÆ¶¯µÄ×ÜŽÅµÀÊý£º %d \n",sum);
    printf(" ÆœŸùÑ°ÕÒ³€¶È£º %f \n",avg);

}


int main(){
	int SerialNumber;//Ñ¡ÔñÐòºÅ
	int DiskTrackNumber;//ŽÅµÀÊýÁ¿
	int i;//±äÁ¿
	int TrcakSequence[maxsize];//ŽÅµÀÐòÁÐ
	int count;//ŽÅµÀÊýÁ¿Öµ


	printf("----------ŽÅÅÌµ÷¶ÈËã·šÄ£Äâ----------\n");

	printf("ÇëÊäÈëŽÅµÀÊýÁ¿£º\n");
	scanf("%d",&DiskTrackNumber);

	printf("ÇëÊäÈëŽÅµÀÐòÁÐ£º\n");
	for(i=0;i<DiskTrackNumber;i++)
	{
		scanf("%d",&TrcakSequence[i]);
	}
	
	printf("\nµ±Ç°ŽÅµÀÐòÁÐÊÇ£º\n");
	for(i=0;i<DiskTrackNumber;i++)
	{
		printf("%d ",TrcakSequence[i]);
	}
	count=DiskTrackNumber;
	printf("\n");
	while(1){

	printf("\nÇëÊäÈëÄ£ÄâËã·š·œÊœ£º\n");
	printf("1.ÏÈœøÏÈ³ö£šFIFO£©Ëã·š\n");
	printf("2.×î¶ÌÑ°ÕÒÊ±ŒäÓÅÏÈ£šSSTF£©Ëã·š\n");
	printf("3.ÉšÃè£šSCAN£©Ëã·š\n");
	printf("4.Ñ­»·ÉšÃè£šC-SCAN£©Ëã·š\n");
	printf("5.ÍË³ö\n");
	printf("ÇëÑ¡Ôñ£º");
	scanf("%d",&SerialNumber);
	if(SerialNumber>5)
            break;
        switch(SerialNumber)//Ëã·šÑ¡Ôñ
        {
        case 1:
            FIFO(TrcakSequence,count);//ÏÈœøÏÈ³öËã·š
            printf("\n");
            break;
        case 2:
           SSTF(TrcakSequence,count);//×î¶Ì·þÎñÊ±ŒäÓÅÏÈËã·š
            printf("\n");
            break;
        case 3:
			SCAN(TrcakSequence,count);//ÉšÃèËã·š
            printf("\n");
            break;
        case 4:
          CSCAN(TrcakSequence,count);//Ñ­»·ÉšÃèËã·š
            printf("\n");
            break;
        case 5:
            exit(0);
        }
	}
return 0;
}
