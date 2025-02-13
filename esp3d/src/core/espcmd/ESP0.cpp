/*
 ESP100.cpp - ESP3D command class

 Copyright (c) 2014 Luc Lebosse. All rights reserved.

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with This code; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "../../include/esp3d_config.h"
#include "../commands.h"
#include "../esp3doutput.h"
#include "../settings_esp3d.h"
const char * help[]= {"[ESP] - display this help",
#if defined (WIFI_FEATURE)
                      "[ESP100](SSID) - display/set STA SSID",
                      "[ESP101](Password) - set STA password",
#endif //WIFI_FEATURE
#if defined (WIFI_FEATURE) || defined (ETH_FEATURE)
                      "[ESP102](Mode) - display/set STA IP mode (DHCP/STATIC)",
                      "[ESP103](IP=xxxx MSK=xxxx GW=xxxx) - display/set STA IP/Mask/GW",
#endif //WIFI_FEATURE || ETH_FEATURE
#if defined( WIFI_FEATURE) ||  defined( BLUETOOTH_FEATURE) || defined (ETH_FEATURE)
                      "[ESP104](State) - display/set sta fallback mode which can be BT, AP, OFF",
#endif // WIFI_FEATURE || BLUETOOTH_FEATURE || ETH_FEATURE
#if defined (WIFI_FEATURE)
                      "[ESP105](SSID) - display/set AP SSID",
                      "[ESP106](Password) - set AP password",
                      "[ESP107](IP) - display/set AP IP",
                      "[ESP108](Chanel) - display/set AP chanel",
#endif //WIFI_FEATURE
#if defined( WIFI_FEATURE) ||  defined( BLUETOOTH_FEATURE) || defined (ETH_FEATURE)
                      "[ESP110](State) - display/set radio state which can be BT, STA, AP, OFF",
#endif // WIFI_FEATURE || BLUETOOTH_FEATURE || ETH_FEATURE
#if defined( WIFI_FEATURE) || defined (ETH_FEATURE)
                      "[ESP111](header)display current IP",
#endif //WIFI_FEATURE || ETH_FEATURE
#if defined(WIFI_FEATURE) || defined(ETH_FEATURE) || defined(BT_FEATURE)
                      "[ESP112](Hostname) - display/set Hostname",
                      "[ESP114](State) - display/set boot Network state which can be ON, OFF",
                      "[ESP115](State) - display/set immediate Network state which can be ON, OFF",
#endif //WIFI_FEATURE || ETH_FEATURE || BT_FEATURE
#if defined(HTTP_FEATURE)
                      "[ESP120](State) - display/set HTTP state which can be ON, OFF",
                      "[ESP121](Port) - display/set HTTP port ",
#endif //HTTP_FEATURE
#if defined(TELNET_FEATURE)
                      "[ESP130](State) - display/set Telnet state which can be ON, OFF",
                      "[ESP131](Port) - display/set Telnet port",
#endif //TELNET_FEATURE
#if defined(TIMESTAMP_FEATURE)
                      "[ESP140](SYNC) (srv1=xxxx) (srv2=xxxx) (srv3=xxxx) (zone=xxx) (dst=YES/NO) (time=YYYY-MM-DD#H24:MM:SS) - sync/display/set current time/time servers",
#endif //TIMESTAMP_FEATURE
                      "[ESP150](delay=time) (verbose=ON/OFF)- display/set boot delay in ms / Verbose boot",
#if defined(WS_DATA_FEATURE)
                      "[ESP160](State) - display/set WebSocket state which can be ON, OFF, CLOSE",
                      "[ESP161](Port) - display/set WebSocket port",
#endif //WS_DATA_FEATURE
#if defined(CAMERA_DEVICE)
                      "[ESP170](plain) (label=value) - display(JSON/plain)/set Camera commands",
#endif //CAMERA_DEVICE
#if defined(FTP_FEATURE)
                      "[ESP180](State) - display/set FTP state which can be ON, OFF",
                      "[ESP181](ctrl=xxxx) (active=xxxx) (passive=xxxx) - display/set FTP ports",
#endif //FTP_FEATURE
#if defined(WEBDAV_FEATURE)
                      "[ESP190](State) - display/set WebDav state which can be ON, OFF",
                      "[ESP191](Port) - display/set WebDav port",
#endif //WEBDAV_FEATURE
#if defined (SD_DEVICE)
                      "[ESP200] - display SD Card Status",
#endif //SD_DEVICE
#ifdef DIRECT_PIN_FEATURE
                      "[ESP201](Pxxx) (Vxxx) (PULLUP=YES RAW=YES ANALOG=NO ANALOG_RANGE=255 CLEARCHANNELS=NO) - read / set  pin value",
#endif //DIRECT_PIN_FEATURE
#if defined (SD_DEVICE)
                      "[ESP202] - display / set  SD Card  SD card Speed factor (1 2 4 6 8 16 32)",
#endif //SD_DEVICE
#ifdef SENSOR_DEVICE
                      "[ESP210](type=NONE/xxx) (interval=xxxx) - display and read/set SENSOR info",
#endif //SENSOR_DEVICE
#if defined (DISPLAY_DEVICE)
                      "[ESP214](text) - display (text) to ESP screen status",
#if defined(DISPLAY_TOUCH_DRIVER)
                      "[ESP215](CALIBRATE) - display state / start touch calibration",
#endif //DISPLAY_TOUCH_DRIVER
#if defined(DISPLAY_SNAPSHOT_FEATURE)
                      "[ESP216](SNAP) - Take screen snapshot",
#endif //DISPLAY_SNAPSHOT_FEATURE
#endif //DISPLAY_DEVICE
#ifdef BUZZER_DEVICE
                      "[ESP250]F=(frequency) D=(duration) - play sound on buzzer",
#endif //BUZZER_DEVICE
                      "[ESP290](delay in ms) - do a pause",
                      "[ESP400] - display ESP3D settings in JSON",
                      "[ESP401]P=(position) T=(type) V=(value) - Set specific setting",
#ifdef SD_UPDATE_FEATURE
                      "[ESP402](State) - display/set check update at boot from SD which can be ON, OFF",
#endif //SD_UPDATE_FEATURE
#if defined (WIFI_FEATURE)
                      "[ESP410](plain) - display available AP list (limited to 30) in plain/JSON",
#endif //WIFI_FEATURE
                      "[ESP420](plain) - display ESP3D current status in plain/JSON",
                      "[ESP444](Cmd) - set ESP3D state (RESET/RESTART)",
#if defined (AUTHENTICATION_FEATURE)
                      "[ESP550](password) - change admin password",
                      "[ESP555](password) - change user password",
#endif //AUTHENTICATION_FEATURE
#if defined(NOTIFICATION_FEATURE)
                      "[ESP600](message) - send notification",
                      "[ESP610]type=(NONE/PUSHOVER/EMAIL/LINE) (T1=xxx) (T2=xxx) (TS=xxx) - display/set Notification settings",
                      "[ESP620]URL=http://XXXXXX  - send GET notification",
#endif //NOTIFICATION_FEATURE
#if defined(FILESYSTEM_FEATURE) && defined(ESP_GCODE_HOST_FEATURE)
                      "[ESP700](filename) - read ESP Filesystem file",
#endif //FILESYSTEM_FEATURE
#if defined(FILESYSTEM_FEATURE)
                      "[ESP710]FORMAT - Format ESP Filesystem",
#endif //FILESYSTEM_FEATURE
#if defined (SD_DEVICE)
                      "[ESP715]FORMATSD - Format SD Filesystem",
#endif //SD_DEVICE
#if defined(FILESYSTEM_FEATURE)
                      "[ESP720](path) - List ESP Filesystem",
                      "[[ESP730]](Action)=(path) - rmdir / remove / mkdir / exists / create on ESP FileSystem (path)",
#endif //FILESYSTEM_FEATURE
#if defined (SD_DEVICE)
                      "[ESP740](path)  - List SD Filesystem",
                      "[ESP750](Action)=(path) - rmdir / remove / mkdir / exists / create on SD (path)",
#endif //SD_DEVICE
#if defined (GLOBAL_FILESYSTEM_FEATURE)
                      "[ESP780](path)  - List Global Filesystem",
                      "[ESP790](Action)=(path) - rmdir / remove / mkdir / exists / create on Global Filesystem (path)",
#endif //GLOBAL_FILESYSTEM_FEATURE
                      "[ESP800](plain)(time=YYYY-MM-DD-HH-MM-SS) - display FW Informations in plain/JSON",
                      "[ESP900](ENABLE/DISABLE) - display/set serial state",
                      "[ESP901](ENABLE/DISABLE) - display/set verbose boot",
#ifdef BUZZER_DEVICE
                      "[ESP910](ENABLE/DISABLE) - display/set buzzer state",
#endif //BUZZER_DEVICE
                      "[ESP920](client)=(ON/OFF) - display/set SERIAL / LCD / PRINTER_LCD/ WEBSOCKET / TELNET /BT / ALL client state",
                      ""
                     };
const uint cmdlist[]= {0,
#if defined (WIFI_FEATURE)
                       100,
                       101,
#endif //WIFI_FEATURE
#if defined (WIFI_FEATURE) || defined (ETH_FEATURE)
                       102,
                       103,
#endif //WIFI_FEATURE || ETH_FEATURE
#if defined( WIFI_FEATURE) ||  defined( BLUETOOTH_FEATURE) || defined (ETH_FEATURE)
                       104,
#endif // WIFI_FEATURE || BLUETOOTH_FEATURE || ETH_FEATURE
#if defined (WIFI_FEATURE)
                       105,
                       106,
                       107,
                       108,
#endif //WIFI_FEATURE
#if defined( WIFI_FEATURE) ||  defined( BLUETOOTH_FEATURE) || defined (ETH_FEATURE)
                       110,
#endif // WIFI_FEATURE || BLUETOOTH_FEATURE || ETH_FEATURE
#if defined( WIFI_FEATURE) || defined (ETH_FEATURE)
                       111,
#endif //WIFI_FEATURE || ETH_FEATURE
#if defined(WIFI_FEATURE) || defined(ETH_FEATURE) || defined(BT_FEATURE)
                       112,
                       114,
                       115,
#endif //WIFI_FEATURE || ETH_FEATURE || BT_FEATURE
#if defined(HTTP_FEATURE)
                       120,
                       121,
#endif //HTTP_FEATURE
#if defined(TELNET_FEATURE)
                       130,
                       131,
#endif //TELNET_FEATURE
#if defined(TIMESTAMP_FEATURE)
                       140,
#endif //TIMESTAMP_FEATURE
                       150,
#if defined(WS_DATA_FEATURE)
                       160,
                       161,
#endif //WS_DATA_FEATURE
#if defined(CAMERA_DEVICE)
                       170,
#endif //CAMERA_DEVICE
#if defined(FTP_FEATURE)
                       180,
                       181,
#endif //FTP_FEATURE
#if defined(WEBDAV_FEATURE)
                       190,
                       191,
#endif //WEBDAV_FEATURE
#if defined (SD_DEVICE)
                       200,
#endif //SD_DEVICE
#ifdef DIRECT_PIN_FEATURE
                       201,
#endif //DIRECT_PIN_FEATURE
#if defined (SD_DEVICE)
                       202,
#endif //SD_DEVICE
#ifdef SENSOR_DEVICE
                       210,
#endif //SENSOR_DEVICE
#if defined (DISPLAY_DEVICE)
                       214,
#if defined(DISPLAY_TOUCH_DRIVER)
                       215,
#endif //DISPLAY_TOUCH_DRIVER
#if defined(DISPLAY_SNAPSHOT_FEATURE)
                       216,
#endif //DISPLAY_SNAPSHOT_FEATURE
#endif //DISPLAY_DEVICE
#ifdef BUZZER_DEVICE
                       250,
#endif //BUZZER_DEVICE
                       290,
                       400,
                       401,
#if defined (WIFI_FEATURE)
                       410,
#endif //WIFI_FEATURE
                       420,
                       444,
#if defined (AUTHENTICATION_FEATURE)
                       550,
                       555,
#endif //AUTHENTICATION_FEATURE
#if defined(NOTIFICATION_FEATURE)
                       600,
                       610,
                       620,
#endif //NOTIFICATION_FEATURE
#if defined(FILESYSTEM_FEATURE) && defined(ESP_GCODE_HOST_FEATURE)
                       700,
#endif //FILESYSTEM_FEATURE
#if defined(FILESYSTEM_FEATURE)
                       710,
#endif //FILESYSTEM_FEATURE
#if defined (SD_DEVICE)
                       715,
#endif //SD_DEVICE
#if defined(FILESYSTEM_FEATURE)
                       720,
                       730,
#endif //FILESYSTEM_FEATURE
#if defined (SD_DEVICE)
                       740,
                       750,
#endif //SD_DEVICE
#if defined (GLOBAL_FILESYSTEM_FEATURE)
                       780,
                       790,
#endif //GLOBAL_FILESYSTEM_FEATURE
                       800,
                       900,
                       901,
#ifdef BUZZER_DEVICE
                       910,

#endif //BUZZER_DEVICE
                       920,
                       0
                      };


//ESP3D Help
//[ESP0] or [ESP]<command>
bool Commands::ESP0(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool response = true;
    String parameter;
    const uint cmdNb = sizeof(help)/sizeof(char*);
    (void)auth_type;
    parameter = get_param (cmd_params, "");
    if (parameter.length() == 0) {
        output->printLN("[List of ESP3D commands]");
        for (uint i = 0; i < cmdNb -1; i++) {
            output->printLN(help[i]);
        }
    } else {
        bool found = false;
        uint cmdval = String(cmd_params).toInt();
        if (sizeof(help)/sizeof(char*) != sizeof(cmdlist)/sizeof(uint)) {
            output->printLN("Error in code");
            return false;
        }
        for (uint i = 0; i < cmdNb-1; i++) {
            if (cmdlist[i] == cmdval) {
                output->printLN(help[i]);
                found = true;
            }
        }
        if (!found) {
            String tmp = "This command is not supported: ";
            tmp+= cmd_params;
            output->printLN(tmp.c_str());
        }
    }
    return response;
}
