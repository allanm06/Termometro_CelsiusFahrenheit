#define button portd.rd0

//endereçamento do display de lcd
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

void celsius(void){

long int tc_rd = 0;
char txt[7]= "0.0"; //string de destino
lcd_out(1,1,"-----TERMOMETRO-----");

tc_rd = ADC_Read(0); //lê valor do AD, em seguida converte em ºC
tc_rd = tc_rd*0.48875;

IntToStr(tc_rd,txt); //convrte inteiro em string

lcd_out(2,1,txt);
lcd_out(2,8,"Celsius");
}

void fahrenheit(void){

long int tf_rd = 0;
char txt[7]= "0.0"; //string de destino
lcd_out(1,1,"-----TERMOMETRO-----");

tf_rd = ADC_Read(0); //lÊ valor do AD, em seguida converte para ºF
tf_rd = (tf_rd*0.87975 + 32);

IntToStr(tf_rd,txt); //Converte inteiro em string

lcd_out(2,1,txt);
lcd_out(2,8,"Fahrenheit");
}

void main(){

int ctr = 0;

TRISA = 1; //Pino RA0 como entrada
TRISD = 1; //Pino RD0 como entrada

ADCON0 = 1; //Liga o conversor AD
ADCON1 = 14; //AN0 como entrada analógica

//iniciando o LCD
lcd_init();
lcd_cmd(_LCD_CURSOR_OFF);
lcd_cmd(_LCD_CLEAR);

while(1){

//controle de troca de unidades ºC/ºF
if((button == 0)&&(ctr == 0)){celsius();}
if((button == 1)&&(ctr == 0)){ctr=1;}
if((button == 0)&&(ctr == 1)){ctr=2;lcd_cmd(_LCD_CLEAR);}
if((button == 0)&&(ctr == 2)){fahrenheit();}
if((button == 1)&&(ctr == 2)){ctr=3;}
if((button == 0)&&(ctr == 3)){ctr=0;lcd_cmd(_LCD_CLEAR);}
 }
}