#include<string.h>
#include<stdio.h>

// 用于替换字符串中某个字符为新的指定字符
void replace(char * str,char oldChar,char newChar){

    int i,count;
    if(str==NULL){

        printf("replace ：将要替换的目标字符串为空！\n");
        return;

    }

    for (i = 0; str[i]!='\0'; i++) {
    
        if(str[i] == oldChar){

            str[i] = newChar;
            count++;

        }
    
    }

    printf("replace : 替换完成，共替换了 %d 个 %c 为 %c\n",count,oldChar,newChar);

}

// 将目标字符串写入目标路径上的文件中
void appendString(char* str,char* path){

    if((str!=NULL)&&(path!=NULL)){

        FILE* fp;
        fp = fopen(path, "a+");
        fputs(str, fp);
        //fputs("\n", fp);// 换行
        fclose(fp);
        printf("appendString : 追加 %s 到 %s 上的文件成功\n",str,path);

    }else{

        printf("appendString : 呵呵，部分参数违法~、\n");

    }
    
}

// 将整形转换为字符串
char* int2String(int i){

    char* buffer = (char*)malloc(sizeof(int));
    //char buffer[4];
    sprintf(buffer, "%d", i);
    printf("int2String : 转换 %d 为字符串完毕\n",i);
    return buffer;

}
