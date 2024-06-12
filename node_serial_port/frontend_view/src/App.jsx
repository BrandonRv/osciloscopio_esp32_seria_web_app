import React, { useState, useEffect } from 'react';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend } from 'recharts';

function App() {
  const [data, setData] = useState([]);
  const [startTime, setStartTime] = useState(Date.now());

  useEffect(() => {
    const interval = setInterval(fetchSerialData, 100); // Actualizar cada 100 ms

    async function fetchSerialData() {
      try {
        const response = await fetch('http://127.0.0.1:3000/seno');
        const apiData = await response.json();

        // Extraer el valor de ADC2
        const adc2Match = apiData.seno.match(/ADC2:\s*(\d+)/);
        const adc2Value = adc2Match ? parseInt(adc2Match[1], 10) : null;

        console.log(adc2Match ? "si hay" : "no hay serial")
        console.log(adc2Value)

        // Convertir el valor de ADC2 a voltios (suponiendo 0-3.3V para 0-4095)
        const voltage = (adc2Value / 4095) * 3.3; // Rango de 0 a 3.3V

        if (voltage >= 0) {
          // Generar valores sinusoidales entre 1.60 y -1.60
          const time = Date.now();
          const relativeTime = (time - startTime) / 1000; // Tiempo relativo en segundos
          const frequency = 6000; // Frecuencia en Hz
          const amplitude = 1.60; // Amplitud máxima de 1.60V

          // Calcular el valor de la señal sinusoidal
          const sinValue = amplitude * Math.sin(2 * Math.PI * frequency / relativeTime);

          setData(prevData => {
            const newData = [...prevData, { time: time - startTime, value: sinValue }];
            // Limitar el tamaño del array a 200 puntos (ajusta según tus necesidades)
            return newData.slice(-100);
          });
        } else {
          // En caso de que el voltaje sea menor a 0, puedes decidir qué hacer, por ahora no haremos nada.
          console.log("Voltaje menor a 0, no se actualiza la señal sinusoidal");
        }

      } catch (error) {
        console.error('Error fetching serial data:', error);
      }
    }

    return () => clearInterval(interval);
  }, [startTime]);

  return (
    <>
      <div style={{ marginTop: '1px' , paddingLeft: '40px'}}>
        <LineChart width={768} height={412} data={data}>
          <CartesianGrid strokeDasharray="3 3" />
          <XAxis
            dataKey="time"
            type="number"
            domain={['dataMin', 'dataMax']}
            tickFormatter={time => time / 1000 + 'ms'} // Mostrar tiempo relativo en ms
          />
          <YAxis
            domain={[-1.60, 1.60]} // Centrando la señal en el rango de -1.60 a 1.60V
            tickFormatter={volt => volt.toFixed(2) + 'V'} // Formato de voltaje en el eje Y
          />
          <Tooltip />
          <Legend />
          <Line type="monotone" dataKey="value" stroke="#8884d8" /> {/* Ajuste a 'value' en vez de 'voltage' */}
        </LineChart>
      </div>

{/* esta grafica es para mostrar los armonicos de la perimera osea hacer FFT */}

      <div style={{ marginBottom: '20px', paddingLeft: '40px' }}>
        <h2 style={{color: 'black'}}>Armonicos</h2>
        <LineChart width={768} height={412} data={data}>
          <CartesianGrid strokeDasharray="3 3" />
          <XAxis
            dataKey="time"
            type="number"
            domain={['dataMin', 'dataMax']}
            tickFormatter={time => time / 27000 + 'hz'} 
          />
          <YAxis
            domain={[-1.60, 1.60]} 
            tickFormatter={volt => volt.toFixed(2) + 'db'} 
          />
          <Tooltip />
          <Legend />
          <Line type="monotone" dataKey="value" stroke="#8884d8" /> 
        </LineChart>

      </div>

    </>
  );
}

export default App;
