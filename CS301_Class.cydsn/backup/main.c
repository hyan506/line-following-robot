/* ========================================
 * Fully working code: 
 * PWM      : 
 * Encoder  : 
 * ADC      :
 * USB      : port displays speed and position.
 * CMD: "PW xx"
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
#include <math.h>
//* ========================================
#include "defines.h"
#include "vars.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================WheelSpeed Functions
void testMotor();
void printQ1(int8 input);
void printQ2(int8 input);
void printQs();
void printQss();
void updateSpeed();
void allButSquiggly();
void Squiggly();
//* ========================================WheelSpeed flags
int updateSpeedFlag = 0;
int printingFlag = 0;

int speed_change_counter = 0;
int speed_change_flag = 0;
double v1, v2;
//* ========================================ADC Functions
void printVbat();
double calculateADC(int ADC);
//* ========================================ADC Flags
int printVbatFlag = 0;
int ADC_0 = 0;
int adc0_count = 0;
int ADC_1 = 0;
int adc1_count = 0;
int ADC_2 = 0;
int adc2_count = 0;
int ADC_3 = 0;
int adc3_count = 0;
int ADC_4 = 0;
int adc4_count = 0;
int ADC_5 = 0;
int adc5_count = 0;

int turnRight = 0;
int turnLeft = 0;

// Definitions

// Higher timeout value = lower sensitivity (will correct itself less often)
int timeout = 20;
// USE 20 FOR ALLBUTSQUIGGLY
// USE 100 FOR SQUIGGLY

#define TOP_LEFT ADC_0
#define TOP_MIDDLE ADC_2
#define TOP_RIGHT ADC_4
#define BOTTOM_LEFT ADC_1
#define BOTTOM_MIDDLE ADC_3
#define BOTTOM_RIGHT ADC_5

#define SET_SPEED 40
#define SET_DISTANCE 127

int fixedCounter = (((SET_DISTANCE / SET_SPEED) * 1000) / 10) + 200;

//* ========================================RF Functions
void Receive_Data(uint8 c);
int16 concatenate(int16 a,uint8 c);
void clearRFdata();
void print_struct(int label);
//* ========================================RF Flags and variables
enum structdata {RSSI,INDEX,R_XPOS,R_YPOS,R_O,G0_XPOS,G0_YPOS,G0_SPEED,G0_DIR,G1_XPOS,G1_YPOS,G1_SPEED,G1_DIR,G2_XPOS,G2_YPOS,G2_SPEED,G2_DIR };
int start_receiving = 0;
int end_receiving = 0;
int analysing = 0;
int i = 0;
int commaCount=0;
int negative = FALSE;
int test =0;
vtype1 RFdata;
vtype1 clearedRF = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


CY_ISR_PROTO(test_isr);
CY_ISR_PROTO(check);
CY_ISR_PROTO(printing);


CY_ISR(printing) {
    printingFlag = 1;
    Timer_2_ReadStatusRegister();
    
    /*--fixedCounter;
    
    if (fixedCounter <= 0) {
        PWM_1_WriteCompare(0);
        PWM_2_WriteCompare(0);
    }*/
}


// For speed correction, 50ms timer is best. For ADC reading, 500ms. LED will show you current value.
CY_ISR(check) {
    updateSpeedFlag = 1;
    printVbatFlag = 1;
    //LED_TOGGLE;
    Timer_1_ReadStatusRegister();
    speed_change_counter++;
    if(speed_change_counter == 1){
        speed_change_flag = 1;
        speed_change_counter = 0;
    }
     /*-----------------------------------------*/
    if (calculateADC(0) > 1.0) {
        ADC_0 = 1;
        adc0_count = 0;
    }
    else{
        adc0_count++;
    }
    if (adc0_count > timeout){
        ADC_0 = 0;
        adc0_count = 0;
    }
   /*-----------------------------------------*/
        if (calculateADC(1) > 1.0) {
        ADC_1 = 1;
        adc1_count = 0;
    }
    else{
        adc1_count++;
    }
    if (adc1_count > timeout){
        ADC_1 = 0;
        adc1_count = 0;
    }
   /*-----------------------------------------*/
        if (calculateADC(2) > 1.0) {
        ADC_2 = 1;
        adc2_count = 0;
    }
    else{
        adc2_count++;
    }
    if (adc2_count > timeout){
        ADC_2 = 0;
        adc2_count = 0;
    }
   /*-----------------------------------------*/
        if (calculateADC(3) > 1.0) {
        ADC_3 = 1;
        adc3_count = 0;
    }
    else{
        adc3_count++;
    }
    if (adc3_count > timeout){
        ADC_3 = 0;
        adc3_count = 0;
    }
   /*-----------------------------------------*/
        if (calculateADC(4) > 1.0) {
        ADC_4 = 1;
        adc4_count = 0;
    }
    else{
        adc4_count++;
    }
    if (adc4_count > timeout){
        ADC_4 = 0;
        adc4_count = 0;
    }
   /*-----------------------------------------*/
        if (calculateADC(5) > 1.0) {
        ADC_5 = 1;
        adc5_count = 0;
    }
    else{
        adc5_count++;
    }
    if (adc5_count > timeout){
        ADC_5 = 0;
        adc5_count = 0;
    }
   /*-----------------------------------------*/
    
    
}



# define RECEIVING start_receiving &&(!end_receiving)


CY_ISR(test_isr){
    uint8 character = UART_GetChar();
    if (character =='#'){
        vtype1 a={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        RFdata = a;
        start_receiving = TRUE;
        end_receiving = FALSE;
        commaCount=0;
         test++;
    }else if ( character == '\n'){
         end_receiving  = TRUE;
         start_receiving = FALSE;
    }else if ( character == ','){
        commaCount= commaCount+1;
    }else if (character == '-'){
        negative = TRUE;
    }else if (character == ']'||character == '['){

    }else {
        if (RECEIVING) Receive_Data(character);

 //char notint = (char)(UART_GetChar());
 //charBuffer[0] = notint;
 //USBUART_PutChar(UART_GetChar());
   

 // i = i+1;
}

}

void Receive_Data(uint8 c){
    switch (commaCount){
        case 0 :
            RFdata.rssi = concatenate(RFdata.rssi, c-48);
            //char s[100];
            //sprintf(s, "%d",  RFdata.rssi);
            //USBUART_PutString(s);
            //USBUART_PutString((char*)(int)RFdata.rssi);
           // USBUART_PutString("a");
        break;
        case 1 :
            RFdata.index = concatenate(RFdata.index, c-48); 
            //USBUART_PutString((char*)(int)RFdata.index);
          //  USBUART_PutString("\n");
        break;
        case 2 :
            RFdata.robot_xpos = concatenate(RFdata.robot_xpos, c-48); 
            //USBUART_PutString((char*)(int)RFdata.robot_xpos);
            //USBUART_PutString("\n");
        break;
        case 3 :
            RFdata.robot_ypos = concatenate(RFdata.robot_ypos, c-48); 
            //USBUART_PutString((char*)(int)RFdata.robot_ypos);
           // USBUART_PutString("\n");
        break;
        case 4 :
            RFdata.robot_orientation = concatenate(RFdata.robot_orientation, c-48); 
           // USBUART_PutString((char*)(int)RFdata.robot_orientation);
          //  USBUART_PutString("\n");
        break;
        case 5 :
            RFdata.g0_xpos = concatenate(RFdata.g0_xpos, c-48); 
            //USBUART_PutString((char*)(int)RFdata.g0_xpos);
           // USBUART_PutString("\n");
        break;
        case 6 :
            RFdata.g0_ypos = concatenate(RFdata.g0_ypos, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g0_ypos);
           // USBUART_PutString("\n");
        break;
        case 7 :
            RFdata.g0_speed = concatenate(RFdata.g0_speed, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g0_speed);
           // USBUART_PutString("\n");
        break;
        case 8 :
            RFdata.g0_direction = concatenate(RFdata.g0_direction, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g0_direction);
            //USBUART_PutString("\n");
        break;
        case 9 :
            RFdata.g1_xpos = concatenate(RFdata.g1_xpos, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g1_xpos);
            //USBUART_PutString("\n");
        break;
        case 10 :
            RFdata.g1_ypos = concatenate(RFdata.g1_ypos, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g1_ypos);
           // USBUART_PutString("\n");
        break;
        case 11 :
            RFdata.g1_speed = concatenate(RFdata.g1_speed, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g1_speed);
           // USBUART_PutString("\n");
        break;
        case 12 :
            RFdata.g1_direction = concatenate(RFdata.g1_direction, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g1_direction);
            //USBUART_PutString("\n");
        break;
        case 13 :
            RFdata.g2_xpos = concatenate(RFdata.g2_xpos, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g2_xpos);
           // USBUART_PutString("\n");
        break;
        case 14 :
            RFdata.g2_ypos = concatenate(RFdata.g2_ypos, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g2_ypos);
           // USBUART_PutString("\n");
        break;
        case 15 :
            RFdata.g2_speed = concatenate(RFdata.g2_speed, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g2_speed);
           // USBUART_PutString("\n");
        break;
        case 16 :
            RFdata.g2_direction = concatenate(RFdata.g2_direction, c-48); 
           // USBUART_PutString((char*)(int)RFdata.g2_direction);
           // USBUART_PutString("\n");
        break;
        default:
        return;

    }
}

int16 concatenate(int16 a,uint8 b){
    if(negative){
        negative = FALSE;  
        a = -b;
    }
    else if(a<0){
        a = a*10-b;   
    }
    else{
        a = a*10+b;
    }
    return a;
}

void print_something(int a){
    char s[1000];
    sprintf(s, "%d\n", a);
    usbPutString(s);
}
void print_struct(int label){
    char s[1000];
    switch(label){
        case RSSI:
            sprintf(s, "RSSI: %d\n", RFdata.rssi);
            usbPutString(s);
            break;
        case INDEX:
            sprintf(s, "INDEX: %d\n", RFdata.index);
            usbPutString(s);
            break;
        case R_XPOS:
            sprintf(s, "R_XPOS: %d\n", RFdata.robot_xpos);
            usbPutString(s);
            break;
        case R_YPOS:
            sprintf(s, "R_YPOS: %d\n", RFdata.robot_ypos);
            usbPutString(s);
        break;
        case R_O:
            sprintf(s, "R_O: %d\n", RFdata.robot_orientation);
            usbPutString(s);
            break;
        case G0_XPOS:
            sprintf(s, "G0_XPOS: %d\n", RFdata.g0_xpos);
            usbPutString(s);
            break;
        case G0_YPOS:
            sprintf(s, "G0_YPOS: %d\n", RFdata.g0_ypos);
            usbPutString(s);
            break;
        case G0_SPEED:
            sprintf(s, "G0_SPEED: %d\n", RFdata.g0_speed);
            usbPutString(s);     
            break;
        case G0_DIR:
            sprintf(s, "G0_DIR: %d\n", RFdata.g0_direction);
            usbPutString(s);    
            break;
        case G1_XPOS:
            sprintf(s, "G1_XPOS: %d\n", RFdata.g1_xpos);
            usbPutString(s);    
            break;
        case G1_YPOS:
            sprintf(s, "G1_YPOS: %d\n", RFdata.g1_ypos);
            usbPutString(s);    
            break;
        case G1_SPEED:
            sprintf(s, "G1_SPEED: %d\n", RFdata.g1_speed);
            usbPutString(s);     
            break;
        case G1_DIR:
            sprintf(s, "G1_DIR: %d\n", RFdata.g1_direction);
            usbPutString(s);    
            break;
        case G2_XPOS:
            sprintf(s, "G2_XPOS: %d\n", RFdata.g2_xpos);
            usbPutString(s);     
            break;
        case G2_YPOS:
            sprintf(s, "G2_YPOS: %d\n", RFdata.g2_ypos);
            usbPutString(s);     
            break;     
        case G2_SPEED:
            sprintf(s, "G2_SPEED: %d\n", RFdata.g2_speed);
            usbPutString(s);     
            break;
        case G2_DIR:
            sprintf(s, "G2_DIR: %d\n", RFdata.g2_direction);
            usbPutString(s);    
            break;

        }
   }






int main()
{

// --------------------------------
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    LED_OFF;
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    PWM_1_Start();
    PWM_2_Start();
    Timer_1_Start();
    Timer_2_Start();
    check_StartEx(check);
    printing_StartEx(printing);
    isrRF_RX_StartEx(test_isr);
    USBUART_Start(0,USBUART_5V_OPERATION);
    
    // ADC Initialisations
    ADC_Start();
    ADC_StartConvert();
    
    //UART Init
    RF_BT_SELECT_Write(0);
    UART_Start();
    
    PWM_1_WriteCompare(225);

//running while loop 
    while (1) {
        
        
        
    /*    if(speed_change_flag){
            speed_change_flag = 0;
            
            // Select different modes.
            if (DIP0_Read() == 0) {
                LED_OFF;
                allButSquiggly();
            }
            else if (DIP0_Read() == 1) {
                LED_ON;
                Squiggly();
            }
        }*/
        
        
        
        
        if (printingFlag == 1 && fixedCounter >= 0) {
            updateSpeed();
            printingFlag = 0;
        }
    }
    
// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);

    usbPutString(displaystring);
    for(;;)
    {
        /* Place your application code here. */
        handle_usb();
        if (flag_KB_string == 1)
        {
            usbPutString(line);
            flag_KB_string = 0;
        }        
    }   
}
//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')

#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
#endif    
}
//* ========================================
void handle_usb()
{
    // handles input at terminal, echos it back to the terminal
    // turn echo OFF, key emulation: only CR
    // entered string is made available in 'line' and 'flag_KB_string' is set
    
    static uint8 usbStarted = FALSE;
    static uint16 usbBufCount = 0;
    uint8 c; 
    

    if (!usbStarted)
    {
        if (USBUART_GetConfiguration())
        {
            USBUART_CDC_Init();
            usbStarted = TRUE;
        }
    }
    else
    {
        if (USBUART_DataIsReady() != 0)
        {  
            c = USBUART_GetChar();

            if ((c == 13) || (c == 10))
            {
//                if (usbBufCount > 0)
                {
                    entry[usbBufCount]= '\0';
                    strcpy(line,entry);
                    usbBufCount = 0;
                    flag_KB_string = 1;
                }
            }
            else 
            {
                if (((c == CHAR_BACKSP) || (c == CHAR_DEL) ) && (usbBufCount > 0) )
                    usbBufCount--;
                else
                {
                    if (usbBufCount > (BUF_SIZE-2) ) // one less else strtok triggers a crash
                    {
                       USBUART_PutChar('!');        
                    }
                    else
                        entry[usbBufCount++] = c;  
                }  
            }
        }
    }    
}
// basic test turns motors on and off at different speeds 5s on 5s off.
void testMotor(){
   //wait for 5s  
   COAST_ON;
   CyDelay(5000);
   //disable motor
   LED_TOGGLE;
   // off 5s
   COAST_OFF;
   CyDelay(5000);
    
}

void printQ1(int8 i) {
    
    // Stores the quadrature counter value in a char.
    char str0[15];
    sprintf(str0, "%d", i);
    
    // Creates the naming text.
    char str1[15] = "Q1: ";
    
    // Concatenates the naming text with the counter value and an end line.
    strcat(str1, str0);
    strcat(str1, "\r\n");
    
    // Prints to PuTTY.
    USBUART_PutString(str1);
}

void printQ2(int8 i) {
    
    // Stores the quadrature counter value in a char.
    char str0[15];
    sprintf(str0, "%d", i);
    
    // Creates the naming text.
    char str1[15] = "Q2: ";
    
    // Concatenates the naming text with the counter value and an end line.
    strcat(str1, str0);
    strcat(str1, "\r\n");
    strcat(str1, "\r\n");
    
    // Prints to PuTTY.
    USBUART_PutString(str1);
}

void printQs() {
    
    // Outputs the result every second.
    CyDelay(1000);
    
    // Prints the quadrature counter values.
    printQ1(QuadDec_M1_GetCounter());
    printQ2(QuadDec_M2_GetCounter());
}

void printQss() {
    
    // Outputs the result every second.
    CyDelay(1000);
    
    // Stores the quadrature counter value in a char.
    char str0[15];
    sprintf(str0, "%d", (~QuadDec_M1_GetCounter() + 1));
    
    // Creates the naming text.
    char str1[15] = "Q1: ";
    
    // Concatenates the naming text with the counter value and an end line.
    strcat(str1, str0);
    strcat(str1, "\r\n");
    
    
    
    // Stores the quadrature counter value in a char.
    char str2[15];
    sprintf(str2, "%d", QuadDec_M2_GetCounter());
    
    // Creates the naming text.
    char str3[15] = "Q2: ";
    
    // Concatenates the naming text with the counter value and an end line.
    strcat(str3, str2);
    strcat(str3, "\r\n");
    strcat(str3, "\r\n");
    
    strcat(str1, str3);
    
    // Prints to PuTTY.
    USBUART_PutString(str1);
}

void updateSpeed() {
    
    // Variable Initialisations
    double c1, c2;                              // Quadrature counter values
    //double v1, v2;                              // Linear velocity values
    char s1[100] = "Q1: ", s2[100] = "Q2: ";    // Name strings
    char s3[10], s4[10];                        // Output strings
    char s5[10] = " cm/s";                      // Unit string
    //uint8 n1, n2, n3, n4, n5, n6;               // Floating point values
    int n1, n2, n3, n4, n5, n6;               // Floating point values
    
    // Waits for one second.
    //CyDelay(500);
    
    // Gets the quadrature's counter value after one second.
    c1 = (~QuadDec_M1_GetCounter())+1;
    
    // Calculates the linear velocity.
    if (c1 > 0.0) {
        v1 = (1.0 / ((0.5 / c1) * 57.0)) * 2.0 * M_PI * 3.25;
    }
    else {
        v1 = 0.0;
    }
    
    // Splits the double into decimal values.
    //n1 = (uint8)(v1);
    //n2 = (uint8)(v1 * 10) % 10;
    //n3 = (uint8)(v1 * 100) % 10;
    n1 = (int)(c1);
    n2 = (int)(c1 * 10) % 10;
    n3 = (int)(c1 * 100) % 100;
    
    // Outputs the linear velocity.
    sprintf(s3, "%d.%d%d", n1, n2, n3);
    //sprintf(s3, "%d", (int)(c1)); // this will print out pure quadrature value
    strcat(s1, s3);
    strcat(s1, s5);
    strcat(s1, "\r\n");
    USBUART_PutString(s1);
    
    // Resets the quadrature's counter value.
    QuadDec_M1_SetCounter(0);
    
    
    
    
    
    // Gets the quadrature's counter value after one second.
    c2 = QuadDec_M2_GetCounter();
    
    // Calculates the linear velocity.
    if (c2 > 0.0) {
        v2 = (1.0 / ((0.5 / c2) * 57.0)) * 2.0 * M_PI * 3.25;
    }
    else {
        v2 = 0.0;
    }
    
    // Splits the double into decimal values.
    n4 = (uint8)(v2);
    n5 = (uint8)(v2 * 10) % 10;
    n6 = (uint8)(v2 * 100) % 10;
    
    // Outputs the linear velocity.
    //sprintf(s4, "%d.%d%d", n4, n5, n6);
    sprintf(s4, "%d", (int)(c2)); // this will print out pure quadrature value
    strcat(s2, s4);
    strcat(s2, s5);
    strcat(s2, "\r\n");
    strcat(s2, "\r\n");
    USBUART_PutString(s2);
    
    // Resets the quadrature's counter value.
    QuadDec_M2_SetCounter(0);
    
    // Sets a speed for the wheels.
    /*if (v2 > SET_SPEED && PWM_2_ReadCompare() >= 10) {
        PWM_2_WriteCompare(PWM_2_ReadCompare() - 10);
    }
    else if (v2 < SET_SPEED && PWM_2_ReadCompare() <= 245) {
        PWM_2_WriteCompare(PWM_2_ReadCompare() + 10);
    }
    
    // Corrects the speed.
    if (v1 > SET_SPEED && PWM_1_ReadCompare() >= 10) {
        PWM_1_WriteCompare(PWM_1_ReadCompare() - 10);
    }
    else if (v1 < SET_SPEED && PWM_1_ReadCompare() <= 245) {
        PWM_1_WriteCompare(PWM_1_ReadCompare() + 10);
    }*/
}

void printVbat() {
    
    // Variable Initialisations
    double Vbat = ADC_CountsTo_Volts(ADC_GetResult16(0));   // Battery voltage value
    char s1[10];                                                   // Output string
    char s2[10] = " V";                                            // Unit string
    uint8 n1, n2, n3;                                              // Floating point values
    
    // Splits the double into decimal values.
    n1 = (uint8)(Vbat);
    n2 = (uint8)(Vbat * 10) % 10;
    n3 = (uint8)(Vbat * 100) % 10;
    
    // Outputs the battery voltage.
    sprintf(s1, "%d.%d%d", n1, n2, n3);
    strcat(s1, s2);
    strcat(s1, "\r\n");
    USBUART_PutString(s1);
}

double calculateADC(int ADC) {
    
    // Variable Initialisations
    double TL = ADC_CountsTo_Volts(ADC_GetResult16(ADC));   // Battery voltage value
    
    return TL;
}

void allButSquiggly() {
    
    timeout = 20;
    
    if (turnRight == 1) {
        PWM_1_WriteCompare(60);
        PWM_2_WriteCompare(60);
        Direction_Control_1_Write(1);
        Direction_Control_2_Write(1);
        
       
    }
    
    else if (turnLeft == 1) {
        PWM_1_WriteCompare(60);
        PWM_2_WriteCompare(60);
        Direction_Control_1_Write(2);
        Direction_Control_2_Write(2);
    }
    
    else {
        
        // Towards right correction
        if (TOP_RIGHT == 0) {
            PWM_1_WriteCompare(180);
            PWM_2_WriteCompare(55);
        }
        
        // Towards left correction
        else if (TOP_LEFT == 0) {
            PWM_1_WriteCompare(55);
            PWM_2_WriteCompare(180);
        }
        
        else {
            PWM_1_WriteCompare(100);
            PWM_2_WriteCompare(100);
        }
        
        // Turning right
        if (TOP_LEFT == 1 && TOP_MIDDLE == 1 && TOP_RIGHT == 1 && BOTTOM_LEFT == 1 && BOTTOM_RIGHT == 0) {
            turnRight = 1;
            
        }
        
        else if (TOP_LEFT == 1 && TOP_MIDDLE == 1 && TOP_RIGHT == 1 && BOTTOM_LEFT == 0 && BOTTOM_RIGHT == 1) {
            turnLeft = 1;
        }
    }
    
    if (TOP_MIDDLE == 0 && (turnRight == 1 || turnLeft == 1)) {
        Direction_Control_1_Write(1);
        Direction_Control_2_Write(2);
        turnLeft = 0;
        turnRight = 0;
    }
}

void Squiggly() {
    
    timeout = 100;
        
    // Towards right correction
    if (TOP_RIGHT == 0) {
        Direction_Control_1_Write(1);
        Direction_Control_2_Write(1);
        PWM_1_WriteCompare(80);
        PWM_2_WriteCompare(55);
    }
    
    // Towards left correction
    else if (TOP_LEFT == 0) {
        Direction_Control_1_Write(2);
        Direction_Control_2_Write(2);
        PWM_1_WriteCompare(55);
        PWM_2_WriteCompare(80);
    }
    
    else {
        Direction_Control_1_Write(1);
        Direction_Control_2_Write(2);
        PWM_1_WriteCompare(60);
        PWM_2_WriteCompare(60);
    }
}

/* [] END OF FILE */
