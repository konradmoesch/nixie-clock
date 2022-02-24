#include "WiFiController.hpp"

static const char AUX_TIMEZONE[] PROGMEM = R"(
{
  "title": "TimeZone",
  "uri": "/timezone",
  "menu": true,
  "element": [
    {
      "name": "caption",
      "type": "ACText",
      "value": "Sets the time zone to get the current local time.",
      "style": "font-family:Arial;font-weight:bold;text-align:center;margin-bottom:10px;color:DarkSlateBlue"
    },
    {
      "name": "timezone",
      "type": "ACSelect",
      "label": "Select TZ name",
      "option": [],
      "selected": 10
    },
    {
      "name": "newline",
      "type": "ACElement",
      "value": "<br>"
    },
    {
      "name": "start",
      "type": "ACSubmit",
      "value": "OK",
      "uri": "/start"
    }
  ]
}
)";

static const Timezone_t TZ[] = {
        {"Europe/London",        "europe.pool.ntp.org",        0},
        {"Europe/Berlin",        "europe.pool.ntp.org",        1},
        {"Europe/Helsinki",      "europe.pool.ntp.org",        2},
        {"Europe/Moscow",        "europe.pool.ntp.org",        3},
        {"Asia/Dubai",           "asia.pool.ntp.org",          4},
        {"Asia/Karachi",         "asia.pool.ntp.org",          5},
        {"Asia/Dhaka",           "asia.pool.ntp.org",          6},
        {"Asia/Jakarta",         "asia.pool.ntp.org",          7},
        {"Asia/Manila",          "asia.pool.ntp.org",          8},
        {"Asia/Tokyo",           "asia.pool.ntp.org",          9},
        {"Australia/Brisbane",   "oceania.pool.ntp.org",       10},
        {"Pacific/Noumea",       "oceania.pool.ntp.org",       11},
        {"Pacific/Auckland",     "oceania.pool.ntp.org",       12},
        {"Atlantic/Azores",      "europe.pool.ntp.org",        -1},
        {"America/Noronha",      "south-america.pool.ntp.org", -2},
        {"America/Araguaina",    "south-america.pool.ntp.org", -3},
        {"America/Blanc-Sablon", "north-america.pool.ntp.org", -4},
        {"America/New_York",     "north-america.pool.ntp.org", -5},
        {"America/Chicago",      "north-america.pool.ntp.org", -6},
        {"America/Denver",       "north-america.pool.ntp.org", -7},
        {"America/Los_Angeles",  "north-america.pool.ntp.org", -8},
        {"America/Anchorage",    "north-america.pool.ntp.org", -9},
        {"Pacific/Honolulu",     "north-america.pool.ntp.org", -10},
        {"Pacific/Samoa",        "oceania.pool.ntp.org",       -11}
};

const char *fw_ver = "current version: " NIXIECLOCK_VERSION;
WebServer Server;

AutoConnect Portal(Server);
AutoConnectConfig Config;
AutoConnectAux Timezone;


void sendRedirect(const String &uri) {
    Server.sendHeader("Location", uri, true);
    Server.send(302, "text/plain", "");
    Server.client().stop();
}

void rootPage() {
    String content =
            "<html>"
            "<head>"
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
            "<script type=\"text/javascript\">"
            "setTimeout(\"location.reload()\", 1000);"
            "</script>"
            "</head>"
            "<body>"
            "<h2 align=\"center\" style=\"color:blue;margin:20px;\">Hello, world</h2>"
            "<h3 align=\"center\" style=\"color:gray;margin:10px;\">{{DateTime}}</h3>"
            "<p style=\"text-align:center;\">Reload the page to update the time.</p>"
            "<p></p><p style=\"padding-top:15px;text-align:center\">" AUTOCONNECT_LINK(COG_24) "</p>"
            "</body>"
            "</html>";
    String dateTime = TimeController::getLongTime();

    content.replace("{{DateTime}}", dateTime);
    Server.send(200, "text/html", content);
}

void startPage() {
    // Retrieve the value of AutoConnectElement with arg function of WebServer class.
    // Values are accessible with the element name.
    String tz = Server.arg("timezone");

    for (const auto &timezone: TZ) {
        String tzName = String(timezone.zone);
        if (tz.equalsIgnoreCase(tzName)) {
            StorageController::storeTimezoneConfig(timezone);
            TimeController::setTimezone(timezone);
            Serial.println("Time zone: " + tz);
            Serial.println("ntp server: " + String(timezone.ntpServer));
            break;
        }
    }

    Server.sendHeader("Location", String("http://") + Server.client().localIP().toString() + String("/"));
    Server.send(302, "text/plain", "");
    Server.client().flush();
    Server.client().stop();
}

NixieController nixieController;

void deleteAllCredentials() {
    AutoConnectCredential credential;
    station_config_t config;
    uint8_t ent = credential.entries();
    Serial.println(String(ent) + " saved credentials");
    Serial.println("Deleting all wifi credentials");

    while (ent--) {
        int8_t id = 0;
        credential.load(id, &config);
        credential.del((const char *) &config.ssid[0]);
    }
}

void togglePowerAndWait() {
    nixieController.togglePowerSupply();
    delay(1000);
}

void otaError(char errorCode) {
    Serial.println("OTA error: " + String(errorCode));
    togglePowerAndWait();
}

void WiFiController::initialize(NixieController nixie_controller) {
    Log.noticeln("Initializing WiFi");
    delay(1000);
    asyncWebServer = AsyncWebServer(8080);

    nixieController = nixie_controller;

    Config.ota = AC_OTA_BUILTIN;
    Config.otaExtraCaption = fw_ver;
    Config.autoReconnect = true;
    Config.tickerPort = 12;
    Config.ticker = true;
    Portal.onOTAStart(togglePowerAndWait);
    Portal.onOTAEnd(togglePowerAndWait);
    Portal.onOTAError(otaError);
    //deleteAllCredentials();
    pinMode(12, OUTPUT);
    for (int i = 0; i < 2; i++) {
        digitalWrite(12, LOW);
        delay(2000);
        digitalWrite(12, HIGH);
        delay(1000);
    }

    Portal.config(Config);

    Timezone.load(AUX_TIMEZONE);
    auto &tz = Timezone["timezone"].as<AutoConnectSelect>();
    for (const auto &timezone: TZ) {
        tz.add(String(timezone.zone));
    }

    Portal.join({Timezone});

    Server.on("/", rootPage);
    Server.on("/start", startPage);

    if (Portal.begin()) {
        Serial.println("WiFi connected: " + WiFi.localIP().toString());
    }
    asyncWebServer.begin();
}

void WiFiController::step() {
    Portal.handleClient();
}

AsyncWebServer &WiFiController::getAsyncServer() {
    return asyncWebServer;
}

WiFiController::WiFiController() : asyncWebServer{8080} {}
