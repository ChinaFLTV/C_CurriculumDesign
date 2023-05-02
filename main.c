#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "StringUtils.c"


#define ANTHOR_SIZE 50// 定义作者名字的最大长度
#define ID_SIZE 20// 定义ID的最大长度
#define NAME_SIZE 50// 定义书名的最大长度
#define PUBLISHER_SIZE 50// 定义出版社名称的最大长度
#define PATH "./books.txt"// 定义书籍本地缓存路径
#define LINE_SIZE 200// 定义行的最大长度
#define TEMP_PATH "./temp.txt"// 定义删除时的临时文件存放路径
#define MAX_STORAGE_COUNT 100// 定义最大存储书籍的条数


// 定义图书结构体指针
typedef struct Book* bookPointer;
// 定义图书结构体
typedef struct Book{

    int id;// 图书编号
    char author[ANTHOR_SIZE];// 作者
    char name[NAME_SIZE];//书名
    char publisher[PUBLISHER_SIZE];//出版社

}book;


// 打印指定Book对象的信息
void printBook(bookPointer bp){

    if(bp==NULL){

        printf("呵呵，Book指针为空~、\n");
        return;

    }
    printf("id = %d , anthor = %s , name = %s , publisher = %s\n",bp->id,bp->author,bp->name,bp->publisher);

}


// 添加一条图书数据
// 返回1则表示添加成功，返回0则表示添加失败
int addBook(){

    char id_str[ID_SIZE];
    bookPointer bp = (bookPointer)malloc(sizeof(book));
    if(bp==NULL){

        printf("addBook : 开辟内存失败\n");
        return 0;

    }
    
    printf("====>请填写你要添加的图书的作者：\n");
    fgets(bp->author,ANTHOR_SIZE,stdin);
    replace(bp->author,'\n','\0');
    
    printf("====>请填写你要添加的图书的图书编号：\n");
    fgets(id_str,ID_SIZE,stdin);

    while((bp->id = atoi(id_str)) == 0){

        printf("====>图书编号非法，请重新输入编号！\n");
        fgets(id_str,ID_SIZE,stdin);

    }
    printf("====>请填写你要添加的图书的图书名称：\n");
    fgets(bp->name,NAME_SIZE,stdin);
    replace(bp->name,'\n','\0');


    printf("====>请填写你要添加的图书的出版社：\n");
    fgets(bp->publisher,PUBLISHER_SIZE,stdin);
    replace(bp->publisher,'\n','\0');

    printf("====>添加成功！新插入的书籍信息为:\n");
    printBook(bp);

    // 本地缓存输入的数据数据
    char book_str[LINE_SIZE];
    sprintf(book_str, "%d\t%s\t%s\t%s\n",bp->id,bp->author,bp->name,bp->publisher);
    appendString(book_str,PATH);
    return 1;

}


// 删除指定编号的图书
void deleteBook(){

    int id;
    char buffer[ID_SIZE],buffer1[LINE_SIZE];
    FILE* old_fp;
    FILE* new_fp;
    char* line;
    int current_id;
    char current_author[ANTHOR_SIZE],current_name[NAME_SIZE],current_publisher[PUBLISHER_SIZE];
    int find = 0;
    printf("====>请输入准备删除的书籍的编号:\n");
    while((id = atoi(fgets(buffer,ID_SIZE, stdin)))==0){

        printf("图书编号非法，请重新输入:\n");

    }
    old_fp = fopen(PATH, "r");
    new_fp = fopen(TEMP_PATH, "w+");

    while ((line=fgets(buffer1,LINE_SIZE,old_fp))!=NULL) {
    
        sscanf(line,"%d\t%s\t%s\t%s\n", &current_id,current_author,current_name,current_publisher);
        if(current_id!=id){

            fputs(line, new_fp);

        }else{

            find = 1;

        }

    }
    
    if(find==0){

        printf("没有此编号下的书籍\n");
        remove(TEMP_PATH);

    }else{

        printf("删除成功！\n");
        remove(PATH);
        rename(TEMP_PATH, PATH);

    }

    fclose(old_fp);
    fclose(new_fp);

}


// 查找指定编号的书籍信息
void searchBook(){

    int id;
    FILE* fp;
    char buffer[LINE_SIZE];
    char* line;
    bookPointer bp = (bookPointer)malloc(sizeof(book));
    int find = 0;
    printf("====>请输入准备查看的书籍的编号:\n");
    scanf("%d",&id);
    fp = fopen(PATH, "r");

    while((line = fgets(buffer, LINE_SIZE, fp))!=NULL){

        sscanf(line,"%d\t%s\t%s\t%s\n", &bp->id,bp->author,bp->name,bp->publisher);
        if(bp->id == id){

            find = 1;
            printf("查询到目标编号的书籍：\n");
            printBook(bp);
            break;

        }

    }
    if(find==0){

        printf("未查询到指定编号的书籍\n");

    }

    fclose(fp);

}


// 根据编号大小进行排序并将结果进行输出
void sortBooks(){

    int mode,m,n,flag;
    FILE* fp;
    char buffer[LINE_SIZE];
    char* line;
    bookPointer temp;
    bookPointer bps[MAX_STORAGE_COUNT];
    int count;
    int index = 0;
    printf("即将对当前书籍进行按编号大小排序：\n");
    printf("1.升序  |  2.降序\n");
    scanf("%d",&mode);
    while((mode!=1)&&(mode!=2)){

        printf("排序模式非法，请重新输入:\n");
        fgets(buffer, LINE_SIZE, stdin);
        mode = atoi(buffer);

    }

    // 将本地数据缓存中的每一行数据映射为一个Book实体并存入数组中
    //fclose(fp);
    fp = fopen(PATH, "r");
    while((line = fgets(buffer, LINE_SIZE, fp))!=NULL){

        bps[index] = (bookPointer)malloc(sizeof(book));
        sscanf(line,"%d\t%s\t%s\t%s\n", &bps[index]->id,bps[index]->author,bps[index]->name,bps[index]->publisher);
        index++;

    }

    // 计算出总的书籍数据数量
    count = index+1;

    // 冒泡排序
    for (m = 0; m<MAX_STORAGE_COUNT-2; m++) {
    
        if(flag ==1){

            flag = 0;
            for (n = m+1; n<MAX_STORAGE_COUNT-1; n++) {
        
                if((bps[m-1]->id)>(bps[m]->id)){

                    flag = 1;
                    temp = bps[m-1];
                    bps[m-1] = bps[m];
                    bps[m] = temp;

                }

            }

        }else if(flag == 0){

            break;

        }

    }
    
    if(mode==1){

        index = 0;
        while(bps[index]!=NULL){

            printBook(bps[index]);
            index++;

        }        

    }else if(mode == 2){

        for(index = count-1;index>=0;index--){

            printBook(bps[index]);

        }

    }

    fclose(fp);

}


int main(void) {

    printf("===============图书资料管理系统==============\n");
    //addBook();
    //deleteBook();
    //searchBook();
    sortBooks();
    return 0;

}