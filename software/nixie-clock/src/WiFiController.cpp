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

static const char AUX_INFORMATION_PROVIDER[] PROGMEM = R"(
{
  "title": "Mode",
  "uri": "/informationprovider",
  "menu": true,
  "element": [
    {
      "name": "caption",
      "type": "ACText",
      "value": "Sets the current display mode.",
      "style": "font-family:Arial;font-weight:bold;text-align:center;margin-bottom:10px;color:DarkSlateBlue"
    },
    {
      "name": "provider",
      "type": "ACSelect",
      "label": "Select Mode",
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

static const InformationProvider_t providers[] = {
        {"Time", 0},
        {"Date",1},
        {"Year",2}
};

const char *fw_ver = "current version: " NIXIECLOCK_VERSION;

AutoConnectAux Timezone, InformationProvider;
WebServer webServer;

void sendRedirect(const String &uri) {
    webServer.sendHeader("Location", uri, true);
    webServer.send(302, "text/plain", "");
    webServer.client().stop();
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
    webServer.send(200, "text/html", content);
}

void startPage() {
    // Retrieve the value of AutoConnectElement with arg function of WebServer class.
    // Values are accessible with the element name.
    String tz = webServer.arg("timezone");

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

    /*String provider = webServer.arg("provider");

    for (const auto &currentProvider: providers) {
        String providerName = String(currentProvider.name);
        if (provider.equalsIgnoreCase(providerName)) {
            _informationProxy->setProvider(currentProvider.providerIndex);
            break;
        }
    }*/

    webServer.sendHeader("Location", String("http://") + webServer.client().localIP().toString() + String("/"));
    webServer.send(302, "text/plain", "");
    webServer.client().flush();
    webServer.client().stop();
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
    _asyncWebServer = AsyncWebServer(8080);

    /*struct rootPageCallback: public Callback<void(void)>{};
    rootPageCallback::func = std::bind(&WiFiController::_rootPage, this);
    auto funcRootPage = static_cast<void(*)()>(rootPageCallback::callback);*/

    /*struct startPageCallback: public Callback<void(void)>{};
    startPageCallback::func = std::bind(&WiFiController::_startPage, this);
    auto funcStartPage = static_cast<void(*)()>(startPageCallback::callback);*/

    nixieController = nixie_controller;

    _autoConnectConfig.ota = AC_OTA_BUILTIN;
    _autoConnectConfig.otaExtraCaption = fw_ver;
    _autoConnectConfig.autoReconnect = true;
    _autoConnectConfig.tickerPort = 12;
    _autoConnectConfig.ticker = true;
    _autoConnectConfig.apid = "nixie-clock";
    _autoConnectConfig.homeUri = "nixie-clock";
    _portal.onOTAStart(togglePowerAndWait);
    _portal.onOTAEnd(togglePowerAndWait);
    _portal.onOTAError(otaError);
    //deleteAllCredentials();
    pinMode(12, OUTPUT);
    for (int i = 0; i < 2; i++) {
        digitalWrite(12, LOW);
        delay(2000);
        digitalWrite(12, HIGH);
        delay(1000);
    }

    _portal.config(_autoConnectConfig);

    Timezone.load(AUX_TIMEZONE);
    auto &tz = Timezone["timezone"].as<AutoConnectSelect>();
    for (const auto &timezone: TZ) {
        tz.add(String(timezone.zone));
    }
    _portal.join({Timezone});

    /*InformationProvider.load(AUX_INFORMATION_PROVIDER);
    auto &provider = InformationProvider["provider"].as<AutoConnectSelect>();
    for (const auto &currentProvider: providers) {
        provider.add(String(currentProvider.name));
    }
    _portal.join({InformationProvider});*/

    webServer.on("/", rootPage);
    webServer.on("/start", startPage);

    if (_portal.begin()) {
        Serial.println("WiFi connected: " + WiFi.localIP().toString());
    }
    _asyncWebServer.begin();
}

void WiFiController::step() {
    _portal.handleClient();
}

AsyncWebServer &WiFiController::getAsyncServer() {
    return _asyncWebServer;
}

WiFiController::WiFiController(InformationProxy* proxy) : _portal{webServer},
                                                          _asyncWebServer{8080}, _informationProxy{proxy} {}
