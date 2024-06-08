#include <Arduino.h>


#include <WiFi.h>
#include <WebServer.h>


// SSID & Password
const char* ssid = "Ander";  // Enter your SSID here
const char* password = "Procesadors";  //Enter your Password here


WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)


// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>"
"<html lang=\"es\">"
"<head>"
"    <meta charset=\"UTF-8\">"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"    <title>Pingüinos - Página Web</title>"
"    <style>"
"        body {"
"            font-family: Arial, sans-serif;"
"            margin: 0;"
"            padding: 0;"
"            background-color: #f0f0f0;"
"        }"
"        header {"
"            background-color: #007bff;"
"            color: white;"
"            padding: 20px;"
"            text-align: center;"
"        }"
"        nav {"
"            background-color: #333;"
"            color: white;"
"            padding: 10px;"
"            text-align: center;"
"        }"
"        nav a {"
"            color: white;"
"            text-decoration: none;"
"            padding: 10px;"
"        }"
"        nav a:hover {"
"            background-color: #555;"
"        }"
"        section {"
"            padding: 20px;"
"        }"
"        footer {"
"            background-color: #007bff;"
"            color: white;"
"            text-align: center;"
"            padding: 10px;"
"            position: fixed;"
"            bottom: 0;"
"            width: 100%;"
"        }"
"    </style>"
"</head>"
"<body>"
"    <header>"
"        <h1>Pingüinos</h1>"
"    </header>"
"    <nav>"
"        <a href=\"#informacion\">Información General</a>"
"        <a href=\"#especies\">Especies</a>"
"        <a href=\"#habitat\">Hábitat</a>"
"        <a href=\"#alimentacion\">Alimentación</a>"
"    </nav>"
"    <section id=\"informacion\">"
"        <h2>Información General</h2>"
"        <p>Los pingüinos son aves marinas no voladoras que habitan en el hemisferio sur. Son conocidos por su plumaje negro y blanco, y su habilidad para nadar y bucear.</p>"
"    </section>"
"    <section id=\"especies\">"
"        <h2>Especies de Pingüinos</h2>"
"        <ul>"
"            <li>Pingüino Emperador</li>"
"            <li>Pingüino Adelaida</li>"
"            <li>Pingüino de Magallanes</li>"
"            <li>Pingüino de Humboldt</li>"
"            <li>Pingüino de Galápagos</li>"
"        </ul>"
"    </section>"
"    <section id=\"habitat\">"
"        <h2>Hábitat</h2>"
"        <p>Los pingüinos habitan principalmente en regiones frías, como la Antártida y algunas islas cercanas al continente sudamericano.</p>"
"    </section>"
"    <section id=\"alimentacion\">"
"        <h2>Alimentación</h2>"
"        <p>La dieta de los pingüinos varía según la especie, pero generalmente consiste en peces, calamares y crustáceos.</p>"
"    </section>"
"    <footer>"
"        <p>&copy; 2024 Pingüinos Web - Todos los derechos reservados</p>"
"    </footer>"
"</body>"
"</html>";
;


// Handle root url (/)
void handle_root() {
server.send(200, "text/html", HTML);
}




void setup() {
Serial.begin(115200);
Serial.println("Try Connecting to ");
Serial.println(ssid);


// Connect to your wi-fi modem
WiFi.begin(ssid, password);


// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP());  //Show ESP32 IP on serial


server.on("/", handle_root);


server.begin();
Serial.println("HTTP server started");
delay(100);
}


void loop() {
server.handleClient();
}
