# 1 "d:\\Programming\\source\\repos\\Arduino\\Arduino_OBD2_Reader\\Arduino_Sketch\\sketch\\sketch.ino"
# 2 "d:\\Programming\\source\\repos\\Arduino\\Arduino_OBD2_Reader\\Arduino_Sketch\\sketch\\sketch.ino" 2
# 3 "d:\\Programming\\source\\repos\\Arduino\\Arduino_OBD2_Reader\\Arduino_Sketch\\sketch\\sketch.ino" 2
# 4 "d:\\Programming\\source\\repos\\Arduino\\Arduino_OBD2_Reader\\Arduino_Sketch\\sketch\\sketch.ino" 2
# 5 "d:\\Programming\\source\\repos\\Arduino\\Arduino_OBD2_Reader\\Arduino_Sketch\\sketch\\sketch.ino" 2

dh::OBDIIController obdController;
dh::ExhaustController exhaustController;
bool valvesOpen;

void setup()
{
  // put your setup code here, to run once:
  Init();

  //obdController.Init();
  exhaustController.Init();
  valvesOpen = false;
}

void loop()
{
  delay(5000);
  exhaustController.SetControlPin(valvesOpen);
  valvesOpen = !valvesOpen;
}

void Init()
{
  Serial.begin(9600);
  Serial.println("Serial initialized");
  dh::LCDController::Init();
}
