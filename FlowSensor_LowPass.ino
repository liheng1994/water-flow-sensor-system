int flowPin = 3;   // This is the input pin on the Arduino
float flowRate;    //This is the value we intend to calculate.
volatile int count;//This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.
float velocity;    // This is the value of vehicle's speed
double Vf;         // Value if filtered
double Vprev;      //Vf(t-1)  previous value
double LPF;        //The value of after Low Pass Filter 
double v;
void setup()
{
  pinMode(flowPin, INPUT); //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);  //Configures interrupt 0 to run the function "Flow"
  Serial.begin(9600);  //Start Serial

}

void loop()
{
  count = 0;
  interrupts();
  delay(500);
  noInterrupts();

  flowRate = (count * 2.25);        //Take counted pulses in the last second and multiply by 2.25mL
  flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute
  flowRate = flowRate / 1000;       //Convert mL to Liters, giving you Liters / Minute
  v=flowRate * 1000;                //Convert Liters / Min to cm^3/min 
  v=v / 1.1304;                     //Compute velocity of vehicle(cm/min) the cross-sectional area of water pipe is 1.1304 cm^2
  v=v / 100;                        //Convert cm/min to m/min
  float alpha =0.8;                 //Tf/(Tf+Ts)  set Tf=0.01 Ts=0.001
  float LPF = alpha*Vprev + (1-alpha)*flowRate; //Low pass filter
  Vprev = LPF;                      //save previous variable
  Serial.println(flowRate);
  Serial.write(flowRate);
  //Serial.println("  Liters/min");
  //Serial.print(","); 
  Serial.println(LPF);
  //Serial.println("  Liters/min(Filtered)");
  //Serial.print(","); 
  //Serial.print(v);
  //Serial.println("  Meters/min");
}
void Flow()
{
  count++; //Every time this function is called, increment "count" by 1
}

smtpObj.sendmail(sender, receivers, message)

//float lowPassFilter(float flowRate)
//{
//  unsigned long now_us = micros();
//  float Ts = (now_us - timestamp) * 1e-6;
//  // quick fix for strange cases (micros overflow)
//  if(Ts <= 0 || Ts > 0.5) Ts = 1e-3; 
//
//  // calculate the filtering 
//  float alpha = Tf/(Tf + Ts);
//  float out = alpha*Vprev + (1-alpha)*flowRate;
// 
// 
//  // save the variables
//  Vprev = out;
//  timestamp = now_us;
//  return out;
//}
