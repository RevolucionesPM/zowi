//sv

#include <Arduino.h>
#include <Servo.h>
#include <Oscillator.h>

#define N_OSCILLATORS 9

#define TRIM_RR -2
#define TRIM_RL -15
#define TRIM_YR -9
#define TRIM_YL -6
#define TRIM_SR 25
#define TRIM_SL -15
#define TRIM_AR 14
#define TRIM_AL 45
#define TRIM_H -12


#define PIN_RR 4
#define PIN_RL 5
#define PIN_YR 6
#define PIN_YL 7
#define PIN_SR 2
#define PIN_SL 8
#define PIN_AR 3
#define PIN_AL 9
#define PIN_H 12

Oscillator osc[N_OSCILLATORS];

void run(int steps=1, int T=500);
void walk(int steps=1, int T=1000);
void backward(int steps=1, int T=1000);
void turnL(int steps=1, int T=1000);
void turnR(int steps=1, int T=1000);
void moonWalkL(int steps=1, int T=1000);
void moonWalkR(int steps=1, int T=1000);
void upDown(int steps=1, int T=700);
void home();
void attack();
void punchL();
void punchR();
void nono(int T=1000);
void queno(int T=300);

void setup()
{
    Serial.begin(19200);
    osc[0].attach(PIN_RR);
    osc[1].attach(PIN_RL);
    osc[2].attach(PIN_YR);
    osc[3].attach(PIN_YL);
    osc[4].attach(PIN_SR);
    osc[5].attach(PIN_SL);
    osc[6].attach(PIN_AR);
    osc[7].attach(PIN_AL);/**/
    osc[8].attach(PIN_H);/**/

    osc[0].SetTrim(TRIM_RR);
    osc[1].SetTrim(TRIM_RL);
    osc[2].SetTrim(TRIM_YR);
    osc[3].SetTrim(TRIM_YL);
    osc[4].SetTrim(TRIM_SR);
    osc[5].SetTrim(TRIM_SL);
    osc[6].SetTrim(TRIM_AR);
    osc[7].SetTrim(TRIM_AL);/**/
    osc[8].SetTrim(TRIM_H);/**/

    home();
    nono();
}

char input;

void loop()
{
    if(Serial.available()){
        while (Serial.available()) input = Serial.read();
        switch(input){
            case 'A':
                walk(1, 1200);
                break;

            case 'B':
                turnR();
                break;

            case 'C':
                backward();
                break;

            case 'D':
                turnL();
                break;

            case 'E':
                upDown();
                break;

            case 'F':
                punchR();
                delay(300);
                break;

            case 'G':
                attack();
                delay(300);
                break;

            case 'H':
                punchL();
                delay(300);
                break;

            case 'I':
                queno();
                break;

            case 'J':
                nono(1000);
                break;
            default:
                home();
                break;
        }
        Serial.flush();
    }
    else home();
}


void oscillate(int A[N_OSCILLATORS], int O[N_OSCILLATORS], int T, double phase_diff[N_OSCILLATORS]){
  for (int i=0; i<8; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(T);
    osc[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<8; i++){
        osc[i].refresh();
     }
  }
}

void oscillate_mod(int A[N_OSCILLATORS], int O[N_OSCILLATORS], int Ta , int Tb, double phase_diff[N_OSCILLATORS]){
  for (int i=0; i<2; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(Ta);
    osc[i].SetPh(phase_diff[i]);
  }
  for (int i=2; i<4; i++) {
    osc[i].SetO(O[i]);
    osc[i].SetA(A[i]);
    osc[i].SetT(Tb);
    osc[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<Tb+ref; x=millis()){
     for (int i=0; i<4; i++){
        osc[i].refresh();
     }
  }
}

void walk(int steps, int T){
    int A[8]= {18, 18, 20, 20, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnR(int steps, int T){
    int A[8]= {15, 15, 10, 30, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnL(int steps, int T){
    int A[8]= {15, 15, 30, 10, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void backward(int steps, int T){
    int A[8]= {15, 15, 25, 25, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(90), DEG2RAD(90), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void moonWalkR(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 10, 10};
    int O[8] = {-15, 15, 0, 0, 60, -60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(180), DEG2RAD(180), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkL(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 20, 20};
    int O[8] = {-15, 15, 0, 0, 60, -60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(0), DEG2RAD(0), DEG2RAD(0), DEG2RAD(0)};


    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 35, 35};
    int O[8] = {-25, 25, 0, 0, -60, 60, 0, 0};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180), 0, 0,
                            0, 0, DEG2RAD(0), DEG2RAD(180)};

    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void home(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(50);
    osc[7].SetPosition(130);
    osc[8].SetPosition(90);
}

void attack(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(90);
    osc[5].SetPosition(90);
    osc[6].SetPosition(40);
    osc[7].SetPosition(140);
}

void punchL(){
    osc[0].SetPosition(40);
    osc[1].SetPosition(70);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(90);
    osc[7].SetPosition(30);
}

void punchR(){
    osc[0].SetPosition(110);
    osc[1].SetPosition(140);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(150);
    osc[7].SetPosition(90);
}

void nono(int T){
    home();

    int steps = 4;
    osc[8].SetO(0);
    osc[8].SetA(30);
    osc[8].SetT(T);
    osc[8].SetPh(0);

    double ref = millis();
    for (double x=ref; x<steps*T+ref; x=millis()){
        osc[8].refresh();
    }
    osc[8].SetPosition(90);
}

void queno(int T){
    home();

    int steps = 4;
    osc[8].SetO(0);
    osc[8].SetA(30);
    osc[8].SetT(T*2);
    osc[8].SetPh(0);

    osc[6].SetO(0);
    osc[6].SetA(30);
    osc[6].SetT(T);
    osc[6].SetPh(0);

    osc[7].SetO(0);
    osc[7].SetA(30);
    osc[7].SetT(T);
    osc[7].SetPh(DEG2RAD(180));

    double ref = millis();
    for (double x=ref; x<steps*T+ref; x=millis()){
        osc[6].refresh();
        osc[7].refresh();
        osc[8].refresh();
    }
    osc[6].SetPosition(50);
    osc[7].SetPosition(130);
    osc[8].SetPosition(90);
}
