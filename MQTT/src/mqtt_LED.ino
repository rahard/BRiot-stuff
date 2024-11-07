#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// #include <Config.h>

// Initialize WiFi Config
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_password";
WiFiClient espClient;

// Initialize MQTT Config
const char* mqttServer = "192.168.7.130";
const char* mqttUser = "";
const char* mqttPass = "";
const char* subTopic = "LED";
const char* pubTopic = "LED";
String clientId = "MYID-";
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
    char messageBuffer[length+1];
    snprintf(messageBuffer, length+1, "%s", payload);
    Serial.print("Message arrived: [ ");
    Serial.print(messageBuffer);
    Serial.print(" ]\n");

    // Switch on the LED if payload==on
    // and Switch off if payload==off
    if (strcmp( messageBuffer, "on" ) == 0) {
        digitalWrite(LED_BUILTIN, LOW);     
    } else if (strcmp( messageBuffer, "off" ) == 0) {
        digitalWrite(LED_BUILTIN, HIGH);  
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
