# 1 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino"
# 2 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino" 2
# 3 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino" 2






void setup() {
  // Configuración del ADC2 (GPIO 26)
  adc2_config_channel_atten(ADC2_CHANNEL_5 /* GPIO 26 es ADC2_CHANNEL_6*/, ADC_ATTEN_DB_11 /* Atenuación de 11dB para rangos de 0-3.3V*/);

  // Inicializar comunicación serial a alta velocidad
  Serial0.begin(115200);
}

void loop() {
  int adcValue = 0; // Variable para almacenar el valor leído por el ADC

  while (true) {
    // Leer el valor del ADC2 (GPIO 26)
    esp_err_t r = adc2_get_raw(ADC2_CHANNEL_5 /* GPIO 26 es ADC2_CHANNEL_6*/, ADC_WIDTH_BIT_12 /* Resolución del ADC (12 bits)*/, &adcValue);

    if (r == 0 /*!< esp_err_t value indicating success (no error) */) { // Verificar si la lectura del ADC fue exitosa
      // Mapear el valor leído de 0-4095 a 0-3.3V (12 bits)
      float voltage = (adcValue * 3.3) / 4095.0;

      // Imprimir los valores leídos por el ADC
      Serial0.print("ADC2: ");
      Serial0.print(adcValue);
      Serial0.print("\tVoltaje: ");
      Serial0.println(voltage, 4);
    } else {
      Serial0.println("Error leyendo el ADC2"); // Mensaje de error en caso de fallo
    }

    // Pausar brevemente para la siguiente lectura (ajustar según sea necesario)
    delayMicroseconds(1000000 / 100000 /* Número de muestras por segundo (máxima capacidad)*/);
  }
}
