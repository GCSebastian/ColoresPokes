#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

const char* WIFI_SSID = "RedESP32";
const char* WIFI_PASSWORD = "redEsp123";
const char* API_KEY = "AIzaSyCUXArBuP4HPr0klfKCVnyyHUwIG4ZoXFo";
const char* FIREBASE_PROJECT_ID = "pokegaiborcarpio";
const char* USER_EMAIL = "espgaibor32@esp.com";
const char* USER_PASSWORD = "12345678";

int rpin = 21;
int gpin = 22;
int bpin = 23;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setColor(int red, int green, int blue) {
  analogWrite(rpin, red);
  analogWrite(gpin, green);
  analogWrite(bpin, blue);
}



void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  setupWiFi();
  setupFirebase();
}

void loop() {
  String path = "Leds";
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];
        const char* colorMuestra = document["fields"]["color"]["stringValue"];

        Serial.print(" : ");
        if (strstr(document_name, "Led") != nullptr) {
          Serial.print(colorMuestra);

          if (strcmp(colorMuestra, "azul") == 0) {
              setColor(0, 0, 255); 
            }
            else if (strcmp(colorMuestra, "verde") == 0) {
              setColor(0, 255, 0); 
            }
            else if (strcmp(colorMuestra, "rojo") == 0) {
              setColor(255, 0, 0); 
            }
            else if (strcmp(colorMuestra, "amarillo") == 0) {
              setColor(255, 228, 0); 
            }
            else if (strcmp(colorMuestra, "tomate") == 0) {
              setColor(255, 135, 0); 
            }
            else if (strcmp(colorMuestra, "morado") == 0) {
              setColor(139, 0, 255); 
            }
            else if (strcmp(colorMuestra, "verdeoz") == 0) {
              setColor(3, 184, 5); 
            }
            else if (strcmp(colorMuestra, "blanco") == 0) {
              setColor(255, 255, 255); 
            }
            else if (strcmp(colorMuestra, "cafe") == 0) {
              setColor(111, 69, 7); 
            }
            else if (strcmp(colorMuestra, "celesteD") == 0) {
              setColor(153, 255, 255); 
            }
            else if (strcmp(colorMuestra, "moradoG") == 0) {
              setColor(128, 0, 128); 
            }
            else if (strcmp(colorMuestra, "celesteF") == 0) {
              setColor(135, 206, 235); 
            }
             else if (strcmp(colorMuestra, "rosado") == 0) {
              setColor(255, 0, 255); 
            }
             else if (strcmp(colorMuestra, "rojoP") == 0) {
              setColor(255, 50, 0); 
            }
             else if (strcmp(colorMuestra, "gris") == 0) {
              setColor(112, 128, 144); 
            }
             else if (strcmp(colorMuestra, "celeste") == 0) {
              setColor(135, 206, 235); 
            }
            else if (strcmp(colorMuestra, "negro") == 0) {
              setColor(25, 25, 25); 
            }
            else if (strcmp(colorMuestra, "grisC") == 0) {
              setColor(170, 170, 170); 
            }
            else if (strcmp(colorMuestra, "rosa") == 0) {
              setColor(255, 192, 203); 
            }
 
        }
      }
    }

    delay(1000); // Añade un pequeño retardo antes de la siguiente iteración
  }
}
