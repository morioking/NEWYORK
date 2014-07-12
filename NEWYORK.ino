
const int LED = 13;
const int MOTO1_CW = 9;
const int MOTO1_CCW = 10;
const int MOTO2_CW = 5;
const int MOTO2_CCW = 6;

const int TRIG = 6;
const int ECHO = 7;

int val = 0;
int state =0;

void setup() 
{
    pinMode(LED, OUTPUT);
    pinMode(MOTO1_CW, OUTPUT);
    pinMode(MOTO1_CCW, OUTPUT);
    pinMode(MOTO2_CW, OUTPUT);
    pinMode(MOTO2_CCW, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    Serial.begin(9600);
}


void loop() 
{
    
    // エコー信号の長さをマイクロ秒単位で返す
    //float distance;
    //distance = getDistance(getEchoLength());
    //Serial.println(distance);
    
    char serialread;
    serialread = Serial.read();
    Serial.println(serialread);
        
    if(serialread == 'r'){
      state = 1;
    }else if(serialread =='w'){
      state = 0;
    }
    
    if(state == 1){
      analogWrite(MOTO1_CW, 255);
      analogWrite(MOTO1_CCW, 0);
      analogWrite(MOTO2_CW, 255);
      analogWrite(MOTO2_CCW, 0); 
      
      // Lチカ
      digitalWrite(LED,HIGH);
      delay(100);
      digitalWrite(LED,LOW);
      delay(100);
      
    }else{
      // 停止
      digitalWrite(MOTO1_CW,LOW);
      digitalWrite(MOTO1_CCW,LOW);
      digitalWrite(MOTO2_CW,LOW);
      digitalWrite(MOTO2_CCW,LOW);
    }
  

    
    
    /*
    if(distance < 10) {
      // 停車
      
      // PWMによる出力値０〜２５５　停止
     analogWrite(VELO,0);
      
      // Lチカ
      digitalWrite(LED,HIGH);
      delay(100);
      digitalWrite(LED,LOW);
      delay(100);
      
    } else {
      // PWMによる出力値０〜２５５　前進
      analogWrite(VELO,255);
      
      // LED点灯
      digitalWrite(LED,HIGH);
    }
    */
    
} 


// エコー信号の長さをマイクロ秒単位で返す
// 引用元 http://wiki.androciti.com/index.php?%C4%B6%B2%BB%C7%C8%B5%F7%CE%A5%C2%AC%C4%EA%A5%BB%A5%F3%A5%B5%A1%BC%A5%E2%A5%B8%A5%E5%A1%BC%A5%EB
long getEchoLength(){
  long echoLen;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);   //トリガに10マイクロ秒のhighパルスを出力し超音波を発生
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  echoLen = pulseIn(ECHO, HIGH); // エコー信号の長さをマイクロ秒単位で入手
  return echoLen;
}

// エコー信号の長さからセンチメートル単位で距離を計算する
float getDistance(long echoLen){
 float distance = ((float)echoLen/2)/29.1; // エコーの長さから距離に変換
 return distance;
}



