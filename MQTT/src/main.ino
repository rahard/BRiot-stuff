#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Config.h>

// Initialize WiFi Config
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
WiFiClient espClient;

// Initialize Ultrasonic Sensor Config
const int trigPin = TRIG_PIN;   
const int echoPin = ECHO_PIN;   

// Initialize MQTT Config
const char* mqttServer = MQTT_SERVER;
const char* mqttUser = MQTT_USER;
const char* mqttPass = MQTT_PASSWORD;
const char* subTopic = SUB_TOPIC;
const char* pubTopic = PUB_TOPIC;
String clientId = CLIENTID_PREFIX;
PubSubClient client(espClient);

// Define used variables
long lastMsgTs = 0;
int iteration = 0;

void setup_wifi() {
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    // While unconnected to WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
    char messageBuffer[length+1];                       // somewhere to put the message
    snprintf(messageBuffer, length+1, "%s", payload);
    Serial.print("Message arrived: [ ");
    Serial.print(messageBuffer);
    Serial.print(" ]\n");

    // Switch on the LED if payload==on
    // and Switch off if payload==off
    if (strcmp( messageBuffer, "on" ) == 0) {
        digitalWrite(LED_BUILTIN, LOW);     // Turn the LED on (Note that LOW is the voltage level
                                            // but actually the LED is on; this is because
                                            // it is acive low on the ESP-01)
    } else if (strcmp( messageBuffer, "off" ) == 0) {
        digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    }
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...\n");
        // Create a random client ID
        clientId += String(random(0xffff), HEX);
        char firstMsg[100];
        snprintf(firstMsg, 100, "%s - connected ", clientId.c_str());
        // Attempt to connect
        if (client.connect(clientId.c_str(), mqttUser, mqttPass)) {
            Serial.print(firstMsg);
            Serial.print("to server: ");
            Serial.println(mqttServer);
            // Once connected, publish an announcement...
            client.publish(pubTopic, firstMsg);
            // ... and resubscribe
            client.subscribe(subTopic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    Serial.begin(BAUD_RATE);
    setup_wifi();
    client.setServer(mqttServer, 1883);
    client.setCallback(callback);
    
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    long duration;  
    long distance;
    long now = millis();
    if (now - lastMsgTs > 100) {
      
        digitalWrite(trigPin, LOW);  
        delayMicroseconds(2);  
        // Sets the trigPin on HIGH state for 10 micro seconds  
        digitalWrite(trigPin, HIGH);  
        delayMicroseconds(10);  
        digitalWrite(trigPin, LOW);  

        // Reads the echoPin, returns the sound wave travel time in microseconds  
        duration = pulseIn(echoPin, HIGH);  
        // Calculate the distance  
        distance = duration*0.034/2;  

        ++iteration;
        lastMsgTs = now;
        char pubMsg[100];
        snprintf(pubMsg, 100, "distance: %ld - interation: %d", distance, iteration);
        Serial.print("Publish message:");
        Serial.println(pubMsg);
        client.publish(pubTopic, pubMsg);
    }
}
