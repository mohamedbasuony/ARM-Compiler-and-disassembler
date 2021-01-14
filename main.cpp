#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <iostream>
#include <fstream>  
using namespace std;
unsigned char buffer[8 * 1024]; // Buffer to hold the machine code

int simulate(unsigned short);
 int j = 825;
unsigned char  Mem[1024];
unsigned int bits[32]={0};

unsigned int Regs[16];
   // initially sp=0; means that it points to the first byte in Mem array
int sp=-1;

#define PC Regs[15]
#define LR Regs[14]
int i=1;

//---------------------main---------------------//
//-- we used the way we used in project 1 just to make the fetching process dependent on PC
int main(int argc, char *argv[])
{

	unsigned int inst_word = 0;
	ifstream inFile;
	ofstream outFile;


	if(argc<1) cout<<"use: disasm <machine_code_file_name>\n";

	inFile.open(argv[1], ios::in | ios::binary | ios::ate);

	if (inFile.is_open())
	{
		int fsize = inFile.tellg(); //size

		inFile.seekg(0, inFile.beg); //begin of the file
		if(!inFile.read((char *)buffer, fsize)) cout<<"Cannot read from input file\n";
		int i = 0;
		while (true)
		{
			
			inst_word = (unsigned char)buffer[PC] |
					   (((unsigned char)buffer[PC + 1]) << 8) ;
					   

			// remove the following line once you have a complete disassembler
			// if(pc==32) break;			// stop when PC reached address 32
			
			if ((fsize / 2)  +1== i)
				break;
                i++;
  printf("%08x\t%04x\t", PC, inst_word);
  //if (inst_word==0xdead) {cout<<"\n";return 0;}
			simulate(inst_word);
			PC += 2;  //go to the next instruction.
		}
	}
	else
		 cout<<"Cannot access input file\n";
// int main()
// {
// for(int i=0; i<1024;i++)
// Mem[i]=0;
// for(int i=0; i<16;i++)
// Regs[i]=0;
//     FILE *fp;
//     unsigned short inst_word;

//     fp = fopen("sum.bin", "rb");
// // int fsize = fp.tell(); //size
//     if (NULL == fp)
//     {
//         printf("Cannot open the file\n");
//         exit(0);
//     }
// while (true)
// 		{
			
// 			inst_word = (unsigned short)fp[PC] |
// 					   ((unsigned short)fp[PC + 1]) << 8) ;
					   

			
			
// 			if (0x70 == PC)
// 				break;

//         printf("%08x\t%04x\t", PC, inst_word);
//         simulate(inst_word);
//         PC += 2;
//     }
//     fclose(fp);
//     return 0;
}
//-------------------------------------------------------------------------------/

//helping functions.
 void printRlist(unsigned int list, bool flag, unsigned int Regs[16], unsigned char Mem[1024]){
   
    for (int i=0;i<8;i++){
        int x=0;int y=0;
        if ((list&1)==1){
        printf("R%d,",i);
        if (flag==false){ // this is to push
             x= Regs[i];
            Mem[sp]= x&0xFF;
            // Mem[sp+1]=(x>>8)&0xFF;
            // Mem[sp+2]=(x>>16)&0xFF;
            // Mem[sp+3]=(x>>24)&0xFF;
            sp=sp+1;
            Regs[13]=sp;    
        }
        else if (flag==true){ // this is to pop out of the stack
                  
             //x= Mem[sp+3]+Mem[sp+2]+Mem[sp+1]+Mem[sp];
           x=Mem[sp];
             Regs[i]=x;
            
             sp=sp-1;       
             Regs[13]=sp;    
        }

        
        }
        list= list>>1;
    }
  printf("\b");
}
int z=0;
void pushorpoplr(unsigned int list, bool flag, unsigned int Regs[16], unsigned char Mem[1024]){
int x=0;int y=0;
if (flag==false){ // this is to push
            // x= Regs[14];
            // Mem[sp]= x&0xFF;
            // Mem[sp+1]=(x>>8)&0xFF;
            // Mem[sp+2]=(x>>16)&0xFF;
            // Mem[sp+3]=(x>>24)&0xFF;
            // sp=sp+4;
            z=PC-6;
            // Regs[13]=sp;     
        }
        else if (flag==true){ // this is to pop out of the stack
                  
            // x= Mem[sp+3]+Mem[sp+2]+Mem[sp+1]+Mem[sp];
           
            // Regs[15]=x;
            
            // sp=sp-4;       
            // Regs[13]=sp; 
            //Regs[15]=z; 
        }

}

int rightRotate(int n, unsigned int d) 
{ 
    /* In n>>d, first d bits are 0.  
    To put last 3 bits of at  
    first, do bitwise or of n>>d 
    with n <<(INT_BITS - d) */
    return (n >> d)|(n << (32 - d)); 
} 

bool isEmpty(int x){
    if (x<0)
    return true;
    else 
    return false;
}

bool isFull(int x){
    if (x>=1023)
    return true;
    else 
    return false;
}

int simulate(unsigned short instr)
{
    int memindex=0;
  
    unsigned char  fmt, op, rd, rs, offset3, rn;
    unsigned int  offset8, f, ro, rb, bit9, L, B, word8,S, sword7,offset, R,Rlist, det,det2, source,t,decide, H,detect,cond,bit12;
signed int  offset5; int tempm;
if ((offset5 >> 4) == 1)
	{
		int temp = 0x7FFFFFF;
		temp = temp << 5;
		offset5 = offset5 + temp;
	}

    fmt = (instr) >> 13;

    switch (fmt)
    {
    case 0: // format 1/2
        op = (instr >> 11) & 3;
        rd = instr & 7;
        rs = (instr >> 3) & 7;
        offset5 = (instr >> 6) & 0x1F;
        int temp;
        if (op != 3)
        { // format 1

            switch (op)
            {
            case 0:
                printf("lsl\tr%d, r%d, #%d", rd, rs, offset5);
                 Regs[rd] = Regs[rs] <<offset5;
                 printf("\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 1:
                printf("lsr\tr%d, r%d, #%d", rd, rs, offset5);
                
                Regs[rd] = Regs[rs] >>offset5;
                printf("\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 2:
                printf("asr\tr%d, r%d, #%d", rd, rs, offset5);
                //needs handling for 1's
                /* temp=Regs[rs];
                Regs[rd] =temp >>offset5; */
                Regs[rd] = Regs[rs] >>offset5;
               printf("\tr%d = %d\n",rd, Regs[rd] );
                break;
            }

        }
        else
        { /*add/sub*/

            offset3 = rn = offset5 & 0x07;
            if ((offset5 & 0x08) == 0)
            {
                printf("add\tr%d, r%d, ", rd, rs);
                if ((offset5 & 0x10) == 0)
                {
                    printf("r%d", rn);
                    Regs[rd] = Regs[rs] + Regs[rn];
                      printf("\tr%d = %d\n",rd, Regs[rd] );
                }
                else
                {
                    printf("#%d", offset3);
                    Regs[rd] = Regs[rs] + offset3;
                        printf("\tr%d = %d\n",rd, Regs[rd] );
                }
            }
            else
            {
                printf("sub\tr%d, r%d, ", rd, rs);
                if ((offset5 & 0x10) == 0)
                {
                    printf("r%d", rn);
                    Regs[rd] = Regs[rs] - Regs[rn];
                       printf("\tr%d = %d\n",rd, Regs[rd] );
                }
                else
                {
                    printf("#%d", offset3);
                    Regs[rd] = Regs[rs] - offset3;
                      printf("\tr%d = %d\n",rd, Regs[rd] );
                }
            }
        }
        //--------------------------------------------------------Andrew---------------------------------------------------//
        break;
    case 1: // format 3
        op = (instr >> 11) & 3;
        rd = (instr >> 8) & 7;

        offset8 = (instr)&0xFF;

        switch (op)
        {
        case 0:
            printf("mov\tr%d, #%d", rd, offset8);
            Regs[rd] = offset8;
             printf("\tr%d = %d\n",rd, Regs[rd] );
            break;
        case 1:
            printf("cmp\tr%d, #%d\n", rd, offset8);
            if((Regs[rd] ==offset8)){
                bits[29]=1;
                bits[30]=1;}
          else   if((Regs[rd] <Regs[rs]))
            bits[31]=1;
           else     if((Regs[rd] >Regs[rs]))
            bits[29]=1;
            break;
        case 2:
            printf("add\tr%d, #%d", rd, offset8);
            Regs[rd] = Regs[rd] + offset8;
              printf("\tr%d = %d\n",rd, Regs[rd] );
            break;
        case 3:
            printf("sub\tr%d, #%d", rd, offset8);
            Regs[rd] = Regs[rd] - offset8;
         printf("\tr%d = %d\n",rd, Regs[rd] );
            break;
        }

        break;
        //---------------------------------------------------------//
    case 2: // format 4/5/6/7
        op = (instr >> 6) & 15;
        rd = instr & 7;
        rs = (instr >> 3) & 7;
        f = (instr >> 10) & 7;
        if (f == 0)
        //-----------------------------------------------------------//
        { // format 4

            switch (op)
            {
            case 0:
                printf("and\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] & Regs[rs];
                    printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 1:
                printf("eor\tr%d, r%d\t", rd, rs);
                Regs[rd] = Regs[rd] ^ Regs[rs];
                printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 2:
                printf("lsl\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] << Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 3:
                printf("lsr\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] >> Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 4:
                printf("asr\tr%d, r%d", rd, rs);
                 /* tempm=Regs[rd];
                Regs[rd] = tempm >> Regs[rs]; */
                Regs[rd] = Regs[rd] >> Regs[rs]; //shoud benarthimatic and what i did is not arthimatic
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 5:
            //c
                printf("adc\tr%d, r%d", rd, rs);   
               if((Regs[rd] ==Regs[rs])){
                bits[29]=1;
                bits[30]=1;}
          else   if((Regs[rd] <Regs[rs]))
            bits[31]=1;
           else     if((Regs[rd] >Regs[rs]))
            bits[29]=1;
                Regs[rd] = Regs[rd] + Regs[rs] +bits[29];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 6:
            //c
           if((Regs[rd] ==Regs[rs])){
                bits[29]=1;
                bits[30]=1;}
          else   if((Regs[rd] <Regs[rs]))
            bits[31]=1;
           else     if((Regs[rd] >Regs[rs]))
            bits[29]=1;

                printf("sbc\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] - Regs[rs]-!bits[29];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 7:
                printf("ror\tr%d, r%d\t", rd, rs);
                Regs[rd]=rightRotate(Regs[rd],Regs[rs]);
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                // Regs[rd] = Regs[rd]  /*Ror*/  Regs[rs]

                break;
            case 8:
                printf("tst\tr%d, r%d\n", rd, rs);
                //set conditions
                  if((Regs[rd] =Regs[rs])){
                bits[29]=1;
                bits[30]=1;}
          else   if((Regs[rd] <Regs[rs]))
            bits[31]=1;
           else     if((Regs[rd] <Regs[rs]))
            bits[29]=1;
                break;
            case 9:
                printf("neg\tr%d, r%d", rd, rs);
                Regs[rd] = -Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 10:
                printf("cmp\tr%d, r%d\n", rd, rs);
                //set conditions
                if((Regs[rd] =Regs[rs])){
                bits[29]=1;
                bits[30]=1;}
          else   if((Regs[rd] <Regs[rs]))
            bits[31]=1;
           else     if((Regs[rd] <Regs[rs]))
            bits[29]=1;
                break;
            case 11:
                printf("cmn\tr%d, r%d\n", rd, rs);
                //set conditions
                if((Regs[rd] =Regs[rs]))
                bits[29]=1;
                bits[30]=1;
            if((Regs[rd] <Regs[rs]))
            bits[31]=1;
               if((Regs[rd] <Regs[rs]))
            bits[29]=1;
                break;
            case 12:
                printf("orrs\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] | Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 13:
                printf("mul\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] * Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 14:
                printf("bic\tr%d, r%d", rd, rs);
                Regs[rd] = Regs[rd] & !Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            case 15:
                printf("mvn\tr%d, r%d", rd, rs);
                Regs[rd] = !Regs[rs];
                 printf("\t\tr%d = %d\n",rd, Regs[rd] );
                break;
            }
        }
        else if (f == 1)
        
        { //-------------------------------------format 5-------------------------------//
        //doesnot requried
            switch (op >> 2)
            {
            case 0:

                if ((op & 0x1) == 1)
                {
                    printf("add\tr%d, r%d\n", rd, rs);
                    if ((op >> 1 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] + Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] + offset3;
                    }
                }
                else
                {
                    printf("add\tr%d, r%d\n", rd, rs);
                    if ((offset5 & 0x1) == 0)
                    {

                        //               Regs[rd] = Regs[rs] - Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] - offset3;
                    }
                }

                break;
            case 1:

                if ((op & 0x1) == 1)
                {
                    printf("cmp\tr%d, r%d\n", rd, rs);
                    if ((op >> 1 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] + Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] + offset3;
                    }
                }
                else
                {
                    printf("cmp\tr%d, r%d\n", rd, rs);
                    if ((offset5 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] - Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] - offset3;
                    }
                }
                break;

            case 2:

                if ((op & 0x1) == 1)
                {
                    printf("mov\tr%d, r%d\n", rd, rs);
                    if ((op >> 1 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] + Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] + offset3;
                    }
                }
                else
                {
                    printf("mov\tr%d, r%d\n", rd, rs);
                    if ((offset5 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] - Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] - offset3;
                    }
                }
                break;
            case 3:

                if ((op & 0x1) == 1)
                {
                    printf("bx\tr%d, r%d\n", rd, rs);
                    if ((op >> 1 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] + Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] + offset3;
                    }
                }
                else
                {
                    printf("bx\tr%d, r%d\n", rd, rs);
                    if ((offset5 & 0x1) == 0)
                    {

                        //                                 Regs[rd] = Regs[rs] - Regs[rn];
                    }
                    else
                    {

                        //                                 Regs[rd] = Regs[rs] - offset3;
                    }
                }
            }
        }
        //-------------format 6-------------//
        else if (f >> 1 == 1)
        {
            rd = (instr >> 8) & 7;
            offset8 = (instr)&0xFF;
            printf("ldr\tr%d, [ PC, %d ]", rd,offset8);
            //word
            if (PC+offset8<1024)
              Regs[rd] =Mem[PC+offset8];
                   printf("\tr%d = %d\n",rd, Regs[rd] );

            
        }
        //-------------format 7 &8-------------//
        else if (f >> 2 == 1)
        {
            rd = instr & 7;
            rb = (instr >> 3) & 7;
            ro = (instr >> 6) & 7;
            bit9 = (instr >> 9) & 1;
            B = (instr >> 10) & 1;
            L = (instr >> 11) & 1;
            if (bit9 == 0)
            {//formate 7
                switch (L)
                {
                case 0:
                    if (B == 0){
                        printf("str\tr%d, [ r%d, r%d ]", rd, rb, ro);
                        //think that this is storing bytes so need to make for loop??
        if( Regs[rb]+Regs[ro]<1024){
                    /* for(int s=0;s<4;s++)
                          Mem[Regs[rb]+Regs[ro]+s] =(Regs[rd]&0xFF)>>8*s; */
                          Mem[Regs[rb]+Regs[ro]] =Regs[rd]; //maco
                   printf("\tr%d = %d\n",rd, Mem[Regs[rb]+Regs[ro]] );}else cout<<"\n";}
                    else{
                        printf("strb\tr%d, [ r%d, r%d ]", rd, rb, ro);
                        //storing byte
                        if( Regs[rb]+ro<1024){
                       Mem[Regs[rb]+Regs[ro]] =Regs[rd];
                   printf("\tr%d = %d\n",rd, Mem[Regs[rb]+Regs[ro]] );}else cout<<"\n";}

                    break;

                case 1:
                    if (B == 0){
                        printf("ldr\tr%d, [ r%d, r%d ]", rd, rb, ro);
                        //storing word
                          if( Regs[rb]+offset5<1024){
                         /* Regs[rd] =(Mem[Regs[rb]+Regs[ro]]&0xFF) 
                         | 
                                   (Mem[Regs[rb]+Regs[ro]+1]&0xFF)<<8    |    
                                   ( Mem[Regs[rb]+Regs[ro]+2] &0xFF)<<16       |
                                    (Mem[Regs[rb]+Regs[ro]+3]&0xFF)<<24 ; */
                             Regs[rd]=Mem[Regs[rb]+Regs[ro]]; //maco
                   printf("\tr%d = %d\n",rd, Regs[rd] );}else cout<<"\n";}
                    else{
                        printf("ldrb\tr%d, [ r%d, r%d ]", rd, rb, ro);
                        //storing byte
                        if( Regs[rb]+ro<1024){
                        Regs[rd]=Mem[Regs[rb]+Regs[ro]];
                   printf("\tr%d = %d\n",rd, Regs[rd] );}else cout<<"\n";}
                    break;
                }
            }
            else
            {//format 8
            ///not required
                switch (L)
                {
                case 0:
                    if (B == 0)
                        printf("strh\tr%d, [ r%d, r%d ]\n", rd, rb, ro);
                    else
                        printf("ldrh\tr%d, [ r%d, r%d ]\n", rd, rb, ro);

                    break;

                case 1:
                    if (B == 0)
                        printf("ldsb\tr%d, [ r%d, r%d ]\n", rd, rb, ro);
                    else
                        printf("ldsh\tr%d, [ r%d, r%d ]\n", rd, rb, ro);
                    break;
                }
            }
        }
        break;
        ///////////////////---------------format 9-----------//
case 3:
rd = instr & 7;
            rb = (instr >> 3) & 7;
            offset5 = (instr >> 6) & 0x1F;
            //bit9 = (instr >> 9) & 1;
            L= (instr >> 11) & 1;
            B = (instr >> 12) & 1;
            switch (L)
                {
                case 0:
                    if (B == 0){
                        printf("str\tr%d, [ r%d, r%d ]", rd, rb, offset5);
                        // //storing word
                          if( Regs[rb]+offset5<1024){
                        /* for(int s=0;s<4;s++)
                         Mem[Regs[rb]+offset5+s] =(Regs[rd]&0xFF)>>8*s; */

                    Mem[Regs[rb]+offset5] =Regs[rd]; //maco
                         
                   printf("\tr%d = %d\n",rd,  Mem[Regs[rb]+offset5] );}
                   else cout<<"\n";}
                    else{
                        printf("strb\tr%d, [ r%d, r%d ]", rd, rb, offset5);
                         //storing byte
                          if( Regs[rb]+offset5<1024){
                          Mem[Regs[rb]+offset5] =Regs[rd];
                    
                   printf("\tr%d = %d\n",rd,  Mem[Regs[rb]+offset5] );}else cout<<"\n";}

                    break;

                case 1:
                    if (B == 0){
                        printf("ldr\tr%d, [ r%d, r%d ]", rd, rb, offset5);
   if( Regs[rb]+offset5<1024){
                      Regs[rd] =(Mem[Regs[rb]+offset5]&0xFF) ; //maco
                      /* | 
                                 ((Mem[Regs[rb]+offset5+1]&0xFF)<<8 )
                    |    
                                   ( Mem[Regs[rb]+offset5+2] &0xFF)<<16    
                                    |
                                    (Mem[Regs[rb]+offset5]+3&0xFF)<<24 ; */
                   
                   printf("\tr%d = %d\n",rd, Regs[rd] );}else cout<<"\n";
                   }
                    else{
                        printf("ldrb\tr%d, [ r%d, r%d ]", rd, rb, offset5);
                           if( Regs[rb]+offset5<1024){
                          Regs[rd]=Mem[Regs[rb]+offset5]; 
                   printf("\tr%d = %d\n",rd, Regs[rd] );}else cout<<"\n";}
                    break;
                }
                break;
      //----------------------end of Andrew---------------------------------------//
//---------------------------------Mahmoud----------------------------------//
      case 4:    //format 10,11
        
      L=(instr>>11)&1;
       det=(instr>>12)&1; //detect whether it is 10 or 11
      switch (det){
          case 0: //format 10
          rd= instr &7;
          rb= (instr>>3)&7;
          offset5=(instr>>6)&31;
         
          if (((offset5>>4)&1)==1){
              offset5=(offset5|0xFFFFFFE0);  //sign extend if the number happens to be negative
          }

      if (L==0){
          // memindex=offset5+ Regs[rb];
           //Mem[memindex]= Regs[rd]&0xFFFF;
            printf("strh\tr%d, [r%d,#%d]\n",rd,rb,offset5);
           //printf("R%d= 0x%X\n",rd, Regs[rd]);
            
            }

      else {
            /* memindex=offset5+ Regs[rb];
            if(memindex<1024)
            Regs[rd]=Mem[memindex]&0xFFFF; */
            //Regs[rd]=memindex &0xFFFF;
            printf("ldrh\tr%d, [r%d,#%d]\n",rd,rb,offset5);
            //printf("R%d= 0x%X\n",rd, Regs[rd]);
            }
              break;

            case 1:
            word8= instr&255;
            rd= (instr>>8)&7;
           if (L==0){
            /* memindex=word8+ Regs[13];
            Mem[memindex]= Regs[rd]; */
            printf("str\tr%d, [sp,#%d]\n",rd ,word8);
            //printf("R%d= 0x%X\n",rd, Regs[rd]);
           }
            else{
            /* memindex=word8+ Regs[13];
            Regs[rd]=Mem[memindex]; */
            //Regs[rd]=memindex;
            printf("ldr\tr%d, [sp,#%d]\n",rd ,word8);
            //printf("R%d= 0x%X\n",rd, Regs[rd]);
            }
              break;
            
            }
            break;

    case 5:  //case 12, 13 , 14
         det=(instr>>12)&1;
        switch (det){
            case 0:
            word8=instr&255;
            rd= (instr>>8)&7;
             source=(instr>>11)&1;
            if (source==0){
            //memindex=word8+ Regs[15];
            // Regs[rd]=Mem[memindex];
            //Regs[rd]=memindex;
            printf("add\tr%d, pc,#%d\n",rd ,word8);
            // Regs[rd]=PC+word8;
            //printf("R%d= 0x%X\n",rd, Regs[rd]);
            }
            else{
            /* memindex=word8+Regs[13];
            Regs[rd]=memindex; */
            // Regs[rd]=Mem[memindex];
            printf("add\tr%d, sp,#%d\n",rd ,word8);
            //printf("R%d= %d\n",rd, Regs[rd]);
            }
            break;         
            
            
         

            case 1:
             det2=(instr>>10)&1;
            switch(det2){
                case 0: //format 13
                    S=(instr>>7)&1;
                    sword7= instr& 127;
                    if (S==0){
                        Regs[13]=Regs[13]+sword7;
                        sp=Regs[13];
                     printf("add\tsp,#%d\t ",sword7);
                     printf("SP= 0x%X\n", Regs[13]);
                    // printf("R%d= 0x%X\n",rd, Regs[rd]);
                    }
                    else{
                        Regs[13]=Regs[13]-sword7;
                         sp=Regs[13];
                    printf("add\tsp,#-%d\t ",sword7);
                    printf("SP= 0x%X\n", Regs[13]);
                    //printf("R%d= 0x%X\n",rd, Regs[rd]);
                    }
                    break;

                case 1: //format 14
                Rlist= instr&0xFF;
                R=(instr>>8)&1;
                L=(instr>>11)&1;
                if (L==0){
                        if (R==0){
                        printf("push {r");
                        printRlist(Rlist,0,Regs,Mem);
                        printf("}\n");                        
                        }
                        else{
                         printf("push {");
                        printRlist(Rlist,0,Regs,Mem);
                     pushorpoplr(Rlist,0,Regs,Mem);
                        printf(",lr}\n");
                        }
                }
                else{
                        if (R==0){
                        printf("pop {");
                        printRlist(Rlist,1,Regs,Mem);
                        printf("}\n");                        
                        }
                        else{
                         printf("pop {");
                        printRlist(Rlist,1,Regs,Mem);
                        pushorpoplr(Rlist,1,Regs,Mem);
                        printf(",pc}\n");
                        }                        
                }
                    break;

            }
        


        }
        break;
       
    //----------------------Basuony---------------------------------------//
       case 6:
            
          cond = (instr >> 8) & 15;
             offset= instr  & 0xFF;
             /* if (((offset>>7)&1)==1){
              offset=(offset|0xFFFFFF00);  //sign extend if the number happens to be negative
          } */
        //   if (offset<0)
        //   offset=-offset;
            rb = (instr >> 8) & 7;
           rd = (instr>>4) & 15;
           ro = instr  & 15;
           L = (instr >> 11) & 1;
            detect = (instr >> 8);
            bit12=(instr>>12)&1;
        if(detect==223)
           { //format 17
       
               printf("SWI \t %d", offset);
               if (offset == 1)  // Print int
                  cout << "  " << dec<<Regs[0]<<endl;

               else if (offset == 5) // read int
              {
                  cout<<" ";
                   cin >> Regs[0];
                   
              }
               else if (offset == 8) // read string
               {
                   char in2;
                   Regs[0] = j; // address of the string in R0
                   for (int i = 0; i < Regs[1]; i++)
                   {   
                       cin >> in2;
                       Mem[j] = in2;
                       j++;
                       if (cin.get() == '\n') {
                           break;
                       }
                   }
                  
                   
               }
               else if (offset == 4) // print string
               {
                   int i = Regs[0]; // Getting the start address of the string 
                   while (true)
                   {
                       char x = Mem[i];
                       cout << x;
                       i++;
                       if (x == 0)
                       {
                           cout << endl;
                           break;
                       }
                   }
               }
               else if (offset == 12)  // read char
               {
                 
                   int char_saver = 500;
                   char in;
                  
                   cin >> in;
                   Mem[char_saver] = in;
                   Regs[0] = char_saver;
                   char_saver++;
                   if (cin.get() == in) {
                       break;
                   }
               }
               else if (offset == 11) // print char
               {
                   cout << Mem[Regs[0]]<<endl; //assuming the regs is read an saved in char_saver

               }
               else if (offset == 10) //terminate 
               {
                   return 0;
               }
               else
               {
                   cout << " | " << "undefined call" << endl;
               }
           
           }
         else {
             if (bit12==0){
          if(L==0)
           { //format 15
        
               printf("stmia\tr%d, [ r%d, r%d ]\n", rd, rb, ro);
               i++;
               break;
           }
          else {
               printf("ldmia\tr%d, [ r%d, r%d]\n", rd, rb, ro);
               i++;
          
              break;
          }
             }
             else{
           switch (cond) //format 16
           {
           case 0:
               printf("beq\t %d\n", offset);
               i++;
            //    if(bits[30]==1)
            //    Regs[15] =  Regs[15] + offset ;
               break;
           case 1:
               printf("bne\t %d\n", offset);
               i++;
            //    if (bits[30] == 0)
            //    PC = PC + offset - 2;
               break;
           case 2:
               printf("bcs\t %d\n", offset);
               i++;
            //    if (bits[29] == 1)
            //    PC = PC + offset - 2;
               break;
           case 3:
               printf("bcc\t %d\n", offset);
               i++;
            //    if (bits[29] == 0)
            //    PC = PC + offset - 2;
               break;
           case 4:
               printf("bmi\t %d\n", offset);
               i++;
            //    if (bits[31] == 1)
            //    PC = PC + offset - 2;
               break;
           case 5:
               printf("bpl\t %d\n", offset);
               i++;
            //    if (bits[31] == 0)
            //    PC = PC + offset - 2;
               break;
           case 6:
               printf("bvs\t %d\n", offset);
               i++;
            //    if (bits[28] == 1)
            //    PC = PC + offset - 2;
               break;
           case 7:
               printf("bvc\t %d\n", offset);
               i++;
            //    if (bits[28] == 0)
            //    PC = PC + offset - 2;
               break;
           case 8:
               printf("bhi\t %d\n", offset);
               i++;
            //    if ((bits[29]==1)&&(bits[30]==0))
            //    PC = PC + offset - 2;
               break;
           case 9:
               printf("bls\t %d\n", offset);
               i++;
            //    if ((bits[29] == 0) || (bits[30] == 1))
            //    PC = PC + offset - 2;
               break;
           case 10:
               printf("bge\t %d\n", offset);
               i++;
            //    if (((bits[31] == 1) && (bits[28] == 1)) || ((bits[31] == 0) && (bits[28] == 0)))
            //    PC = PC + offset - 2;
               break;
           case 11:
               printf("blt\t %d\n", offset);
               i++;
            //    if (((bits[31] == 1) && (bits[28] == 0)) || ((bits[31] == 0) && (bits[28] == 1)))
            //    PC = PC + offset - 2;
               break;
           case 12:
               printf("bgt\t %d\n", offset);
               i++;
            //    if ((bits[30]==0) && (((bits[31] == 1) && (bits[28] == 1)) || ((bits[31] == 0) && (bits[28] == 0))))
            //                 PC = PC + offset - 2;
               break;
           case 13:
               printf("ble\t %d\n", offset);
               i++;
            //    if ((bits[30] == 1) || (((bits[31] == 1) && (bits[28] == 0)) || ((bits[31] == 0) && (bits[28] == 1))))
            //    PC = PC + offset - 2;
               break;
           default:  printf("\n");

           }
             }}
           break;

       case 7:
       
     if(((instr>>11)&3) == 0) {
                
              if(instr & 0x400)
                    offset = (instr & 0x7FF) - 0x800;
                else
                    offset = (instr & 0x7FF);

          }else offset = (instr & 0x7FF);
            H = (instr >> 11) & 1;
            decide = (instr >> 12) & 1;
           ////need to handle the negative
           switch (decide)
           { // format 18
           case 0:
               printf("B\t %d\n", offset);
            // Regs[15]=PC+(offset<<1);  
            
               i++;
               break;
           case 1:
               switch (H) //format 19
               {
               case 0:
                   printf("BL\t  %d\n", offset);
                   i++;

                  /* Regs[14] =( offset<<12)+ PC;
                   z=Regs[14]; */
                 
                   break;
               case 1:
                   printf(/*BL\t %d*/"", offset);
                   //i++;
                //  t = PC + 2;
               
                //   Regs[15] = LR+2 +( offset<<1 );
                //    Regs[14] = t |1; 
                  cout<<dec<<Regs[15]<<" "<<hex<<LR<<endl;
                   break;
                   default:   printf("UNKNOWN INSTR!\n");
               }
           } break;



    /*
        case 7:
            if(((instr>>11)&3) == 0) {
                int off;
                if(instr & 0x400)
                    off = (instr & 0x7FF) - 0x800;
                else
                    off = (instr & 0x7FF);
                printf("B\t%d\t\t# Jump to (current instr. addr)+4%+d\n", off,off*2);
            }
            break;
        */
    default:
        printf("UNKNOWN INSTR!\n");
    }
}