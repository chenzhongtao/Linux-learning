/*
 * =====================================================================================
 *
 *       Filename:  base64.c
 *
 *    Description:  实现base64 编码和解码
 *
 * =====================================================================================
 */

/* *
 * base64是一种基于64个可打印字符来表示二进制数据的表示方法
 *   编码能够把任意二进制数据编码为可见的字符串
 *   常用于信息的交互
 * 因为2**6=64, 所以每6bit就可以对应一个字符表中的字符，
 *    由于3个原始数据字节可以用4个base64字符表示 3*8 = 4*6 = 24
 *
EE 标准base64 字符集
static const unsigned char base64_alphabet[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', 
	'4', '5', '6', '7', '8', '9', '+', '/'
};

EE base64 字符集有多种变形
EE base64 URL 字符集
   因为URL编码器会把 base64中的 '+' '/' 字符转换为 %XX 的形式
   所以有一种用于URL的base64 变形标准， 该标准中把原始base64字符
   集中的 '+' '/' 分别改为'*','-'

EE base64 编码规则
    Base64要求把每三个8Bit的字节转换为四个6Bit的字节（3*8 = 4*6 = 24），
    然后把每个6Bit再添两位高位0，组成四个8Bit的字节，
    也就是说，转换后的字符串理论上将要比原来的长1/3。
      3B -> 4B = 3B + 1
    最后的数据如果不够3B用0补足3B，在转换, 
    如果最後剩下兩個輸入數據，在編碼結果後加1個「=」；
    如果最後剩下一個輸入數據，編碼結果後加2個「=」；
    如果沒有剩下任何數據，就什麼都不要加，這樣才可以保證資料還原的正確性

    2.每产生76个转换后的字符加一个\r\n

**/


#include <stdio.h>
#include <stdint.h>
#include <string.h>

static const unsigned char base64_alphabet[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', 
	'4', '5', '6', '7', '8', '9', '+', '/'
};


/*  |    data[0]    |  data[1]      |   data[2]     |
    +---------------|---------------|---------------+
    |7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|
    +-----------|-----------|-----------|-----------+
    |  cv[0] 6  |   cv[1] 12|  cv[2]  18|  cv[3]    |
*/


//@return: 编码后的dst长度
int encode_to_base64(char *dst, const uint8_t *src, size_t len)
{
    char *d = dst;
    const uint8_t *s = src;
    
        //X321 从高位到地位 -> datas
    for (; len >= 3; len-=3) {
        *(d++) = base64_alphabet[(s[0] >> 2) & 0x3F];
        *(d++) = base64_alphabet[((s[0] & 0x3) << 4) | (s[1] >> 4)];
        *(d++) = base64_alphabet[((s[1] & 0xF) << 2) | (s[2] >> 6)];
        *(d++) = base64_alphabet[s[2] & 0x3F];
        s+=3;
    }

    //不够3个B，差一个B时 把转换后的最后一个4元组字符的组后一个字符变为=
    //  e.g.[X,X,X=]
    //  差两个B时 把转换后的最后一个4元组字符的组后两个字符变为=
    //  e.g.[X,X,=,=]

    if (len) {
        *(d++) = base64_alphabet[(s[0] >> 2) & 0x3F];
        if (len == 1) {
          *(d++) = base64_alphabet[(s[0] & 0x3) << 4];
          *d++ = '=';
        } else { //len == 2
            *(d++) = base64_alphabet[((s[0] & 0x3) << 4) | (s[1] >> 4)];
            *(d++) = base64_alphabet[(s[1] & 0xF) << 2];
        }
        *d++ = '=';
    }

    return d - dst;
}


int main() {
  char buf[64];
  char *str="hello";
  int i = encode_to_base64(buf, (uint8_t*)str, strlen(str));
  buf[i] ='\0';
  printf("len=%d str=%s\n", i, buf);
  return 0;

}


//EE decode 解码 ??