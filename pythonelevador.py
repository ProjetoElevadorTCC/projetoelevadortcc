from flask import Flask, request, jsonify
import serial
import time

app = Flask(__name__)

# Configuração da porta serial para se comunicar com o Arduino
arduino_port = '/dev/ttyACM0'  # Substitua pela porta serial correta do seu Arduino
arduino_baudrate = 9600
arduino = serial.Serial(arduino_port, arduino_baudrate, timeout=1)

# Mapeamento dos andares para os comandos enviados ao Arduino
floor_commands = {
    '1': '1',
    '2': '2',
    '3': '3'
}

# Variáveis de controle do elevador
current_floor = 1
target_floor = 1

def move_elevator(floor):
    global current_floor, target_floor

    target_floor = floor

    if current_floor == target_floor:
        return f'Você já está no {current_floor}º andar.'

    # Mapeia o andar de destino para o comando correspondente
    command = floor_commands.get(str(target_floor))

    if command is not None:
        # Envia o comando ao Arduino
        arduino.write(command.encode())

        # Atualiza o andar atual
        current_floor = target_floor
        return f'Chegamos ao {current_floor}º andar.'
    else:
        return 'Andar inválido. Por favor, escolha um andar entre 1, 2 e 3.'

@app.route('/elevator', methods=['POST'])
def elevator_intent():
    data = request.get_json()
    floor = data.get('floor')

    if floor is not None:
        response = move_elevator(floor)
    else:
        response = 'Requisição inválida. Por favor, especifique o andar.'

    return jsonify({'response': response})

if __name__ == '__main__':
    app.run(debug=True)
