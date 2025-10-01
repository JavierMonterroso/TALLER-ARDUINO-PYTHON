import serial
import time

# Configura el puerto serie (ajusta el COM o /dev/ttyUSB según tu PC)
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=1)
time.sleep(2)  # esperar a que Arduino se reinicie

print("Leyendo datos desde Arduino...\n")

try:
    while True:
        # Leer una línea desde Arduino
        linea = arduino.readline().decode('utf-8').strip()
        
        if linea:  # si hay datos
            try:
                # Esperamos que Arduino mande "temp,humedad,distancia"
                temp, hum, dist = linea.split(",")
                print(f"Temperatura: {temp} °C | Humedad: {hum} % | Distancia: {dist} cm")
            except ValueError:
                # Si la línea no viene bien formada
                print("Dato recibido:", linea)

except KeyboardInterrupt:
    print("\nPrograma detenido por el usuario.")

finally:
    arduino.close()
