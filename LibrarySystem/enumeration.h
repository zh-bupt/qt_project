/***************************
 * 所有枚举类型的头文件
 * 包含读者类型，读者所属院系以及书籍类别
 * created by zh
****************************/
#ifndef ENUMERATION_H
#define ENUMERATION_H

//读者类型：本科在校生，研究生，博士生，老师，教授
enum TYPE{
        UNDERGRADUATE,MASTER,DOCTER,TEACHER,PROFESSOR
    };

//读者院系：计科，信通，人文，树莓，经管，网工，信安
enum ACADEMY{
        JIKE,XINTONG,RENWEN,SHUMEI,JINGGUAN,WANGGONG,XINAN
    };

//todo:图书类别枚举类型
enum CATEGORY{
    WENXUELISHI,ZHENGFAJINGJI,JUNSHI,YISHU,SHULIKEXUE,ZIRANKEXUE,GONGYEJISHU,ZAZHI,BAOZHI,MANHUA,QITA
};

#endif // ENUMERATION_H
