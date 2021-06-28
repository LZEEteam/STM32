#include "usmart_str.h"
#include "usmart.h"
#include "sys.h"
u8 usmart_strcmp(u8 *str1,u8 *str2)
{
	while(1)
	{
		if(*str1!=*str2)return 1;
		if(*str1=='\0')break;
		str1++;
		str2++;
	}
	return 0;
}

void usmart_strcopy(u8*str1,u8 *str2)
{
	while(1)
	{										   
		*str2=*str1;
		if(*str1=='\0')break;
		str1++;
		str2++;
	}
}

u8 usmart_strlen(u8*str)
{
	u8 len=0;
	while(1)
	{							 
		if(*str=='\0')break;
		len++;
		str++;
	}
	return len;
}

u32 usmart_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	    

u8 usmart_str2num(u8*str,u32 *res)
{
	u32 t;
	int tnum;
	u8 bnum=0;
	u8 *p;		  
	u8 hexdec=10;
	u8 flag=0;
	p=str;
	*res=0;
	while(1)
	{
		if((*p<='9'&&*p>='0')||((*str=='-'||*str=='+')&&bnum==0)||(*p<='F'&&*p>='A')||(*p=='X'&&bnum==1))//�����Ϸ�
		{
			if(*p>='A')hexdec=16;
			if(*str=='-'){flag=2;str+=1;}
			else if(*str=='+'){flag=1;str+=1;}
			else bnum++;
		}else if(*p=='\0')break;
		else return 1;
		p++; 
	} 
	p=str;			    //���¶�λ���ַ�����ʼ�ĵ�ַ.
	if(hexdec==16)		//16��������
	{
		if(bnum<3)return 2;			//λ��С��3��ֱ���˳�.��Ϊ0X��ռ��2��,���0X���治������,������ݷǷ�.
		if(*p=='0' && (*(p+1)=='X'))//������'0X'��ͷ.
		{
			p+=2;	//ƫ�Ƶ�������ʼ��ַ.
			bnum-=2;//��ȥƫ����
		}else return 3;//��ʼͷ�ĸ�ʽ����
	}else if(bnum==0)return 4;//λ��Ϊ0��ֱ���˳�.
	while(1)
	{
		if(bnum)bnum--;
		if(*p<='9'&&*p>='0')t=*p-'0';	//�õ����ֵ�ֵ
		else t=*p-'A'+10;				//�õ�A~F��Ӧ��ֵ
		*res+=t*usmart_pow(hexdec,bnum);		   
		p++;
		if(*p=='\0')break;//���ݶ�������.
	}
	if(flag==2)//�Ǹ���?
	{	
		tnum=-*res; 
		*res=tnum;
	}
	return 0;//�ɹ�ת��
}
//�õ�ָ����
//*str:Դ�ַ���
//*cmdname:ָ����
//*nlen:ָ��������
//maxlen:��󳤶�(������,ָ�����̫����)
//����ֵ:0,�ɹ�;����,ʧ��.
u8 usmart_get_cmdname(u8*str,u8*cmdname,u8 *nlen,u8 maxlen)
{
	*nlen=0;
 	while(*str!=' '&&*str!='\0') //�ҵ��ո���߽���������Ϊ������
	{
		*cmdname=*str;
		str++;
		cmdname++;
		(*nlen)++;//ͳ�������
		if(*nlen>=maxlen)return 1;//�����ָ��
	}
	*cmdname='\0';//���������
	return 0;//��������
}
//��ȡ��һ���ַ������м��кܶ�ո��ʱ�򣬴˺���ֱ�Ӻ��Կո��ҵ��ո�֮��ĵ�һ���ַ���
//str:�ַ���ָ��
//����ֵ:��һ���ַ�
u8 usmart_search_nextc(u8* str)
{		   	 	
	str++;
	while(*str==' '&&str!='\0')str++;
	return *str;
} 
//��str�еõ�������
//*str:Դ�ַ���ָ��
//*fname:��ȡ���ĺ�������ָ��
//*pnum:�����Ĳ�������
//*rval:�Ƿ���Ҫ��ʾ����ֵ(0,����Ҫ;1,��Ҫ)
//����ֵ:0,�ɹ�;����,�������.
u8 usmart_get_fname(u8*str,u8*fname,u8 *pnum,u8 *rval)
{
	u8 res;
	u8 fover=0;	  //�������
	u8 *strtemp;
	u8 offset=0;  
	u8 parmnum=0;
	u8 temp=1;
	u8 fpname[6];//void+X+'/0'
	u8 fplcnt=0; //��һ�������ĳ��ȼ�����
	u8 pcnt=0;	 //����������
	u8 nchar;
	//�жϺ����Ƿ��з���ֵ
	strtemp=str;
	while(*strtemp!='\0')//û�н���
	{
		if(*strtemp!=' '&&(pcnt&0X7F)<5)//����¼5���ַ�
		{	
			if(pcnt==0)pcnt|=0X80;//��λ���λ,��ǿ�ʼ���շ���ֵ����
			if(((pcnt&0x7f)==4)&&(*strtemp!='*'))break;//���һ���ַ�,������*
			fpname[pcnt&0x7f]=*strtemp;//��¼�����ķ���ֵ����
			pcnt++;
		}else if(pcnt==0X85)break;
		strtemp++; 
	} 
	if(pcnt)//��������
	{
		fpname[pcnt&0x7f]='\0';//���������
		if(usmart_strcmp(fpname,"void")==0)*rval=0;//����Ҫ����ֵ
		else *rval=1;							   //��Ҫ����ֵ
		pcnt=0;
	} 
	res=0;
	strtemp=str;
	while(*strtemp!='('&&*strtemp!='\0') //�˴����ҵ���������������ʼλ��
	{  
		strtemp++;
		res++;
		if(*strtemp==' '||*strtemp=='*')
		{
			nchar=usmart_search_nextc(strtemp);		//��ȡ��һ���ַ�
			if(nchar!='('&&nchar!='*')offset=res;	//�����ո��*��
		}
	}	 
	strtemp=str;
	if(offset)strtemp+=offset+1;//������������ʼ�ĵط�
	res=0;
	nchar=0;//�Ƿ������ַ�������ı�־,0�������ַ���;1�����ַ���;
	while(1)
	{
		if(*strtemp==0)
		{
			res=USMART_FUNCERR;//��������
			break;
		}else if(*strtemp=='('&&nchar==0)fover++;//�����������һ��
		else if(*strtemp==')'&&nchar==0)
		{
			if(fover)fover--;
			else res=USMART_FUNCERR;//�������,û�յ�'('
			if(fover==0)break;//��ĩβ��,�˳�
		}else if(*strtemp=='"')nchar=!nchar;

		if(fover==0)//��������û������
		{
			if(*strtemp!=' ')//�ո����ں�����
			{
				*fname=*strtemp;//�õ�������
				fname++;
			}
		}else //�Ѿ��������˺�������.
		{
			if(*strtemp==',')
			{
				temp=1;		//ʹ������һ������
				pcnt++;	
			}else if(*strtemp!=' '&&*strtemp!='(')
			{
				if(pcnt==0&&fplcnt<5)		//����һ��������ʱ,Ϊ�˱���ͳ��void���͵Ĳ���,�������ж�.
				{
					fpname[fplcnt]=*strtemp;//��¼��������.
					fplcnt++;
				}
				temp++;	//�õ���Ч����(�ǿո�)
			}
			if(fover==1&&temp==2)
			{
				temp++;		//��ֹ�ظ�����
				parmnum++; 	//��������һ��
			}
		}
		strtemp++; 			
	}   
	if(parmnum==1)//ֻ��1������.
	{
		fpname[fplcnt]='\0';//���������
		if(usmart_strcmp(fpname,"void")==0)parmnum=0;//����Ϊvoid,��ʾû�в���.
	}
	*pnum=parmnum;	//��¼��������
	*fname='\0';	//���������
	return res;		//����ִ�н��
}


//��str�еõ�һ�������Ĳ���
//*str:Դ�ַ���ָ��
//*fparm:�����ַ���ָ��
//*ptype:�������� 0������;1���ַ���;0XFF����������
//����ֵ:0,�Ѿ��޲�����;����,��һ��������ƫ����.
u8 usmart_get_aparm(u8 *str,u8 *fparm,u8 *ptype)
{
	u8 i=0;
	u8 enout=0;
	u8 type=0;//Ĭ��������
	u8 string=0; //���str�Ƿ����ڶ�
	while(1)
	{		    
		if(*str==','&& string==0)enout=1;			//�ݻ������˳�,Ŀ����Ѱ����һ����������ʼ��ַ
		if((*str==')'||*str=='\0')&&string==0)break;//�����˳���ʶ��
		if(type==0)//Ĭ�������ֵ�
		{
			if((*str>='0' && *str<='9')||*str=='-'||*str=='+'||(*str>='a' && *str<='f')||(*str>='A' && *str<='F')||*str=='X'||*str=='x')//���ִ����
			{
				if(enout)break;					//�ҵ�����һ������,ֱ���˳�.
				if(*str>='a')*fparm=*str-0X20;	//Сдת��Ϊ��д
				else *fparm=*str;		   		//Сд�������ֱ��ֲ���
				fparm++;
			}else if(*str=='"')//�ҵ��ַ����Ŀ�ʼ��־
			{
				if(enout)break;//�ҵ�,����ҵ�",��Ϊ������.
				type=1;
				string=1;//�Ǽ�STRING ���ڶ���
			}else if(*str!=' '&&*str!=',')//���ַǷ��ַ�,��������
			{
				type=0XFF;
				break;
			}
		}else//string��
		{ 
			if(*str=='"')string=0;
			if(enout)break;			//�ҵ�����һ������,ֱ���˳�.
			if(string)				//�ַ������ڶ�
			{	
				if(*str=='\\')		//����ת���(������ת���)
				{ 
					str++;			//ƫ�Ƶ�ת���������ַ�,����ʲô�ַ�,ֱ��COPY
					i++;
				}					
				*fparm=*str;		//Сд�������ֱ��ֲ���
				fparm++;
			}	
		}
		i++;//ƫ��������
		str++;
	}
	*fparm='\0';	//���������
	*ptype=type;	//���ز�������
	return i;		//���ز�������
}
//�õ�ָ����������ʼ��ַ
//num:��num������,��Χ0~9.
//����ֵ:�ò�������ʼ��ַ
u8 usmart_get_parmpos(u8 num)
{
	u8 temp=0;
	u8 i;
	for(i=0;i<num;i++)temp+=usmart_dev.plentbl[i];
	return temp;
}
//��str�еõ���������
//str:Դ�ַ���;
//parn:�����Ķ���.0��ʾ�޲��� void����
//����ֵ:0,�ɹ�;����,�������.
u8 usmart_get_fparam(u8*str,u8 *parn)
{	
	u8 i,type;  
	u32 res;
	u8 n=0;
	u8 len;
	u8 tstr[PARM_LEN+1];//�ֽڳ��ȵĻ���,�����Դ��PARM_LEN���ַ����ַ���
	for(i=0;i<MAX_PARM;i++)usmart_dev.plentbl[i]=0;//��ղ������ȱ�
	while(*str!='(')//ƫ�Ƶ�������ʼ�ĵط�
	{
		str++;											    
		if(*str=='\0')return USMART_FUNCERR;//������������
	}
	str++;//ƫ�Ƶ�"("֮��ĵ�һ���ֽ�
	while(1)
	{
		i=usmart_get_aparm(str,tstr,&type);	//�õ���һ������
		str+=i;								//ƫ��
		switch(type)
		{
			case 0:	//����
				if(tstr[0]!='\0')				//���յ��Ĳ�����Ч
				{					    
					i=usmart_str2num(tstr,&res);	//��¼�ò���
					if(i)return USMART_PARMERR;		//��������.
					*(u32*)(usmart_dev.parm+usmart_get_parmpos(n))=res;//��¼ת���ɹ��Ľ��.
					usmart_dev.parmtype&=~(1<<n);	//�������
					usmart_dev.plentbl[n]=4;		//�ò����ĳ���Ϊ4
					n++;							//��������
					if(n>MAX_PARM)return USMART_PARMOVER;//����̫��
				}
				break;
			case 1://�ַ���
				len=usmart_strlen(tstr)+1;	//�����˽�����'\0'
				usmart_strcopy(tstr,&usmart_dev.parm[usmart_get_parmpos(n)]);//����tstr���ݵ�usmart_dev.parm[n]
				usmart_dev.parmtype|=1<<n;	//����ַ���
				usmart_dev.plentbl[n]=len;	//�ò����ĳ���Ϊlen
				n++;
				if(n>MAX_PARM)return USMART_PARMOVER;//����̫��
				break;
			case 0XFF://����
				return USMART_PARMERR;//��������
		}
		if(*str==')'||*str=='\0')break;//�鵽������־��.
	}
	*parn=n;	//��¼�����ĸ���
	return USMART_OK;//��ȷ�õ��˲���
}














