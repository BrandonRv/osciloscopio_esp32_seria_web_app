#include <Arduino.h>
#line 1 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino"
#include <driver/adc.h>
#include <esp_adc_cal.h>

#define ADC_CHANNEL ADC2_CHANNEL_5 // GPIO 26 es ADC2_CHANNEL_6
#define SAMPLE_RATE 100000 // Número de muestras por segundo (máxima capacidad)
#define ADC_WIDTH ADC_WIDTH_BIT_12 // Resolución del ADC (12 bits)
#define ADC_ATTEN ADC_ATTEN_DB_11 // Atenuación de 11dB para rangos de 0-3.3V

#line 9 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino"
void setup();
#line 17 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino"
void loop();
#line 9 "/Users/brandonrv/Documents/PROYECTO PELADO UNIVERSIDAD/generador_de_onda/generador_de_onda.ino"
void setup() {
  // Configuración del ADC2 (GPIO 26)
  adc2_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

  // Inicializar comunicación serial a alta velocidad
  Serial.begin(115200);
}

void loop() {
  int adcValue = 0; // Variable para almacenar el valor leído por el ADC

  while (true) {
    // Leer el valor del ADC2 (GPIO 26)
    esp_err_t r = adc2_get_raw(ADC_CHANNEL, ADC_WIDTH, &adcValue);

    if (r == ESP_OK) { // Verificar si la lectura del ADC fue exitosa
      // Mapear el valor leído de 0-4095 a 0-3.3V (12 bits)
      float voltage = (adcValue * 3.3) / 4095.0;

      // Imprimir los valores leídos por el ADC
      Serial.print("ADC2: ");
      Serial.print(adcValue);
      Serial.print("\tVoltaje: ");
      Serial.println(voltage, 4);
    } else {
      Serial.println("Error leyendo el ADC2"); // Mensaje de error en caso de fallo
    }

    // Pausar brevemente para la siguiente lectura (ajustar según sea necesario)
    delayMicroseconds(1000000 / SAMPLE_RATE);
  }
}

