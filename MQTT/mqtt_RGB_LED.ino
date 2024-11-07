#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Initialize WiFi Config
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_pass"";
WiFiClient espClient;

// Initialize MQTT Config
const char* mqttServer = "192.168.7.130";
const char* mqttUser = "";
const char* mqttPass = "";
const char* subTopic = "LED";
const char* pubTopic = "LED";
String clientId = "MYID-";
PubSubClient client(espClient);

// RGB LED connected to Wemos D1 mini
#define R 2
#define G 0
#define B 4

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
    char messageBuffer[length+1];
    snprintf(messageBuffer, length+1, "%s", payload);
    Serial.print("Message arrived: [ ");
    Serial.print(messageBuffer);
    Serial.print(" ]\n");

    // Switch on the LED if payload==on
    // and Switch off if payload==off
    if (strcmp( messageBuffer, "red" ) == 0) {
        digitalWrite(R, HIGH);
        digitalWrite(G, LOW);
        digitalWrite(B, LOW);
    } else if (strcmp( messageBuffer, "green" ) == 0) {
        digitalWrite(R, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(B, LOW);
    } else if (strcmp( messageBuffer, "blue" ) == 0) {
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(B, HIGH);
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
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    Serial.begin(9600);
    setup_wifi();
    client.setServer(mqttServer, 1883);
    client.setCallback(callback);
    
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
