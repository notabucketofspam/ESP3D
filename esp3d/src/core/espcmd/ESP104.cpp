/*
 ESP104.cpp - ESP3D command class

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
#if defined( WIFI_FEATURE) ||  defined( BLUETOOTH_FEATURE) || defined (ETH_FEATURE)
#include "../commands.h"
#include "../esp3doutput.h"
#include "../settings_esp3d.h"
#include "../../modules/network/netconfig.h"
#include "../../modules/authentication/authentication_service.h"
//Set STA fallback mode state at boot which can be BT, WIFI-AP,  OFF
//[ESP104]<state>pwd=<admin password>
bool Commands::ESP104(const char* cmd_params, level_authenticate_type auth_type, ESP3DOutput * output)
{
    bool response = true;
    String parameter;
#ifdef AUTHENTICATION_FEATURE
    if (auth_type == LEVEL_GUEST) {
        output->printERROR("Wrong authentication!", 401);
        return false;
    }
#else
    (void)auth_type;
#endif //AUTHENTICATION_FEATURE
    parameter = get_param (cmd_params, "");
    //get
    if (parameter.length() == 0) {
        int8_t wifiMode = Settings_ESP3D::read_byte(ESP_STA_FALLBACK_MODE);
        if (wifiMode == ESP_NO_NETWORK) {
            output->printMSG("OFF");
        } else if (wifiMode == ESP_BT) {
            output->printMSG("BT");
        } else if (wifiMode == ESP_WIFI_AP) {
            output->printMSG("WIFI-AP");
        } else {
            output->printMSG("??");
        }
    } else { //set
#ifdef AUTHENTICATION_FEATURE
        if (auth_type != LEVEL_ADMIN) {
            output->printERROR("Wrong authentication!", 401);
            return false;
        }
#endif //AUTHENTICATION_FEATURE
        parameter.toUpperCase();
        if (!(
#if defined( BLUETOOTH_FEATURE)
                    (parameter == "BT") ||
#endif //BLUETOOTH_FEATURE     
#if defined( WIFI_FEATURE)
                    (parameter == "WIFI-AP") ||
#endif //WIFI_FEATURE
#if defined( ETH_FEATURE)
                    (parameter == "ETH-STA") || //(parameter == "ETH-SRV") ||
#endif //ETH_FEATURE
                    (parameter == "OFF"))) {

            output->printERROR ("Only "
#ifdef BLUETOOTH_FEATURE
                                "BT or "
#endif //BLUETOOTH_FEATURE
#ifdef WIFI_FEATURE
                                "WIFI-AP or "
#endif //WIFI_FEATURE
                                "OFF mode supported!");
            return false;
        }

        int8_t bbuf = ESP_NO_NETWORK;
#ifdef WIFI_FEATURE
        if(parameter == "WIFI-AP") {
            bbuf = ESP_WIFI_AP;
        }
#endif //WIFI_FEATURE

#ifdef BLUETOOTH_FEATURE
        if(parameter == "BT") {
            bbuf = ESP_BT;
        }
#endif //BLUETOOTH_FEATURE
        if (!Settings_ESP3D::write_byte(ESP_STA_FALLBACK_MODE, bbuf)) {
            output->printERROR ("Set failed!");
            response = false;
        } else {
            output->printMSG("Fallback mode updated");
        }
    }
    return response;
}

#endif //WIFI_FEATURE
