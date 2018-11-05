//integer 无符号整形数，str 转换后的字符数组
void WordToStr(unsigned int integer,unsigned char num);
//10个数去掉最大最小值，求平均
unsigned char Average(unsigned char* str); 
/*==============================================
两个无符号整数比较大小,最前面有1，则“代表”负数
     返回值               意义
	   0                  相等
	   1                  前者大
	   2                  后者大
===============================================*/
unsigned char Compare(unsigned int first,unsigned int second);
 