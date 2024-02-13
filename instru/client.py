import time
import paho.mqtt.client as paho

resolution_voltage = 0.01960784313725490196078431372549

broker = "143.198.97.197"
port = 1883

username = "app"
password = "display"

def string_to_number(byte_string):
    value = 0
    length = len(byte_string) - 1

    for i,x in enumerate(byte_string):
        value += int(x) * pow(2,(length - i)) 

    return value

def calculate_voltage(binary_value):
    return 12 * binary_value * resolution_voltage

#define callback
def on_message(client, userdata, message):
    #time.sleep(1)
    #print("received message =",str(message.payload.decode("utf-8")))
    print("Voltaje = ", calculate_voltage(string_to_number(str(message.payload.decode("utf-8")))))

def connect_mqtt():

    client = paho.Client("app") 
    client.username_pw_set(username, password)
    print("connecting to broker ",broker, port)
    client.connect(broker, port)
    return client

def subscribe(client):
    client.on_message = on_message
    print("subscribing ")
    client.subscribe("voltmeter")#subscribe

def run():
    client = connect_mqtt()
    #client.loop_start() #start loop to process received messages
    subscribe(client)
    client.loop_forever()

    client.disconnect() #disconnect
    client.loop_stop() #stop loop

if __name__ == '__main__':
    run()