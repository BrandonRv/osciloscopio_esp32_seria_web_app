# 1 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/osciloscopio_esp32/osciloscopio_esp32.ino"


unsigned long previousMillisRead = 0; // Para controlar el tiempo de lectura del serial
unsigned long previousMillisBlink = 0; // Para controlar el tiempo de parpadeo del LED

const long intervalRead = 50; // Intervalo para la lectura del estado del serial (50 ms)
const long intervalBlink = 500; // Intervalo para el parpadeo del LED (500 ms)

bool ledBlinkState = 0x0; // Estado actual del LED para parpadeo

void setup() {
  // Configurar el pin del LED como salida
  pinMode(17 /* Pin para el LED*/, 0x03);

  // Inicializar la comunicación serial
  Serial0.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();

  // Tarea 1: Lectura del puerto serial cada 50 ms
  if (currentMillis - previousMillisRead >= intervalRead) {
    previousMillisRead = currentMillis;

    if (Serial0.available() > 0) {
      // Leer el dato del serial (aunque no haremos nada específico con el dato recibido)
      char incomingByte = Serial0.read();

      // Enviar el estado del LED al puerto serial
      if (ledBlinkState == 0x1) {
        Serial0.println("Encendido");
      } else {
        Serial0.println("Apagado");
      }
    }
  }
    if (currentMillis - previousMillisBlink >= intervalBlink) {
    previousMillisBlink = currentMillis;

    // Alternar el estado del LED
    ledBlinkState = !ledBlinkState;
    digitalWrite(17 /* Pin para el LED*/, ledBlinkState);
  }
}
