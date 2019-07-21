#include <SoftwareSerial.h> //블루투스 시리얼 포트 설정
#include<Wire.h>
#include <Adafruit_MLX90614.h>
 
SoftwareSerial bluetooth(8, 9);

//자이로 변수
const int MPU=0x68;  //MPU 6050 의 I2C 기본 주소
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

//맥박 변수
volatile int BPM;                   // 심박수 저장
volatile int Signal;                // 심장박동센서에서 측정되는 값 저장
volatile int IBI = 600;             // 심박수 측정 시 사용되는 시간 변수(심장이 몇초마다 뛰는지 측정)
volatile boolean Pulse = false;     // 유저의 심박수가 측정되면 True, 아무것도 측정되지 않으면 False

//체온변수
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void setup(){
  //자이로 센서
  Wire.begin();      //Wire 라이브러리 초기화
  Wire.beginTransmission(MPU); //MPU로 데이터 전송 시작
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     //MPU-6050 시작 모드로
  Wire.endTransmission(true); 
  
  //블루투스 통신
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  //  }
  //Serial.println("Hello World!");
  //블루투스와 아두이노의 통신속도를 9600으로 설정
  bluetooth.begin(9600);

  //맥박센서
  interruptSetup();

  //체온센서
  mlx.begin();  
}

void loop(){
  //자이로 센서
  Wire.beginTransmission(MPU);    //데이터 전송시작
  Wire.write(0x3B);               // register 0x3B (ACCEL_XOUT_H), 큐에 데이터 기록
  Wire.endTransmission(false);    //연결유지
  Wire.requestFrom(MPU,14,true);  //MPU에 데이터 요청
  //데이터 한 바이트 씩 읽어서 반환
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  
 
  Serial.println(millis());
  //시리얼 모니터에 출력
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print("GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.print(GyZ);
  Serial.print("BPM: ");Serial.println(BPM);
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.println();
  bluetooth.print("{\"X\":"+String(AcX)+",");
  bluetooth.print("\"Y\":"+String(AcY)+","); 
  bluetooth.print("\"Z\":"+String(AcZ)+","); 
  bluetooth.print("\"B\":"+String(BPM)+","); 
  bluetooth.print("\"A\":"+String(mlx.readAmbientTempC())+",");
  bluetooth.print("\"O\":"+String(mlx.readObjectTempC())+"}");
  bluetooth.println();
  bluetooth.flush();
  Serial.println(millis());
  delay(5100);
}
