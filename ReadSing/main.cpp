#include <stdio.h>

int main()//歌曲分析部分
{
    FILE *fpr,*fpw;
    int y,i,j,n=0,f=0;
    int a[12][12]={0};
    float p[12][12]={0};
    char s[1000],note[13]="BC#D#EF#G#A#";
    if((fpr=fopen("src_note.txt","r"))!=NULL)
    {
        fscanf(fpr,"%d",&n);
        for(i=0;i<12;i++)
        {
            for(j=0;j<12;j++)
            {fscanf(fpr,"%d",&a[i][j]);}
        }
        fclose(fpr);
    }
    fpr=fopen("a.nn","r");//准备分析袅袅文件
    fgets(s,1000,fpr);
    fgets(s,1000,fpr);
	
    for(i=0;i<4;i++)
    {fscanf(fpr,"%s",s);}
    fscanf(fpr,"%d",&y);
	
    y=(48-y)%12;
    for(i=0;i<9;i++)
    {fscanf(fpr,"%s",s);}

	int x;
    while(1)
    {
        x=y;
		//接着开始循环读
        for(i=0;i<4;i++)
        {
			if(fscanf(fpr,"%s",s)==EOF)
				f=1;
		}
        fscanf(fpr,"%d",&y);
        y=(48-y)%12;
        for(i=0;i<9;i++)
        {
            if(fscanf(fpr,"%s",s)==EOF)
				f=1;
        }
        a[x][y]++;
        n++;
        if(f==1)//读完了就退
			break;
        printf("音符统计：第%d个数据\n",n);//输出这段的分析结果
        printf("\tB\tC\t#\tD\t#\tE\tF\t#\tG\t#\tA\t#\n");
        for(i=0;i<12;i++)
        {
            printf("%c\t",note[i]);
            for(j=0;j<12;j++)
            {
                p[i][j]=1.0*a[i][j]/n;
                printf("%.4f\t",p[i][j]);

            }
            printf("\n");
        }
    }
	
    fclose(fpr);
    fpw=fopen("src_note.txt","w");//一个记录作用？关键是写不是前面的读
    fprintf(fpw,"%d\n",n);//先写入之前读的次数
    for(i=0;i<12;i++)//再循环把之前统计的写一下
    {
        for(j=0;j<12;j++)
        {fprintf(fpw,"%d\t",a[i][j]);}
        fprintf(fpw,"\n");
    }
    fclose(fpw);
    fpw=fopen("note.txt","w");//再次准备写，它在note_p中被用到
	int d;
    for(i=0;i<12;i++)
    {
        d=0;
        for(j=0;j<12;j++)
        {
            d+=a[i][j];
        }
        for(j=0;j<12;j++)
        {
            if(note[i]!='#' && note[j]!='#')
            {
				//对给src_note写的a又进行了进一步处理出p，再写到note里，最后用的是这个
                p[i][j]=1.0*a[i][j]/d;
                if(d==0)p[i][j]=0;
                fprintf(fpw,"%.4f\t",p[i][j]);
            }
        }
        if(note[i]!='#' && note[j]!='#')
			fprintf(fpw,"\n");
    }
    fclose(fpw);
}
